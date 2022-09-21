#include "PreCompile.h"
#include "ElderBrother.h"
#include "GravityActor.h"
#include "BloodSplatters.h"
#include "HardLandingEffect.h "

namespace
{
    const char*                ELDER_ATTACK_NAME = "elderBrother_attack";
    constexpr std::string_view TEST              = "TEST";
}  // namespace

ElderBrother::ElderBrother()
    : Flow_(APPEARFLOW::Attack)
    , JumpForce_(500.f)
{}

ElderBrother::~ElderBrother() {}

void ElderBrother::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("elderBrother_idle", {"elderBrother_idle.png", 0, 9, 0.1f, true});

    Renderer_->CreateFrameAnimationCutTexture("elderBrother_jumpStart", {"elderBrother_jump.png", 0, 8, 0.1f, false});

    Renderer_->CreateFrameAnimationCutTexture("elderBrother_jumpStart_event",
                                              {"elderBrother_jump.png", 0, 8, 0.08f, false});

    Renderer_->AnimationBindEnd(
        "elderBrother_jumpStart",
        [&](const FrameAnimation_DESC& _Info)
        {
            IsJump_ = true;
            Renderer_->ChangeFrameAnimation("elderBrother_jump");

            LandEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{0, 50});
            LandEffect_->GetRenderer()->On();
            LandEffect_->GetRenderer()->ChangeMetaAnimation("penitent_hardlanding_effects");
        });

    Renderer_->AnimationBindEnd("elderBrother_jumpStart_event",
                                [&](const FrameAnimation_DESC& _Info)
                                {
                                    Flow_ = APPEARFLOW::Jump;
                                    Renderer_->CurAnimationReset();

                                    IsJump_ = true;
                                    Renderer_->ChangeFrameAnimation("elderBrother_jump");
                                });

    Renderer_->CreateFrameAnimationCutTexture("elderBrother_jump", {"elderBrother_jump.png", 9, 14, 0.07f, true});

    Renderer_->CreateFrameAnimationCutTexture("elderBrother_land", {"elderBrother_jump.png", 15, 24, 0.07f, false});
    Renderer_->CreateFrameAnimationCutTexture("elderBrother_land_event",
                                              {"elderBrother_jump.png", 15, 24, 0.08f, false});

    Renderer_->AnimationBindFrame(
        "elderBrother_land",
        [&](const FrameAnimation_DESC& _Info)
        {
            if (2 == _Info.CurFrame)
            {
                JumpEffecter_->SetCreatePos(GetTransform().GetWorldPosition() + float4{0, 75});
                JumpEffecter_->CreateEffect();
            }
        });

    Renderer_->AnimationBindEnd("elderBrother_land", [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    Renderer_->AnimationBindEnd("elderBrother_land_event",
                                [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });

    Renderer_->CreateFrameAnimationCutTexture("elderBrother_attack", {"elderBrother_attack.png", 0, 23, 0.08f, false});

    Renderer_->AnimationBindFrame(
        "elderBrother_attack",
        [&](const FrameAnimation_DESC& _Info)
        {
            if (16 == _Info.CurFrame)
            {
                AffectChecker->Move();
                AffectChecker->On();

                AttackCollider_->On();
                AttackCollider_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()
                                                                 + float4{0.f, 100.f});
            }

            if (16 < _Info.CurFrame)
            {
                if (nullptr == AffectChecker)
                {
                    return;
                }

                float DirX = Dir_.NormalizeReturn().x;

                if (0 > DirX)
                {
                    AttackEffecter_->SetCreatePos(AffectChecker->GetTransform().GetWorldPosition() + float4{0, 75.f});
                    AttackEffecter_->SetDir(-1);
                    AttackEffecter_->CreateEffect();
                }

                else
                {
                    AttackEffecter_->SetCreatePos(AffectChecker->GetTransform().GetWorldPosition() + float4{0, 75.f});
                    AttackEffecter_->SetDir(1);
                    AttackEffecter_->CreateEffect();
                }

                AttackCollider_->GetTransform().SetWorldMove({Dir_.x * 100.f, 0.f});
            }

            if (22 == _Info.CurFrame)
            {
                AttackCollider_->Off();
            }
        });

    Renderer_->AnimationBindEnd("elderBrother_attack", [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });

    Renderer_->CreateFrameAnimationCutTexture("elderBrother_attack_event",
                                              {"elderBrother_attack.png", 0, 23, 0.08f, false});

    Renderer_->AnimationBindEnd("elderBrother_attack_event",
                                [&](const FrameAnimation_DESC& _Info)
                                {
                                    if (0 == AttackCount_)
                                    {
                                        ++AttackCount_;
                                        Flow_ = APPEARFLOW::Attack;
                                    }

                                    else if (1 == AttackCount_)
                                    {
                                        Flow_ = APPEARFLOW::JumpStart;
                                    }

                                    Renderer_->CurAnimationReset();
                                });

    Renderer_->CreateFrameAnimationCutTexture("elderBrother_death", {"elderBrother_death.png", 0, 48, 0.07f, false});
    Renderer_->AnimationBindFrame("elderBrother_death",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      if (3 == _Info.CurFrame)
                                      {
                                          BodyCollider_->Off();
                                          DetectCollider_->Off();
                                          AttackCollider_->Off();
                                      }
                                  });

    Renderer_->AnimationBindEnd("elderBrother_death",
                                [&](const FrameAnimation_DESC& _Info)
                                {
                                    Penitent::GetMainPlayer()->BossDeathUIOn(1);
                                    DeathEventOn_ = true;
                                });

    Renderer_->GetTransform().SetWorldScale({1100, 600});
    Renderer_->SetPivot(PIVOTMODE::BOT);
    Renderer_->GetTransform().PixLocalNegativeX();

    AttackEffecter_ = GetLevel()->CreateActor<AttackCorpseEffecter>();
    JumpEffecter_   = GetLevel()->CreateActor<JumpCorpseEffecter>();

    AffectChecker = GetLevel()->CreateActor<GravityActor>(ACTORORDER::Monster);
    AffectChecker->Off();

    State_.CreateStateMember("Appear",
                             std::bind(&ElderBrother::AppearUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::AppearStart, this, std::placeholders::_1),
                             std::bind(&ElderBrother::AppearEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Idle",
                             std::bind(&ElderBrother::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::IdleStart, this, std::placeholders::_1),
                             std::bind(&ElderBrother::IdleEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Jump",
                             std::bind(&ElderBrother::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::JumpStart, this, std::placeholders::_1),
                             std::bind(&ElderBrother::JumpEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Fall",
                             std::bind(&ElderBrother::FallUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::FallStart, this, std::placeholders::_1),
                             std::bind(&ElderBrother::FallEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Land",
                             std::bind(&ElderBrother::LandUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::LandStart, this, std::placeholders::_1),
                             std::bind(&ElderBrother::LandEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Attack",
                             std::bind(&ElderBrother::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::AttackStart, this, std::placeholders::_1),
                             std::bind(&ElderBrother::AttackEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Death",
                             std::bind(&ElderBrother::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::DeathStart, this, std::placeholders::_1),
                             std::bind(&ElderBrother::DeathEnd, this, std::placeholders::_1));

    State_.ChangeState("Appear");

    Gravity_ = CreateComponent<GravityComponent>();

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->GetTransform().SetWorldScale({3000.0f, 1500.0f});
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB, float4{1.0f, 1.0f, 1.0f, 0.25f});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
    BodyCollider_->GetTransform().SetWorldScale({100.0f, 200.0f});
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB, float4{1.0f, 0.91f, 0.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldMove({0, 200});

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->ChangeOrder(COLLISIONORDER::BossMonsterAttack);
    AttackCollider_->GetTransform().SetWorldScale({100.0f, 100.0f});
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB, float4{1.0f, 1.0f, 1.0f, 0.25f});
    AttackCollider_->Off();

    Renderer_->GetColorData().MulColor  = float4::ZERO;
    Renderer_->GetColorData().PlusColor = float4{0.18f, 0.18f, 0.21f, 1.0f};

    BossUI_ = GetLevel()->CreateActor<BossUI>();
    BossUI_->SetBossMonster(this);
    BossUI_->SetBossUI();
    BossUI_->SetBossName("Ä§¹¬ÇÏ´Â ºñÅºÀÇ ÆÄ¼ö²Û");
    BossUI_->AllOff();

    BloodEffect_ = GetLevel()->CreateActor<BloodSplatters>();
    BloodEffect_->SetScale(200, 200);
    BloodEffect_->GetRenderer()->Off();

    LandEffect_ = GetLevel()->CreateActor<HardLandingEffect>();
    LandEffect_->GetTransform().SetWorldScale({2.5f, 2.5f, 1});
    LandEffect_->GetRenderer()->Off();
}

void ElderBrother::Update(float _DeltaTime)
{
    BossMonster::Update(_DeltaTime);

    State_.Update(_DeltaTime);

    if (true == GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 59.f)))
    {
        if (true == UphillRoadCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 60.f)))
        {
            GetTransform().SetWorldMove(float4::UP);
        }
    }

    if ("Death" == State_.GetCurStateStateName() || "Appear" == State_.GetCurStateStateName())
    {
        return;
    }

    DamageCheck();
}

