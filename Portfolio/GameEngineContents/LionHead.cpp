#include "PreCompile.h"
#include "LionHead.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

LionHead::LionHead() {}

LionHead::~LionHead() {}


void LionHead::Start()
{
    NormalMonster::Start();

    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("Lionhead_idle_anim");

        MetaRenderer_->CreateMetaAnimation(
            "Lionhead_idle_anim",
            {"Lionhead_idle_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("Lionhead_attack_anim");

        MetaRenderer_->CreateMetaAnimation(
            "Lionhead_attack_anim",
            {"Lionhead_attack_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        MetaRenderer_->AnimationBindFrame(
            "Lionhead_attack_anim",
            [&](const FrameAnimation_DESC& _Info)
            {
                if (1 == _Info.CurFrame)
                {
                    SoundPlayer_ = GameEngineSound::SoundPlayControl("LEON_START_ATTACK.wav");
                    SoundPlayer_.Volume(0.3f);
                }

                if (9 == _Info.CurFrame)
                {
                    SoundPlayer_ = GameEngineSound::SoundPlayControl("LEON_PREATTACK.wav");
                    SoundPlayer_.Volume(0.3f);
                }

                if (12 == _Info.CurFrame)
                {
                    AttackCollider_->On();

                    SoundPlayer_ = GameEngineSound::SoundPlayControl("LEON_HIT.wav");
                    SoundPlayer_.Volume(0.3f);
                }

                else if (13 == _Info.CurFrame)
                {
                    AttackCollider_->Off();
                }
            });

        MetaRenderer_->AnimationBindEnd("Lionhead_attack_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeMonsterState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("Lionhead_walk_anim");

        MetaRenderer_->CreateMetaAnimation(
            "Lionhead_walk_anim",
            {"Lionhead_walk_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("Lionhead_walk_backward_anim");

        MetaRenderer_->CreateMetaAnimation(
            "Lionhead_walk_backward_anim",
            {"Lionhead_walk_backward_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("Lionhead_death_anim");

        MetaRenderer_->CreateMetaAnimation(
            "Lionhead_death_anim",
            {"Lionhead_death_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindFrame("Lionhead_death_anim",
                                          [&](const FrameAnimation_DESC& _Info)
                                          {
                                              if (5 == _Info.CurFrame)
                                              {
                                                  BodyCollider_->Off();
                                                  AttackCollider_->Off();
                                                  DetectCollider_->Off();
                                              }
                                          });

        MetaRenderer_->AnimationBindEnd("Lionhead_death_anim", [&](const FrameAnimation_DESC& _Info) { Death(); });
    }

    MetaRenderer_->ChangeMetaAnimation("Lionhead_idle_anim");
    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);

    Gravity_ = CreateComponent<GravityComponent>();

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.99f, 0.7f, 0.6f, 0.25f});
    DetectCollider_->GetTransform().SetWorldScale({900.0f, 250.0f, 1.0f});
    DetectCollider_->GetTransform().SetWorldMove({0, 100.f});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::Monster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.99f, 0.7f, 0.6f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({30.0f, 250.0f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({0, 120.f});

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->ChangeOrder(COLLISIONORDER::Monster);
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.0f, 0.0f, 0.25f});
    AttackCollider_->GetTransform().SetWorldScale({250.0f, 100.0f, 1.0f});
    AttackCollider_->GetTransform().SetWorldMove({150.f, 0.f});
    AttackCollider_->Off(); 

    State_.CreateStateMember("Idle",
                             std::bind(&LionHead::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&LionHead::IdleStart, this, std::placeholders::_1),
                             std::bind(&LionHead::IdleEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Track",
                             std::bind(&LionHead::TrackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&LionHead::TrackStart, this, std::placeholders::_1),
                             std::bind(&LionHead::TrackEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Return",
                             std::bind(&LionHead::ReturnUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&LionHead::ReturnStart, this, std::placeholders::_1),
                             std::bind(&LionHead::ReturnEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Attack",
                             std::bind(&LionHead::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&LionHead::AttackStart, this, std::placeholders::_1),
                             std::bind(&LionHead::AttackEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Death",
                             std::bind(&LionHead::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&LionHead::DeathStart, this, std::placeholders::_1),
                             std::bind(&LionHead::DeathEnd, this, std::placeholders::_1));
    State_.ChangeState("Idle");

    SetSpeed(50.f);
    SetCrossroad(300.f);
    SetTear(300);

    PatrolStart_ = true;
    PatrolEnd_   = false;
}

void LionHead::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 10));
    Gravity_->SetActive(!IsGround_);

    if ("Death" != State_.GetCurStateStateName())
    {
        NormalMonster::DamageCheck(10.f, 75.f);
    }

    GameEngineDebug::OutPutString("LionHead State" + State_.GetCurStateStateName());
}

void LionHead::End() {}


void LionHead::IdleStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("Lionhead_idle_anim"); }

void LionHead::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (1.f >= _Info.StateTime)
    {
        return;
    }

    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, nullptr))
    {
        State_.ChangeState("Track");
    }

    else if (StartPos_.x > GetTransform().GetWorldPosition().x)
    {
        State_.ChangeState("Return");
    }
}

void LionHead::IdleEnd(const StateInfo& _Info) {}


void LionHead::ReturnStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("Lionhead_idle_anim");
    DetectCollider_->GetTransform().SetWorldScale({500.0f, 250.0f, 1.0f});
}

void LionHead::ReturnUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (1.5f >= _Info.StateTime)
    {
        return;
    }

    else
    {
        MetaRenderer_->ChangeMetaAnimation("Lionhead_walk_backward_anim");
    }

    GetTransform().SetWorldMove(float4::RIGHT * Speed_ * _DeltaTime);

    if (StartPos_.x <= GetTransform().GetWorldPosition().x)
    {
        State_.ChangeState("Idle");
    }

    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&LionHead::LookAtPlayer, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Track");
    }
}

