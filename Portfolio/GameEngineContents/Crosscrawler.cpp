#include "PreCompile.h"
#include "Crosscrawler.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

Crosscrawler::Crosscrawler() {}

Crosscrawler::~Crosscrawler() {}

void Crosscrawler::Start()
{
    NormalMonster::Start();

    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("crosscrawler_idle");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_idle",
            {"crosscrawler_idle.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("crosscrawler_walking");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_walking",
            {"crosscrawler_walking.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindFrame("crosscrawler_walking",
                                          [&](const FrameAnimation_DESC& _Info)
                                          {
                                              if (10 == _Info.CurFrame)
                                              {
                                                  SoundPlayer_
                                                      = GameEngineSound::SoundPlayControl("CROSSCRAWLER_WALK_1.wav");
                                                  SoundPlayer_.Volume(0.3f);
                                              }
                                          });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("crosscrawler_turnaround");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_turnaround",
            {"crosscrawler_turnaround.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        MetaRenderer_->AnimationBindFrame(
            "crosscrawler_turnaround",
            [&](const FrameAnimation_DESC& _Info)
            {
                if (1 == _Info.CurFrame)
                {
                    SoundPlayer_ = GameEngineSound::SoundPlayControl("CROSSCRAWLER_TURN.wav");
                    SoundPlayer_.Volume(0.3f);
                }

                if (17 == _Info.CurFrame)
                {
                    SoundPlayer_ = GameEngineSound::SoundPlayControl("CROSSCRAWLER_TURN_END.wav");
                    SoundPlayer_.Volume(0.3f);
                }
            });

        MetaRenderer_->AnimationBindEnd("crosscrawler_turnaround",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            if (false == IsPlayerRight_ && false == IsPlayerLeft_)
                                            {
                                                ChangeMonsterState("Patrol");
                                            }

                                            else
                                            {
                                                ChangeMonsterState("Track");
                                            }
                                        });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("crosscrawler_attack");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_attack",
            {"crosscrawler_attack.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindFrame(
            "crosscrawler_attack",
            [&](const FrameAnimation_DESC& _Info)
            {
                if (1 == _Info.CurFrame)
                {
                    SoundPlayer_ = GameEngineSound::SoundPlayControl("CROSSCRAWLER_ATTACK_1.wav");
                    SoundPlayer_.Volume(0.3f);
                }

                if (15 == _Info.CurFrame)
                {
                    SoundPlayer_ = GameEngineSound::SoundPlayControl("CROSSCRAWLER_ATTACK_2.wav");
                    SoundPlayer_.Volume(0.3f);
                }

                if (19 == _Info.CurFrame)
                {
                    AttackCollider_->On();

                    SoundPlayer_ = GameEngineSound::SoundPlayControl("CROSSCRAWLER_ATTACK_HIT.wav");
                    SoundPlayer_.Volume(0.3f);

                    if (true == Penitent::GetMainPlayer()->GetParryOn())
                    {
                        Penitent::GetMainPlayer()->ParrySlide();
                    }
                }

                else if (20 == _Info.CurFrame)
                {
                    AttackCollider_->Off();
                }
            });

        MetaRenderer_->AnimationBindEnd("crosscrawler_attack",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeMonsterState("Track"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("crosscrawler_death");

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

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("crosscrawler_stun_anim");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_stun_anim",
            {"crosscrawler_stun_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.12f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("crosscrawler_execution");

        MetaRenderer_->CreateMetaAnimation(
            "crosscrawler_execution",
            {"crosscrawler_execution.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("crosscrawler_execution",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            float4 MonsterPos = GetTransform().GetWorldPosition();

                                            if (0 < GetTransform().GetLocalScale().x)
                                            {
                                                Penitent::GetMainPlayer()->GetTransform().SetWorldPosition(
                                                    {MonsterPos.x - 17.5f, MonsterPos.y, PlayerZ});
                                            }

                                            else
                                            {
                                                Penitent::GetMainPlayer()->GetTransform().SetWorldPosition(
                                                    {MonsterPos.x + 17.5f, MonsterPos.y, PlayerZ});
                                            }

                                            Penitent::GetMainPlayer()->ChangeState("Idle");

                                            BloodEffect_->Death();
                                            Death();
                                        });
    }


    MetaRenderer_->ChangeMetaAnimation("crosscrawler_idle");
    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);

    Gravity_ = CreateComponent<GravityComponent>();

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    DetectCollider_->GetTransform().SetWorldScale({600.0f, 200.0f, 1.0f});
    DetectCollider_->GetTransform().SetWorldMove({0, 100.f});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::Monster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({30.0f, 100.0f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({-40, 50.f});

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->ChangeOrder(COLLISIONORDER::MonsterAttack);
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.0f, 0.0f, 0.25f});
    AttackCollider_->GetTransform().SetWorldScale({150.0f, 150.0f, 1.0f});
    AttackCollider_->GetTransform().SetWorldMove({50, 50.f});
    AttackCollider_->Off();

    State_.CreateStateMember("Idle",
                             std::bind(&Crosscrawler::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::IdleStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::IdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Patrol",
                             std::bind(&Crosscrawler::PatrolUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::PatrolStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::PatrolEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "PatrolTurn",
        std::bind(&Crosscrawler::PatrolTurnUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&Crosscrawler::PatrolTurnStart, this, std::placeholders::_1),
        std::bind(&Crosscrawler::PatrolTurnEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "TrackTurn",
        std::bind(&Crosscrawler::TrackTurnUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&Crosscrawler::TrackTurnStart, this, std::placeholders::_1),
        std::bind(&Crosscrawler::TrackTurnEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Track",
                             std::bind(&Crosscrawler::TrackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::TrackStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::TrackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Attack",
                             std::bind(&Crosscrawler::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::AttackStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::AttackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Stun",
                             std::bind(&Crosscrawler::StunUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::StunStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::StunEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "Execution",
        std::bind(&Crosscrawler::ExecutionUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&Crosscrawler::ExecutionStart, this, std::placeholders::_1),
        std::bind(&Crosscrawler::ExecutionEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&Crosscrawler::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Crosscrawler::DeathStart, this, std::placeholders::_1),
                             std::bind(&Crosscrawler::DeathEnd, this, std::placeholders::_1));

    State_.ChangeState("Patrol");

    SetSpeed(50.f);
    SetCrossroad(150.f);

    SetTear(20);

    PatrolStart_ = true;
    PatrolEnd_   = false;
}

void Crosscrawler::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
    Gravity_->SetActive(!IsGround_);

    if ("Death" != State_.GetCurStateStateName() && "Execution" != State_.GetCurStateStateName())
    {
        if (90 > GetHP() && "Stun" != State_.GetCurStateStateName())
        {
            State_.ChangeState("Stun");
            return;
        }

        NormalMonster::DamageCheck(10.f, 30.f);
    }

    GameEngineDebug::OutPutString("Crosscrawler State: " + State_.GetCurStateStateName());
}

void Crosscrawler::End() {}

//���� ������
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
            State_.ChangeState("PatrolTurn");

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
            State_.ChangeState("PatrolTurn");

            PatrolStart_ = true;
            PatrolEnd_   = false;
        }
    }
}


void Crosscrawler::IdleStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_idle"); }

void Crosscrawler::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (1.f > _Info.StateTime)
    {
        return;
    }

    if (false
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&Crosscrawler::DetectPlayer, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Patrol");
    }

    //else
    //{
    //    State_.ChangeState("Attack");
    //}
}

void Crosscrawler::IdleEnd(const StateInfo& _Info) {}


void Crosscrawler::PatrolStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("crosscrawler_walking");

    if (0 > GetTransform().GetLocalScale().x && true == PatrolStart_ && false == PatrolEnd_
        || 0 < GetTransform().GetLocalScale().x && false == PatrolStart_ && true == PatrolEnd_)
    {
        IsPlayerRight_ = false;
        IsPlayerLeft_  = false;

        State_.ChangeState("PatrolTurn");
    }
}

void Crosscrawler::PatrolUpdate(float _DeltaTime, const StateInfo& _Info)
{
    PatrolMoveX(_DeltaTime);

    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, nullptr))
    {
        State_.ChangeState("Track");
    }
}

