#include "PreCompile.h"
#include "Crosscrawler.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

Crosscrawler::Crosscrawler() {}

Crosscrawler::~Crosscrawler() {}

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

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("crosscrawler_walking");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_walking",
            {"crosscrawler_walking.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("crosscrawler_turnaround");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_turnaround",
            {"crosscrawler_turnaround.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("crosscrawler_turnaround",
                                    [&](const FrameAnimation_DESC& _Info) { ChangeMonsterState("Patrol"); });
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

    State_.CreateStateMember("Patrol",
                             std::bind(&Crosscrawler::PatrolUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::PatrolStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::PatrolEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Turn",
                             std::bind(&Crosscrawler::TurnUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::TurnStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::TurnEnd, this, std::placeholders::_1));

    State_.ChangeState("Patrol");

    SetSpeed(50.f);
    SetTear(20);

    PatrolStart_ = true;
    PatrolEnd_   = false;
}

void Crosscrawler::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
    Gravity_->SetActive(!IsGround_);
}

void Crosscrawler::End() {}

void Crosscrawler::PatrolMoveX(float _DeltaTime)
{
    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        if (true == RightObstacleCheck(GetTransform().GetWorldPosition().x + 80, -(GetTransform().GetWorldPosition().y))
            && false
                   == RightObstacleCheck(GetTransform().GetWorldPosition().x + 80,
                                         -(GetTransform().GetWorldPosition().y + 30)))
        {
            GetTransform().SetWorldMove(float4::RIGHT * Speed_ * _DeltaTime);
        }

        else
        {
            State_.ChangeState("Turn");

            PatrolEnd_   = true;
            PatrolStart_ = false;
        }
    }

    else if (false == PatrolStart_ && true == PatrolEnd_)
    {
        if (true == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 80, -(GetTransform().GetWorldPosition().y))
            && false
                   == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 80,
                                        -(GetTransform().GetWorldPosition().y + 30)))
        {
            GetTransform().SetWorldMove(float4::LEFT * Speed_ * _DeltaTime);
        }

        else
        {
            State_.ChangeState("Turn");

            PatrolStart_ = true;
            PatrolEnd_   = false;
        }
    }
}

void Crosscrawler::PatrolStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_walking"); }

void Crosscrawler::PatrolUpdate(float _DeltaTime, const StateInfo& _Info) { PatrolMoveX(_DeltaTime); }

void Crosscrawler::PatrolEnd(const StateInfo& _Info) {}

void Crosscrawler::TurnStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_turnaround"); }

void Crosscrawler::TurnUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::TurnEnd(const StateInfo& _Info) 
{
    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        GetTransform().PixLocalPositiveX();
    }

    else if (false == PatrolStart_ && true == PatrolEnd_)
    {
        GetTransform().PixLocalNegativeX();
    }
}