void ElderBrother::End() {}

void ElderBrother::DamageCheck()
{
    if (false
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;

        Renderer_->GetColorData().MulColor = float4{1.f, 1.f, 1.f, 1.0f};
    }

    if (true == IsHit_)
    {
        return;
    }

    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = true;

        Renderer_->GetColorData().MulColor = float4{1.5f, 1.5f, 1.5f, 1.0f};

        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetTransform().SetWorldPosition(
            {BodyCollider_->GetTransform().GetWorldPosition().x + (-(Dir_.x) * 75.f),
             BodyCollider_->GetTransform().GetWorldPosition().y,
             PlayerEffectZ});
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplatters");

        MinusHP(5.f);
    }

    if (0 >= GetHP())
    {
        State_.ChangeState("Death");
    }
}

void ElderBrother::AppearStart(const StateInfo& _Info)
{
    JumpForce_ = 200.f;
    Renderer_->ChangeFrameAnimation("elderBrother_idle");
}

void ElderBrother::AppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (false == EventOn_)
    {
        return;
    }

    AppearTime_ += _DeltaTime;

    if (3.f > AppearTime_)
    {
        return;
    }

    switch (Flow_)
    {
        case APPEARFLOW::Attack:
            Renderer_->ChangeFrameAnimation("elderBrother_attack_event");
            break;
        case APPEARFLOW::JumpStart:
            Renderer_->ChangeFrameAnimation("elderBrother_jumpStart_event");
            break;
        case APPEARFLOW::Jump:
            JumpForce_.y -= _DeltaTime * 200.f;
            Dir_ = GetTransform().GetUpVector() * 20.f;
            Dir_ += GetTransform().GetLeftVector() * 3.f;

            GameEngineDebug::OutPutString(std::to_string(GetTransform().GetWorldPosition().y));

            Gravity_->SetActive(!IsGround_);
            GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);

            if (0.f < GetTransform().GetWorldPosition().y)
            {
                Renderer_->GetColorData().MulColor = float4::ONE;
                Renderer_->GetColorData().PlusColor = float4::ZERO;

                GetTransform().SetWorldPosition(
                    {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, BossMonsterZ});

                Flow_ = APPEARFLOW::Fall;
            }
            break;
        case APPEARFLOW::Fall:
            JumpForce_.y -= _DeltaTime * 350.f;
            Dir_ = GetTransform().GetUpVector() * 5.f;
            Dir_ += GetTransform().GetLeftVector() * 3.f;

            Gravity_->SetActive(!IsGround_);
            GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);

            if (true == IsGround_)
            {
                Renderer_->ChangeFrameAnimation("elderBrother_land_event");
                Flow_ = APPEARFLOW::Appear;
            }
            break;
        case APPEARFLOW::Appear:
            BossUI_->AllOn();
            BossEvent_ = true;
            break;
    }
}

