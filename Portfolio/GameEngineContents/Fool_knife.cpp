#include "PreCompile.h"
#include "Fool_knife.h"

Fool_knife::Fool_knife() {}

Fool_knife::~Fool_knife() {}

void Fool_knife::Start()
{
    NormalMonster::Start();

    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("fool_idle_knife", {"fool_idle_knife.png", 0, 11, 0.1f, true});

    Renderer_->CreateFrameAnimationCutTexture("Fool_turn_knife", {"Fool_turn_knife.png", 0, 6, 0.07f, false});

    Renderer_->AnimationBindEnd("Fool_turn_knife",
                                [&](const FrameAnimation_DESC& _Info)
                                {
                                    if (false == IsPlayerLeft_ && false == IsPlayerRight_)
                                    {
                                        ChangeMonsterState("Patrol");
                                    }

                                    else
                                    {
                                        ChangeMonsterState("Track");
                                    }
                                });

    Renderer_->CreateFrameAnimationCutTexture("Fool_walk_knife", {"Fool_walk_knife.png", 0, 8, 0.1f, true});

    Renderer_->AnimationBindFrame("Fool_walk_knife",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      if (0 == _Info.CurFrame % 4)
                                      {
                                          SoundPlayer_ = GameEngineSound::SoundPlayControl("FOOL_FOOTSTEP_4.wav");
                                          SoundPlayer_.Volume(0.15f);
                                      }
                                  });

    Renderer_->CreateFrameAnimationCutTexture("Fool_hurt_knife", {"Fool_hurt_knife.png", 0, 8, 0.07f, false});

    Renderer_->AnimationBindEnd("Fool_hurt_knife",
                                [&](const FrameAnimation_DESC& _Info)
                                {
                                    if (0 >= GetHP())
                                    {
                                        State_.ChangeState("Death");
                                        return;
                                    }

                                    State_.ChangeState("Idle");
                                });

    Renderer_->CreateFrameAnimationCutTexture("Fool_death_knife", {"Fool_death_knife.png", 0, 13, 0.07f, false});
    Renderer_->AnimationBindEnd("Fool_death_knife", [&](const FrameAnimation_DESC& _Info) { Death(); });

    Renderer_->ChangeFrameAnimation("fool_idle_knife");

    Renderer_->GetTransform().SetWorldScale({400, 300});
    Renderer_->SetPivot(PIVOTMODE::BOT);

    Gravity_ = CreateComponent<GravityComponent>();

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    DetectCollider_->GetTransform().SetWorldScale({600.0f, 300.0f, 1.0f});
    DetectCollider_->GetTransform().SetWorldMove({0, 100});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::Monster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({50, 130.0f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({0, 100});

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->ChangeOrder(COLLISIONORDER::MonsterAttack);
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.0f, 0.0f, 0.5f});
    AttackCollider_->GetTransform().SetWorldScale({30.f, 20.0f, 1.0f});
    AttackCollider_->GetTransform().SetWorldMove({40, 130});

    State_.CreateStateMember("Idle",
                             std::bind(&Fool_knife::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Fool_knife::IdleStart, this, std::placeholders::_1),
                             std::bind(&Fool_knife::IdleEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Patrol",
                             std::bind(&Fool_knife::PatrolUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Fool_knife::PatrolStart, this, std::placeholders::_1),
                             std::bind(&Fool_knife::PatrolEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Track",
                             std::bind(&Fool_knife::TrackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Fool_knife::TrackStart, this, std::placeholders::_1),
                             std::bind(&Fool_knife::TrackEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Death",
                             std::bind(&Fool_knife::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Fool_knife::DeathStart, this, std::placeholders::_1),
                             std::bind(&Fool_knife::DeathEnd, this, std::placeholders::_1));
    State_.CreateStateMember(
        "PatrolTurn",
        std::bind(&Fool_knife::PatrolTurnUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&Fool_knife::PatrolTurnStart, this, std::placeholders::_1),
        std::bind(&Fool_knife::PatrolTurnEnd, this, std::placeholders::_1));
    State_.CreateStateMember(
        "TrackTurn",
        std::bind(&Fool_knife::TrackTurnUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&Fool_knife::TrackTurnStart, this, std::placeholders::_1),
        std::bind(&Fool_knife::TrackTurnEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Hurt",
                             std::bind(&Fool_knife::HurtUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Fool_knife::HurtStart, this, std::placeholders::_1),
                             std::bind(&Fool_knife::HurtEnd, this, std::placeholders::_1));
    State_.ChangeState("Patrol");

    SetSpeed(70.f);

    SetTear(5);

    PatrolStart_ = true;
}

void Fool_knife::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    DamageCheck();

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 35));
    Gravity_->SetActive(!IsGround_);

    GameEngineDebug::OutPutString("Fool: " + State_.GetCurStateStateName());
}

void Fool_knife::End() {}

