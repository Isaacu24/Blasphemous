#include "PreCompile.h"
#include "Nun.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

Nun::Nun() 
{
}

Nun::~Nun() 
{
}

void Nun::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("nun_idle");

        MetaRenderer_->CreateMetaAnimation(
            "nun_idle",
            {"nun_idle.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    MetaRenderer_->ChangeMetaAnimation("nun_idle");
    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);

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
                             std::bind(&Nun::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Nun::IdleStart, this, std::placeholders::_1),
                             std::bind(&Nun::IdleEnd, this, std::placeholders::_1));

    State_.ChangeState("Idle");

    SetSpeed(150.f);

    PatrolStart_ = true;
    PatrolEnd_   = false;
}

void Nun::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
    Gravity_->SetActive(!IsGround_);
}

void Nun::End() {}

void Nun::PatrolMoveX(float _DeltaTime) {}