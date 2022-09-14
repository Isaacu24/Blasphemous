#include "PreCompile.h"
#include "ShieldMaiden.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"
#include "BlockEffect.h"

namespace SHIELD_MAIDEN
{
    inline const char* IDLE = "TEST";
}

ShieldMaiden::ShieldMaiden()
    : NextState_("Patrol")
{}

ShieldMaiden::~ShieldMaiden() {}


void ShieldMaiden::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldandsword_idle");

        MetaRenderer_->CreateMetaAnimation(
            "shieldandsword_idle",
            {"shieldandsword_idle.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldMaiden_walking_anim");

        MetaRenderer_->CreateMetaAnimation(
            "shieldMaiden_walking_anim",
            {"shieldMaiden_walking_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldMaiden_attack");

        MetaRenderer_->CreateMetaAnimation(
            "shieldMaiden_attack",
            {"shieldMaiden_attack.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);


        MetaRenderer_->AnimationBindFrame("shieldMaiden_attack",
                                          [&](const FrameAnimation_DESC& _Info)
                                          {
                                              if (5 == _Info.CurFrame)
                                              {
                                                  AttackCollider_->On();
                                              }

                                              else if (6 == _Info.CurFrame)
                                              {
                                                  AttackCollider_->Off();
                                              }
                                          });

        MetaRenderer_->AnimationBindEnd("shieldMaiden_attack",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            State_.ChangeState("Idle");
                                            NextState_ = "Track";
                                        });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldMaiden_parryReaction");

        MetaRenderer_->CreateMetaAnimation(
            "shieldMaiden_parryReaction",
            {"shieldMaiden_parryReaction.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.12f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("shieldMaiden_parryReaction",
                                        [&](const FrameAnimation_DESC& _Info) { State_.ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldMaiden_stun");

        MetaRenderer_->CreateMetaAnimation(
            "shieldMaiden_stun",
            {"shieldMaiden_stun.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldandsword_death");

        MetaRenderer_->CreateMetaAnimation(
            "shieldandsword_death",
            {"shieldandsword_death.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindFrame("shieldandsword_death",
                                          [&](const FrameAnimation_DESC& _Info)
                                          {
                                              if (5 == _Info.CurFrame)
                                              {
                                                  BodyCollider_->Off();
                                                  AttackCollider_->Off();
                                                  DetectCollider_->Off();
                                              }
                                          });

        MetaRenderer_->AnimationBindEnd("shieldandsword_death", [&](const FrameAnimation_DESC& _Info) { Death(); });
    }

    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_walking_anim");

    //해당 몬스터는 피벗을 맞추면 틀어진다
    // MetaRenderer_->SetPivot(PIVOTMODE::BOT);

    Gravity_ = CreateComponent<GravityComponent>();

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.98f, 0.52f, 0.48f, 0.25f});
    DetectCollider_->GetTransform().SetWorldScale({400.0f, 200.0f, 1.0f});
    DetectCollider_->GetTransform().SetWorldMove({0, 100.f});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::Monster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.98f, 0.52f, 0.48f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({30.0f, 100.0f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({-20, 50.f});

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->ChangeOrder(COLLISIONORDER::MonsterAttack);
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.0f, 0.0f, 0.25f});
    AttackCollider_->GetTransform().SetWorldScale({100.0f, 150.0f, 1.0f});
    AttackCollider_->GetTransform().SetWorldMove({80, 50.f});
    AttackCollider_->Off();

    BloodEffect_ = GetLevel()->CreateActor<BloodSplatters>();
    BloodEffect_->GetRenderer()->Off();

    Effect_ = GetLevel()->CreateActor<BlockEffect>();
    Effect_->GetTransform().SetWorldScale({2, 2, 1});
    Effect_->Renderer_->Off();

    State_.CreateStateMember("Idle",
                             std::bind(&ShieldMaiden::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ShieldMaiden::IdleStart, this, std::placeholders::_1),
                             std::bind(&ShieldMaiden::IdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Patrol",
                             std::bind(&ShieldMaiden::PatrolUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ShieldMaiden::PatrolStart, this, std::placeholders::_1),
                             std::bind(&ShieldMaiden::PatrolEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Track",
                             std::bind(&ShieldMaiden::TrackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ShieldMaiden::TrackStart, this, std::placeholders::_1),
                             std::bind(&ShieldMaiden::TrackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Attack",
                             std::bind(&ShieldMaiden::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ShieldMaiden::AttackStart, this, std::placeholders::_1),
                             std::bind(&ShieldMaiden::AttackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Stun",
                             std::bind(&ShieldMaiden::StunUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ShieldMaiden::StunStart, this, std::placeholders::_1),
                             std::bind(&ShieldMaiden::StunEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "ParryReaction",
        std::bind(&ShieldMaiden::ParryReactionUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&ShieldMaiden::ParryReactionStart, this, std::placeholders::_1),
        std::bind(&ShieldMaiden::ParryReactionEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "Execution",
        std::bind(&ShieldMaiden::ExecutionUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&ShieldMaiden::ExecutionStart, this, std::placeholders::_1),
        std::bind(&ShieldMaiden::ExecutionEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&ShieldMaiden::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ShieldMaiden::DeathStart, this, std::placeholders::_1),
                             std::bind(&ShieldMaiden::DeathEnd, this, std::placeholders::_1));

    State_.ChangeState("Idle");

    SetSpeed(50.f);
    SetTear(15);

    SetCrossroad(100.f);

    PatrolStart_ = true;
    PatrolEnd_   = false;
}

void ShieldMaiden::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
    Gravity_->SetActive(!IsGround_);

    if ("Death" != State_.GetCurStateStateName() && "Stun" != State_.GetCurStateStateName()
        && "Execution" != State_.GetCurStateStateName())
    {
        DamageCheck();

        if (90 > GetHP())
        {
            State_.ChangeState("Stun");
        }
    }
}

void ShieldMaiden::End() {}


void ShieldMaiden::DamageCheck()
{
    if (false
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_                                  = false;
        MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
    }

    if (true == IsHit_)
    {
        return;
    }

    if (true == IsPlayerLeft_)
    {
        if (Dir_.CompareInt4D(float4::LEFT))
        {
            if (true
                == BodyCollider_->IsCollision(
                    CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
            {
                float4 EffectPos = GetTransform().GetWorldPosition();
                Effect_->GetTransform().SetWorldPosition(
                    {EffectPos.x + (Dir_.x * 60.f), EffectPos.y - 100.f, MonsterZ});

                Effect_->Renderer_->On();
            }

            return;
        }
    }

    else if (true == IsPlayerRight_)
    {
        if (Dir_.CompareInt4D(float4::RIGHT))
        {
            if (true
                == BodyCollider_->IsCollision(
                    CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
            {
                float4 EffectPos = GetTransform().GetWorldPosition();
                Effect_->GetTransform().SetWorldPosition(
                    {EffectPos.x + (Dir_.x * 10.f), EffectPos.y - 100.f, MonsterZ});

                Effect_->Renderer_->On();
            }

            return;
        }
    }

    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = true;
        MinusHP(30.f);

        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetTransform().SetWorldPosition(
            {BodyCollider_->GetTransform().GetWorldPosition().x + (-(Dir_.x) * 30.f),
             BodyCollider_->GetTransform().GetWorldPosition().y,
             PlayerEffectZ});
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

        MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
    }

    if (0 >= GetHP())
    {
        State_.ChangeState("Death");
    }
}


void ShieldMaiden::PatrolMoveX(float _DeltaTime)
{
    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        if (true
            == RightObstacleCheck(GetTransform().GetWorldPosition().x + 70, -(GetTransform().GetWorldPosition().y)))
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
        if (true == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 70, -(GetTransform().GetWorldPosition().y)))
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


void ShieldMaiden::IdleStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("shieldandsword_idle");
    IdleTime_ = 0;
}

void ShieldMaiden::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    DetectCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Player,
        CollisionType::CT_OBB2D,
        std::bind(&ShieldMaiden::DetectPlayer, this, std::placeholders::_1, std::placeholders::_2));

    IdleTime_ += _DeltaTime;

    if (2.5f <= IdleTime_)
    {
        State_.ChangeState(NextState_);
    }
}

void ShieldMaiden::IdleEnd(const StateInfo& _Info) {}

void ShieldMaiden::PatrolStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_walking_anim");

    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        GetTransform().PixLocalPositiveX();
    }

    else if (false == PatrolStart_ && true == PatrolEnd_)
    {
        GetTransform().PixLocalNegativeX();
    }
}

void ShieldMaiden::PatrolUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, nullptr))
    {
        State_.ChangeState("Track");
        return;
    }

    PatrolMoveX(_DeltaTime);
}

void ShieldMaiden::PatrolEnd(const StateInfo& _Info) {}


void ShieldMaiden::TrackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_walking_anim");
}

void ShieldMaiden::TrackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    DetectCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Player,
        CollisionType::CT_OBB2D,
        std::bind(&ShieldMaiden::DetectPlayer, this, std::placeholders::_1, std::placeholders::_2));

    if (false
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&ShieldMaiden::DetectPlayer, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Patrol");
        return;
    }

    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&ShieldMaiden::CrossroadCheck, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Attack");
        return;
    }

    if (true == IsPlayerLeft_)
    {
        Dir_ = float4::LEFT;
        GetTransform().PixLocalNegativeX();
        GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
    }

    else if (true == IsPlayerRight_)
    {
        Dir_ = float4::RIGHT;
        GetTransform().PixLocalPositiveX();
        GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
    }
}

