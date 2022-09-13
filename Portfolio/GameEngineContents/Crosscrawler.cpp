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

        MetaRenderer_->AnimationBindEnd("crosscrawler_idle",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeMonsterState("Patrol"); });
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
            {"crosscrawler_turnaround.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("crosscrawler_turnaround",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeMonsterState("Patrol"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("crosscrawler_attack");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_attack",
            {"crosscrawler_attack.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("crosscrawler_attack",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeMonsterState("Track"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("crosscrawler_death");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_death",
            {"crosscrawler_death.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("crosscrawler_death",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            BloodEffect_->Off();
                                            Death();
                                        });
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

    BloodEffect_ = GetLevel()->CreateActor<BloodSplatters>();
    BloodEffect_->GetRenderer()->Off();

    State_.CreateStateMember("Idle",
                             std::bind(&Crosscrawler::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::IdleStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::IdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Patrol",
                             std::bind(&Crosscrawler::PatrolUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::PatrolStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::PatrolEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Turn",
                             std::bind(&Crosscrawler::TurnUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::TurnStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::TurnEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Track",
                             std::bind(&Crosscrawler::TrackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::TrackStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::TrackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Attack",
                             std::bind(&Crosscrawler::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::AttackStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::AttackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&Crosscrawler::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::DeathStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::DeathEnd, this, std::placeholders::_1));

    State_.ChangeState("Patrol");

    SetSpeed(50.f);
    SetTear(20);
    SetCrossroad(150.f);

    PatrolStart_ = true;
    PatrolEnd_   = false;
}

void Crosscrawler::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
    Gravity_->SetActive(!IsGround_);

    if ("Death" != State_.GetCurStateStateName())
    {
        NormalMonster::DamageCheck(10.f, 30.f);
    }
}

void Crosscrawler::End() {}

void Crosscrawler::PatrolMoveX(float _DeltaTime)
{
    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        if (true == RightObstacleCheck(GetTransform().GetWorldPosition().x + 90, -(GetTransform().GetWorldPosition().y))
            && false
                   == RightObstacleCheck(GetTransform().GetWorldPosition().x + 90,
                                         -(GetTransform().GetWorldPosition().y + 30)))
        {
            Dir_ = float4::RIGHT;
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
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
        if (true == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 90, -(GetTransform().GetWorldPosition().y))
            && false
                   == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 90,
                                        -(GetTransform().GetWorldPosition().y + 30)))
        {
            Dir_ = float4::LEFT;
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
        }

        else
        {
            State_.ChangeState("Turn");

            PatrolStart_ = true;
            PatrolEnd_   = false;
        }
    }
}

void Crosscrawler::IdleStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_idle"); }

void Crosscrawler::IdleUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::IdleEnd(const StateInfo& _Info) {}

void Crosscrawler::PatrolStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_walking"); }

void Crosscrawler::PatrolUpdate(float _DeltaTime, const StateInfo& _Info)
{
    PatrolMoveX(_DeltaTime);

    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&Crosscrawler::TrackPlayer, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Track");
    }
}

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

void Crosscrawler::TrackStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_walking"); }

void Crosscrawler::TrackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == IsPlayerLeft_)
    {
        if (false
            == RightObstacleCheck(GetTransform().GetWorldPosition().x + 90, -(GetTransform().GetWorldPosition().y)))
        {
            State_.ChangeState("Idle");
            return;
        }

        Dir_ = float4::RIGHT;
        GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
    }

    else if (true == IsPlayerRight_)
    {
        if (false
            == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 90, -(GetTransform().GetWorldPosition().y)))
        {
            State_.ChangeState("Idle");
            return;
        }

        Dir_ = float4::LEFT;
        GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
    }

    if (false
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, nullptr))
    {
        // Track or Idle
        State_.ChangeState("Idle");
        return;
    }

    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&Crosscrawler::CrossroadCheck, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Attack");
    }
}

void Crosscrawler::TrackEnd(const StateInfo& _Info) {}


void Crosscrawler::AttackStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_attack"); }

void Crosscrawler::AttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::AttackEnd(const StateInfo& _Info) {}


void Crosscrawler::StunStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_stun_anim"); }

void Crosscrawler::StunUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::StunEnd(const StateInfo& _Info) {}

void Crosscrawler::ExecutionStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("crosscrawler_execution");
}

void Crosscrawler::ExecutionUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::ExecutionEnd(const StateInfo& _Info) {}


void Crosscrawler::DeathStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("crosscrawler_death");
    MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
}

void Crosscrawler::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::DeathEnd(const StateInfo& _Info) {}
