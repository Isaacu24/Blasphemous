#include "PreCompile.h"
#include "ShieldMaiden.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

namespace SHIELD_MAIDEN
{
    inline const char* IDLE = "TEST";
}

ShieldMaiden::ShieldMaiden() {}

ShieldMaiden::~ShieldMaiden() {}

void ShieldMaiden::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldMaiden_walking_anim");

        MetaRenderer_->CreateMetaAnimation(
            "shieldMaiden_walking_anim",
            {"shieldMaiden_walking_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_walking_anim");

    //해당 몬스터는 피벗을 맞추면 틀어진다
    // MetaRenderer_->SetPivot(PIVOTMODE::BOT);

    Gravity_ = CreateComponent<GravityComponent>();

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    DetectCollider_->GetTransform().SetWorldScale({300.0f, 300.0f, 1.0f});
    DetectCollider_->GetTransform().SetWorldMove({0, 100.f});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::Monster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({30.0f, 100.0f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({-20, 50.f});

    State_.CreateStateMember("Patrol",
                             std::bind(&ShieldMaiden::PatrolUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ShieldMaiden::PatrolStart, this, std::placeholders::_1),
                             std::bind(&ShieldMaiden::PatrolEnd, this, std::placeholders::_1));

    State_.ChangeState("Patrol");

    SetSpeed(80.f);
    SetTear(15);

    PatrolStart_ = true;
    PatrolEnd_   = false;   
}

void ShieldMaiden::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
    Gravity_->SetActive(!IsGround_);
}

void ShieldMaiden::End() {}


void ShieldMaiden::PatrolMoveX(float _DeltaTime)
{
    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        if (true
            == RightObstacleCheck(GetTransform().GetWorldPosition().x + 70,
                                  -(GetTransform().GetWorldPosition().y)))
        {
            GetTransform().SetWorldMove(float4::RIGHT * Speed_ * _DeltaTime);
        }

        else
        {
            GetTransform().PixLocalNegativeX();

            PatrolEnd_   = true;
            PatrolStart_ = false;
        }   
    }

    else if (false == PatrolStart_ && true == PatrolEnd_)
    {
        if (true
            == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 70, -(GetTransform().GetWorldPosition().y)))
        {
            GetTransform().SetWorldMove(float4::LEFT * Speed_ * _DeltaTime);
        }

        else
        {
            GetTransform().PixLocalPositiveX();

            PatrolStart_ = true;
            PatrolEnd_   = false;
        }
    }
}


void ShieldMaiden::PatrolStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_walking_anim");
}

void ShieldMaiden::PatrolUpdate(float _DeltaTime, const StateInfo& _Info) 
{ 
    PatrolMoveX(_DeltaTime); 

}

void ShieldMaiden::PatrolEnd(const StateInfo& _Info) {}