void Fool_knife::DamageCheck()
{
    if ("Death" != State_.GetCurStateStateName() && "Hurt" != State_.GetCurStateStateName())
    {
        if (false
            == BodyCollider_->IsCollision(
                CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
        {
            IsHit_ = false;

            Renderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
        }

        if (true == IsHit_)
        {
            return;
        }

        if (true
            == BodyCollider_->IsCollision(
                CollisionType::CT_OBB2D,
                COLLISIONORDER::PlayerAttack,
                CollisionType::CT_OBB2D,
                std::bind(&Fool_knife::ReverseBloodEffect, this, std::placeholders::_1, std::placeholders::_2)))
        {
            MinusHP(25.f);
            IsHit_ = true;
            State_.ChangeState("Hurt");

            Renderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};

            float4 HitPos = BodyCollider_->GetTransform().GetWorldPosition();

            BloodEffect_->GetRenderer()->On();
            BloodEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
            BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

            HitEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
            HitEffect_->ShowHitEffet();
        }

        else if (true
                 == BodyCollider_->IsCollision(
                     CollisionType::CT_OBB2D,
                     COLLISIONORDER::PlayerRangeAttack,
                     CollisionType::CT_OBB2D,
                     std::bind(&Fool_knife::ReverseBloodEffect, this, std::placeholders::_1, std::placeholders::_2)))
        {
            IsHit_ = true;

            Renderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};

            float4 HitPos = BodyCollider_->GetTransform().GetWorldPosition();

            BloodEffect_->GetRenderer()->On();
            BloodEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
            BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

            HitEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
            HitEffect_->ShowRangeHitEffect();

            MinusHP(7.f);
        }

        if (0 >= GetHP())
        {
            State_.ChangeState("Death");
        }
    }
}


void Fool_knife::PatrolMoveX(float _DeltaTime)
{
    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        if (true
            == RightObstacleCheck(GetTransform().GetWorldPosition().x + 50,
                                  -(GetTransform().GetWorldPosition().y + 35)))
        {
            GetTransform().SetWorldMove(float4::RIGHT * Speed_ * _DeltaTime);
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
        if (true
            == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 50, -(GetTransform().GetWorldPosition().y + 35)))
        {
            GetTransform().SetWorldMove(float4::LEFT * Speed_ * _DeltaTime);
        }

        else
        {
            State_.ChangeState("PatrolTurn");

            PatrolStart_ = true;
            PatrolEnd_   = false;
        }
    }
}


void Fool_knife::IdleStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("fool_idle_knife"); }

void Fool_knife::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
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
            std::bind(&Fool_knife::DetectPlayer, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Patrol");
        return;
    }

    if (true == IsPlayerLeft_)
    {
        if (true
            == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 50, -(GetTransform().GetWorldPosition().y + 35)))
        {
            State_.ChangeState("Track");
        }
    }

    else if (true == IsPlayerRight_)
    {
        if (true
            == RightObstacleCheck(GetTransform().GetWorldPosition().x + 50,
                                  -(GetTransform().GetWorldPosition().y + 35)))
        {
            State_.ChangeState("Track");
        }
    }
}

void Fool_knife::IdleEnd(const StateInfo& _Info) {}


void Fool_knife::PatrolStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("Fool_walk_knife");

    if (0 > GetTransform().GetLocalScale().x && true == PatrolStart_ && false == PatrolEnd_
        || 0 < GetTransform().GetLocalScale().x && false == PatrolStart_ && true == PatrolEnd_)
    {
        IsPlayerRight_ = false;
        IsPlayerLeft_  = false;

        State_.ChangeState("PatrolTurn");
    }
}

void Fool_knife::PatrolUpdate(float _DeltaTime, const StateInfo& _Info)
{
    PatrolMoveX(_DeltaTime);

    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&Fool_knife::TrackPlayer, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Track");
    }
}

void Fool_knife::PatrolEnd(const StateInfo& _Info) {}


void Fool_knife::TrackStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("Fool_walk_knife"); }

void Fool_knife::TrackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&Fool_knife::TrackPlayer, this, std::placeholders::_1, std::placeholders::_2)))
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
                == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 50,
                                     -(GetTransform().GetWorldPosition().y + 35)))
            {
                State_.ChangeState("Idle");
                return;
            }

            GetTransform().SetWorldMove(float4::LEFT * Speed_ * _DeltaTime);
        }

        else if (true == IsPlayerRight_)
        {
            if (false
                == RightObstacleCheck(GetTransform().GetWorldPosition().x + 50,
                                      -(GetTransform().GetWorldPosition().y + 35)))
            {
                State_.ChangeState("Idle");
                return;
            }

            GetTransform().SetWorldMove(float4::RIGHT * Speed_ * _DeltaTime);
        }
    }

    else
    {
        State_.ChangeState("Idle");
    }
}

void Fool_knife::TrackEnd(const StateInfo& _Info) {}


void Fool_knife::HurtStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("Fool_hurt_knife");

    SoundPlayer_ = GameEngineSound::SoundPlayControl("FOOL_DEATH_2.wav");
    SoundPlayer_.Volume(0.15f);
}

void Fool_knife::HurtUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (0.2f < _Info.StateTime)
    {
        Renderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
    }
}

void Fool_knife::HurtEnd(const StateInfo& _Info) {}


void Fool_knife::PatrolTurnStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("Fool_turn_knife"); }

void Fool_knife::PatrolTurnUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Fool_knife::PatrolTurnEnd(const StateInfo& _Info)
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


void Fool_knife::TrackTurnStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("Fool_turn_knife"); }

void Fool_knife::TrackTurnUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Fool_knife::TrackTurnEnd(const StateInfo& _Info)
{
    if (true == IsPlayerRight_)
    {
        GetTransform().PixLocalPositiveX();
    }

    else if (true == IsPlayerLeft_)
    {
        GetTransform().PixLocalNegativeX();
    }
}

void Fool_knife::DeathStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("FOOL_DEATH_1.wav");

    BodyCollider_->Off();
    DetectCollider_->Off();
    AttackCollider_->Off();

    Renderer_->ChangeFrameAnimation("Fool_death_knife");
    Renderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};

    Penitent::GetMainPlayer()->PlusTear(GetTear());
}

void Fool_knife::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Fool_knife::DeathEnd(const StateInfo& _Info) {}