void Crosscrawler::PatrolEnd(const StateInfo& _Info) {}


void Crosscrawler::PatrolTurnStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("crosscrawler_turnaround");
}

void Crosscrawler::PatrolTurnUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::PatrolTurnEnd(const StateInfo& _Info)
{
    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        Dir_ = float4::RIGHT;
        GetTransform().PixLocalPositiveX();
    }

    else if (false == PatrolStart_ && true == PatrolEnd_)
    {
        Dir_ = float4::LEFT;
        GetTransform().PixLocalNegativeX();
    }
}


void Crosscrawler::TrackTurnStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("crosscrawler_turnaround");
}

void Crosscrawler::TrackTurnUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::TrackTurnEnd(const StateInfo& _Info)
{
    if (true == IsPlayerRight_)
    {
        Dir_ = float4::RIGHT;
        GetTransform().PixLocalPositiveX();
    }

    else if (true == IsPlayerLeft_)
    {
        Dir_ = float4::LEFT;
        GetTransform().PixLocalNegativeX();
    }
}


void Crosscrawler::TrackStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_walking"); }

void Crosscrawler::TrackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&Crosscrawler::TrackPlayer, this, std::placeholders::_1, std::placeholders::_2)))
    {
        if (0 > GetTransform().GetLocalScale().x && true == IsPlayerRight_
            || 0 < GetTransform().GetLocalScale().x && true == IsPlayerLeft_)
        {
            State_.ChangeState("TrackTurn");
            return;
        }

        if (true == IsPlayerLeft_)
        {
            if (false
                    == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 90,
                                         -(GetTransform().GetWorldPosition().y))
                || true
                       == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 90,
                                            -(GetTransform().GetWorldPosition().y + 30)))
            {
                State_.ChangeState("Idle");
                return;
            }

            Dir_ = float4::LEFT;
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
        }

        else if (true == IsPlayerRight_)
        {
            if (false
                    == RightObstacleCheck(GetTransform().GetWorldPosition().x + 90,
                                          -(GetTransform().GetWorldPosition().y))
                || true
                       == RightObstacleCheck(GetTransform().GetWorldPosition().x + 90,
                                             -(GetTransform().GetWorldPosition().y + 30)))
            {
                State_.ChangeState("Idle");
                return;
            }

            Dir_ = float4::RIGHT;
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
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

    else
    {
        State_.ChangeState("Patrol");
    }
}

