#include "PreCompile.h"
#include "LionHead.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

LionHead::LionHead() {}

LionHead::~LionHead() {}

void LionHead::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("Lionhead_idle_anim");

        MetaRenderer_->CreateMetaAnimation(
            "Lionhead_idle_anim",
            {"Lionhead_idle_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    MetaRenderer_->ChangeMetaAnimation("Lionhead_idle_anim");
    MetaRenderer_->SetPivot(PIVOTMODE::BOT);

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

    State_.CreateStateMember("Idle",
                             std::bind(&LionHead::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&LionHead::IdleStart, this, std::placeholders::_1),
                             std::bind(&LionHead::IdleEnd, this, std::placeholders::_1));

    State_.ChangeState("Idle");

    SetSpeed(150.f);

    PatrolStart_ = true;
    PatrolEnd_   = false;
}

void LionHead::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
    Gravity_->SetActive(!IsGround_);
}

void LionHead::End() {}

void LionHead::IdleStart(const StateInfo& _Info) 
{ MetaRenderer_->ChangeMetaAnimation("Lionhead_idle_anim"); }
void LionHead::IdleUpdate(float _DeltaTime, const StateInfo& _Info) {}
void LionHead::IdleEnd(const StateInfo& _Info) {}

void LionHead::PatrolMoveX(float _DeltaTime) {}