void ElderBrother::AppearEnd(const StateInfo& _Info) { AppearTime_ = 0.f; }


void ElderBrother::IdleStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("elderBrother_idle");
    Distance_ = 0.f;
}

void ElderBrother::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    DecideTime_ += _DeltaTime;

    if (1.5f > DecideTime_)
    {
        return;
    }

    DetectCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Player,
        CollisionType::CT_OBB2D,
        std::bind(&ElderBrother::DetectPlayer, this, std::placeholders::_1, std::placeholders::_2));

    if (500.f >= Distance_ && 2.f <= DecideTime_)
    {
        int Value = Random_.RandomInt(0, 2);

        if (0 == Value || 1 == Value)
        {
            State_.ChangeState("Attack");
            return;
        }

        else if (2 == Value)
        {
            State_.ChangeState("Jump");
            return;
        }
    }

    else if (500.f < Distance_)
    {
        State_.ChangeState("Jump");
    }

    Gravity_->SetActive(!IsGround_);
}

void ElderBrother::IdleEnd(const StateInfo& _Info) { DecideTime_ = 0.f; }


void ElderBrother::JumpStart(const StateInfo& _Info)
{
    IsJump_ = false;

    Alpha_     = 0.f;
    JumpForce_ = 300.f;

    Renderer_->ChangeFrameAnimation("elderBrother_jumpStart");
}


