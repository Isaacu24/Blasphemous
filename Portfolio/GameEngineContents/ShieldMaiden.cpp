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
    NormalMonster::Start();

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

        MetaRenderer_->AnimationBindFrame("shieldMaiden_walking_anim",
                                          [&](const FrameAnimation_DESC& _Info)
                                          {
                                              if (0 == _Info.CurFrame % 5)
                                              {
                                                  SoundPlayer_
                                                      = GameEngineSound::SoundPlayControl("SHIELD_ENEMY_WALK_1.wav");
                                                  SoundPlayer_.Volume(0.05f);
                                              }
                                          });
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
                                                  SoundPlayer_
                                                      = GameEngineSound::SoundPlayControl("SHIELD_ENEMY_ATTACK.wav");
                                                  SoundPlayer_.Volume(0.05f);

                                                  AttackCollider_->On();

                                                  if (true == Penitent::GetMainPlayer()->GetParryOn())
                                                  {
                                                      State_.ChangeState("ParryReaction");
                                                      Penitent::GetMainPlayer()->ParrySuccess();
                                                  }
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
                                        [&](const FrameAnimation_DESC& _Info)
                                        { MetaRenderer_->ChangeMetaAnimation("shieldMaiden_parryReactionToIdle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldMaiden_parryReactionToIdle");

        MetaRenderer_->CreateMetaAnimation(
            "shieldMaiden_parryReactionToIdle",
            {"shieldMaiden_parryReactionToIdle.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.12f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("shieldMaiden_parryReactionToIdle",
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
    DetectCollider_->GetTransform().SetWorldScale({300.0f, 200.0f, 1.0f});
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

    BlockEffect_ = GetLevel()->CreateActor<BlockEffect>();
    BlockEffect_->GetTransform().SetWorldScale({2, 2, 1});
    BlockEffect_->Renderer_->Off();

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

    if ("Death" != State_.GetCurStateStateName() && "Execution" != State_.GetCurStateStateName())
    {
        if (90 > GetHP() && "Stun" != State_.GetCurStateStateName())
        {
            State_.ChangeState("Stun");
            return;
        }

        DamageCheck();
    }

    GameEngineDebug::OutPutString("ShieldMaiden State : " + State_.GetCurStateStateName());
}

void ShieldMaiden::End() {}


void ShieldMaiden::DamageCheck()
{
    if (false
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;

        MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
    }

    if (true == IsHit_)
    {
        return;
    }

    //패링에 당한 상태가 아닐 경우
    if ("ParryReaction" != State_.GetCurStateStateName() && "Stun" != State_.GetCurStateStateName())
    {
        if (true
            == BodyCollider_->IsCollision(
                CollisionType::CT_OBB2D,
                COLLISIONORDER::PlayerRangeAttack,
                CollisionType::CT_OBB2D,
                std::bind(&ShieldMaiden::RangeAttackCheck, this, std::placeholders::_1, std::placeholders::_2)))
        {
            float4 EffectPos = GetTransform().GetWorldPosition();
            BlockEffect_->GetTransform().SetWorldPosition(
                {EffectPos.x + (Dir_.x * 50.f), EffectPos.y - 100.f, MonsterZ});

            BlockEffect_->Renderer_->On();
            return;
        }

        if (true == IsPlayerLeft_ && Dir_.CompareInt4D(float4::LEFT))
        {
            if (true
                == BodyCollider_->IsCollision(
                    CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
            {
                float4 EffectPos = GetTransform().GetWorldPosition();
                BlockEffect_->GetTransform().SetWorldPosition(
                    {EffectPos.x + (Dir_.x * 50.f), EffectPos.y - 100.f, MonsterZ});

                BlockEffect_->Renderer_->On();
            }

            return;
        }

        else if (true == IsPlayerRight_ && Dir_.CompareInt4D(float4::RIGHT))
        {
            if (true
                == BodyCollider_->IsCollision(
                    CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
            {
                float4 EffectPos = GetTransform().GetWorldPosition();
                BlockEffect_->GetTransform().SetWorldPosition(
                    {EffectPos.x + (Dir_.x * 10.f), EffectPos.y - 100.f, MonsterZ});

                BlockEffect_->Renderer_->On();
            }

            return;
        }
    }

    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::PlayerAttack,
            CollisionType::CT_OBB2D,
            std::bind(&ShieldMaiden::ReverseBloodEffect, this, std::placeholders::_1, std::placeholders::_2)))
    {
        IsHit_ = true;
        MinusHP(30.f);

        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetTransform().SetWorldPosition(
            {BodyCollider_->GetTransform().GetWorldPosition().x + (-(Dir_.x) * 30.f),
             BodyCollider_->GetTransform().GetWorldPosition().y,
             PlayerEffectZ});
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

        float4 HitPos = BodyCollider_->GetTransform().GetWorldPosition();
        HitEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
        HitEffect_->ShowHitEffet();

        MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
    }

    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::PlayerRangeAttack,
            CollisionType::CT_OBB2D,
            std::bind(&ShieldMaiden::ReverseBloodEffect, this, std::placeholders::_1, std::placeholders::_2)))
    {
        IsHit_ = true;

        MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};

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

bool ShieldMaiden::RangeAttackCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    float4 HitDir = GetTransform().GetWorldPosition() - _Other->GetTransform().GetWorldPosition();
    HitDir.Normalize();

    if (0 < Dir_.x)
    {
        if (0 > HitDir.x)
        {
            return true;
        }
    }

    if (0 > Dir_.x)
    {
        if (0 < HitDir.x)
        {
            return true;
        }
    }

    return false;
}


void ShieldMaiden::PatrolMoveX(float _DeltaTime)
{
    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        if (true
            == RightObstacleCheck(GetTransform().GetWorldPosition().x + 70, -(GetTransform().GetWorldPosition().y)))
        {
            Dir_ = float4::RIGHT;
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
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
            Dir_ = float4::LEFT;
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
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

void ShieldMaiden::AttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

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

    BodyCollider_->ChangeOrder(COLLISIONORDER::MonsterBody);

    ExecutionCollider_->On();

    DetectCollider_->Off();
    AttackCollider_->Off();
}

void ShieldMaiden::StunUpdate(float _DeltaTime, const StateInfo& _Info)
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

void ShieldMaiden::StunEnd(const StateInfo& _Info)
{
    BodyCollider_->ChangeOrder(COLLISIONORDER::Monster);
    UIRenderer_->Off();
}


void ShieldMaiden::ExecutionStart(const StateInfo& _Info)
{
    Penitent::GetMainPlayer()->SetExecutionType(EXECUTIONTYPE::ShieldMaiden);
    Penitent::GetMainPlayer()->ChangeState("Execution");

    DetectCollider_->Death();
    BodyCollider_->Death();
    AttackCollider_->Death();
    BloodEffect_->Death();
    MetaRenderer_->Death();
    UIRenderer_->Death();

    Penitent::GetMainPlayer()->PlusTear(GetTear());

    SoundPlayer_ = GameEngineSound::SoundPlayControl("SHIELD_MAIDEN_EXECUTION.wav");
    SoundPlayer_.Volume(0.05f);

    Death(10.f);
}

void ShieldMaiden::ExecutionUpdate(float _DeltaTime, const StateInfo& _Info) {}

void ShieldMaiden::ExecutionEnd(const StateInfo& _Info) {}


void ShieldMaiden::DeathStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("shieldandsword_death");
    MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};

    Penitent::GetMainPlayer()->PlusTear(GetTear());

    SoundPlayer_ = GameEngineSound::SoundPlayControl("SHIELD_ENEMY_DEATH.wav");
    SoundPlayer_.Volume(0.05f);
}

void ShieldMaiden::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void ShieldMaiden::DeathEnd(const StateInfo& _Info) {}