void Crosscrawler::TrackEnd(const StateInfo& _Info) {}


void Crosscrawler::AttackStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("crosscrawler_attack"); }

void Crosscrawler::AttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::AttackEnd(const StateInfo& _Info) {}


void Crosscrawler::StunStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("ENEMY_STUNT.wav");
    SoundPlayer_.Volume(0.3f);

    MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
    MetaRenderer_->ChangeMetaAnimation("crosscrawler_stun_anim");

    BodyCollider_->ChangeOrder(COLLISIONORDER::MonsterBody);

    ExecutionCollider_->On();

    DetectCollider_->Off();
    AttackCollider_->Off();
}

void Crosscrawler::StunUpdate(float _DeltaTime, const StateInfo& _Info)
{
    bool IsExecution = ExecutionCheck();

    if (true == GameEngineInput::GetInst()->IsDownKey("Interaction") && true == IsExecution
        || true == GameEngineInput::GetInst()->IsDownButton("PenitentY") && true == IsExecution)
    {
        State_.ChangeState("Execution");
        return;
    }

    if (5.f < _Info.StateTime)
    {
        DetectCollider_->On();
        ExecutionCollider_->Off();
        SetHP(90);

        State_.ChangeState("Idle");
    }
}

void Crosscrawler::StunEnd(const StateInfo& _Info)
{
    UIRenderer_->Off();
    BodyCollider_->ChangeOrder(COLLISIONORDER::Monster);
}


void Crosscrawler::ExecutionStart(const StateInfo& _Info)
{
    Penitent::GetMainPlayer()->SetExecutionType(EXECUTIONTYPE::Crosscrawler);
    Penitent::GetMainPlayer()->ChangeState("Execution");
    Penitent::GetMainPlayer()->PlusTear(GetTear());

    DetectCollider_->Death();
    BodyCollider_->Death();
    AttackCollider_->Death();
    BloodEffect_->Death();
    MetaRenderer_->Death();

    SoundPlayer_ = GameEngineSound::SoundPlayControl("CROSSCRAWLER_EXECUTION.wav");
    SoundPlayer_.Volume(0.3f);

    Death(10.f);
}

void Crosscrawler::ExecutionUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::ExecutionEnd(const StateInfo& _Info) {}


void Crosscrawler::DeathStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("CROSSCRAWLER_DEATH.wav");
    SoundPlayer_.Volume(0.3f);

    MetaRenderer_->ChangeMetaAnimation("crosscrawler_death");
    MetaRenderer_->GetColorData().PlusColor = float4::ZERO;

    DetectCollider_->Death();
    BodyCollider_->Death();
    AttackCollider_->Death();

    Penitent::GetMainPlayer()->PlusTear(GetTear());
}

void Crosscrawler::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Crosscrawler::DeathEnd(const StateInfo& _Info) {}