void ElderBrother::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (false == IsJump_)
    {
        return;
    }

    JumpForce_.y -= _DeltaTime * 500.f;
    Dir_ = GetTransform().GetUpVector() * 10.f;

    if (0 > JumpForce_.y)
    {
        ChangeState("Fall");
        return;
    }

    Alpha_ += _DeltaTime * 0.1f;

    if (1 < Alpha_)
    {
        Alpha_ = 1.f;
    }

    float4 LerpPos = float4::LerpLimit(GetTransform().GetWorldPosition(), Target_, Alpha_);
    GetTransform().SetWorldPosition({LerpPos.x, LerpPos.y, BossMonsterZ});

    Gravity_->SetActive(!IsGround_);
    GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);
}

void ElderBrother::JumpEnd(const StateInfo& _Info) {}


void ElderBrother::FallStart(const StateInfo& _Info) {}

void ElderBrother::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpForce_.y -= _DeltaTime * 250.f;
    Dir_ = GetTransform().GetUpVector() * 10.f;

    Gravity_->SetActive(!IsGround_);
    GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);

    if (true == IsGround_)
    {
        ChangeState("Land");
    }

    if (false == IsJump_)
    {
        return;
    }

    Alpha_ += _DeltaTime * 0.1f;

    if (1 < Alpha_)
    {
        Alpha_ = 1.f;
    }

    float4 LerpPos = float4::LerpLimit(GetTransform().GetWorldPosition(), Target_, Alpha_);
    GetTransform().SetWorldPosition({LerpPos.x, LerpPos.y, BossMonsterZ});

    float4 Distance = Target_ - GetTransform().GetWorldPosition();

    if (150.f >= Distance.y)
    {
        IsJump_ = false;
    }
}

void ElderBrother::FallEnd(const StateInfo& _Info) {}


void ElderBrother::LandStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("elderBrother_land");

    LandEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{0, 50});
    LandEffect_->GetRenderer()->On();
    LandEffect_->GetRenderer()->ChangeMetaAnimation("penitent_hardlanding_effects");
}

void ElderBrother::LandUpdate(float _DeltaTime, const StateInfo& _Info) { Gravity_->SetActive(!IsGround_); }

void ElderBrother::LandEnd(const StateInfo& _Info) {}


void ElderBrother::AttackStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("elderBrother_attack");

    AffectChecker->SetGround(ColMap_);
    AffectChecker->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
    AffectChecker->SetDirection(Dir_);
    AffectChecker->Off();
}

void ElderBrother::AttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void ElderBrother::AttackEnd(const StateInfo& _Info) {}


void ElderBrother::DeathStart(const StateInfo& _Info)
{
    BossUI_->AllOff();

    Renderer_->ChangeFrameAnimation("elderBrother_death");

    BossDeathEvent();
}

void ElderBrother::DeathUpdate(float _DeltaTime, const StateInfo& _Info) { Gravity_->SetActive(!IsGround_); }

void ElderBrother::DeathEnd(const StateInfo& _Info)
{
    AttackEffecter_->Death();
    JumpEffecter_->Death();
}


//Ãæµ¹
bool ElderBrother::DetectPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
    {
        Dir_.x = 1;
        BloodEffect_->GetTransform().PixLocalNegativeX();
        Renderer_->GetTransform().PixLocalPositiveX();
    }

    else
    {
        Dir_.x = -1;
        BloodEffect_->GetTransform().PixLocalPositiveX();
        Renderer_->GetTransform().PixLocalNegativeX();
    }

    Distance_ = abs(_This->GetTransform().GetWorldPosition().x - _Other->GetTransform().GetWorldPosition().x);
    Target_   = _Other->GetTransform().GetWorldPosition();

    return true;
}