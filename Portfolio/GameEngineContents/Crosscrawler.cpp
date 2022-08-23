#include "PreCompile.h"
#include "Crosscrawler.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

Crosscrawler::Crosscrawler() 
{
}

Crosscrawler::~Crosscrawler() 
{
}

void Crosscrawler::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("crosscrawler_idle");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_idle",
            {"crosscrawler_idle.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    MetaRenderer_->ChangeMetaAnimation("crosscrawler_idle");
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
                             std::bind(&Crosscrawler::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::IdleStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::IdleEnd, this, std::placeholders::_1));

    State_.ChangeState("Idle");

    SetSpeed(150.f);

    PatrolStart_ = true;
    PatrolEnd_   = false;
}

void Crosscrawler::Update(float _DeltaTime) 
{
    State_.Update(_DeltaTime);

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
    Gravity_->SetActive(!IsGround_);
}

void Crosscrawler::End() {

}

void Crosscrawler::IdleStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_idle"); }

void Crosscrawler::IdleUpdate(float _DeltaTime, const StateInfo& _Info) 
{

}

void Crosscrawler::IdleEnd(const StateInfo& _Info) {

}

void Crosscrawler::PatrolMoveX(float _DeltaTime)
{

}