void ShieldMaiden::TrackEnd(const StateInfo& _Info) {}


void ShieldMaiden::AttackStart(const StateInfo& _Info)
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

    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_attack");
}

void ShieldMaiden::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true
        == AttackCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerParry, CollisionType::CT_OBB2D, nullptr))
    {
        State_.ChangeState("ParryReaction");
        Penitent::GetMainPlayer()->ParrySuccess();
    }
}

void ShieldMaiden::AttackEnd(const StateInfo& _Info) { AttackCollider_->Off(); }


void ShieldMaiden::ParryReactionStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_parryReaction");
}

void ShieldMaiden::ParryReactionUpdate(float _DeltaTime, const StateInfo& _Info) {}

void ShieldMaiden::ParryReactionEnd(const StateInfo& _Info) {}


void ShieldMaiden::StunStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_stun");
    MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};

    DetectCollider_->Off();
    BodyCollider_->Off();
    AttackCollider_->Off();
}

void ShieldMaiden::StunUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == GameEngineInput::GetInst()->IsDownKey("FreeCamera"))
    {
        State_.ChangeState("Execution");
        return;
    }

    if (5.f < _Info.StateTime)
    {
        DetectCollider_->On();
        BodyCollider_->On();
        State_.ChangeState("Idle");
    }
}

void ShieldMaiden::StunEnd(const StateInfo& _Info) {}


void ShieldMaiden::ExecutionStart(const StateInfo& _Info)
{
    Penitent::GetMainPlayer()->SetExecutionType(EXECUTIONTYPE::ShieldMaiden);
    Penitent::GetMainPlayer()->ChangeState("Execution");

    DetectCollider_->Death();
    BodyCollider_->Death();
    AttackCollider_->Death();

    Death();
}

void ShieldMaiden::ExecutionUpdate(float _DeltaTime, const StateInfo& _Info) {}

void ShieldMaiden::ExecutionEnd(const StateInfo& _Info) {}


void ShieldMaiden::DeathStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("shieldandsword_death");
    MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};

    Penitent::GetMainPlayer()->SerTear(GetTear());
}

void ShieldMaiden::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void ShieldMaiden::DeathEnd(const StateInfo& _Info) {}