void LionHead::ReturnEnd(const StateInfo& _Info)
{
    DetectCollider_->GetTransform().SetWorldScale({1000.0f, 250.0f, 1.0f});
}


void LionHead::TrackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("Lionhead_walk_anim");
    DetectCollider_->GetTransform().SetWorldScale({2000.0f, 250.0f, 1.0f});
}

void LionHead::TrackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true
        == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 100, -(GetTransform().GetWorldPosition().y - 10)))
    {
        GetTransform().SetWorldMove(float4::LEFT * Speed_ * _DeltaTime);
    }

    else
    {
        State_.ChangeState("Return");
        return;
    }

    if (false
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&LionHead::LookAtPlayer, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Return");
        return;
    }

    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&LionHead::CrossroadCheck, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Attack");
    }
}

void LionHead::TrackEnd(const StateInfo& _Info)
{
    DetectCollider_->GetTransform().SetWorldScale({1000.0f, 250.0f, 1.0f});
}


void LionHead::AttackStart(const StateInfo& _Info)
{
    BodyCollider_->GetTransform().SetWorldScale({30.0f, 150.0f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({0, -50.f});

    MetaRenderer_->ChangeMetaAnimation("Lionhead_idle_anim");
}

void LionHead::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (1.f <= _Info.StateTime)
    {
        MetaRenderer_->ChangeMetaAnimation("Lionhead_attack_anim");
    }
}

void LionHead::AttackEnd(const StateInfo& _Info)
{
    BodyCollider_->GetTransform().SetWorldScale({30.0f, 250.0f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({0, 50.f});
}


void LionHead::DeathStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("Lionhead_death_anim");
    MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};

    SoundPlayer_ = GameEngineSound::SoundPlayControl("LEON_DEATH.wav");
    SoundPlayer_.Volume(0.3f);

    Penitent::GetMainPlayer()->PlusTear(GetTear());
}

void LionHead::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void LionHead::DeathEnd(const StateInfo& _Info) {}