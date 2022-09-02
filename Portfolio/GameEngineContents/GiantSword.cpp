#include "PreCompile.h"
#include "GiantSword.h"
#include "Pontiff.h"

GiantSword::GiantSword() {}

GiantSword::~GiantSword() {}


void GiantSword::Start()
{
    EyeRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    EyeRenderer_->SetTexture("pontiff_giantSword_eyeGlobeSprite.png");
    EyeRenderer_->GetTransform().SetLocalScale({125, 400});
    EyeRenderer_->Off();

    IrisRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    IrisRenderer_->SetTexture("pontiff_giantSword_irisSprite.png");
    IrisRenderer_->GetTransform().SetLocalScale({125, 400});
    IrisRenderer_->SetPivot(PIVOTMODE::CUSTOM);
    IrisRenderer_->Off();

    Renderer_ = CreateComponent<GameEngineTextureRenderer>();

    Renderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_teleportOUT",
                                              {"pontiff_giantSword_teleportOUT.png", 0, 19, 0.1f, false});
    Renderer_->AnimationBindEnd("pontiff_giantSword_teleportOUT",
                                [&](const FrameAnimation_DESC&)
                                { Renderer_->SetTexture("pontiff_giantSword_swordSprite.png"); });

    Renderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_teleportIN",
                                              {"pontiff_giantSword_teleportIN.png", 0, 26, 0.1f, false});
    Renderer_->AnimationBindEnd("pontiff_giantSword_teleportIN",
                                [&](const FrameAnimation_DESC&) { State_.ChangeState("Visible"); });

    Renderer_->GetTransform().SetLocalScale({125, 400});

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.9f, 0.0f, 0.25f});
    DetectCollider_->GetTransform().SetWorldScale({1500.f, 1000.f, 1.0f});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.97f, 0.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({50.f, 300.f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({0, 0});

    BloodEffect_ = GetLevel()->CreateActor<BloodSplatters>();
    BloodEffect_->GetRenderer()->Off();

    State_.CreateStateMember(
        "TeleportIN",
        std::bind(&GiantSword::TeleportINUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&GiantSword::TeleportINStart, this, std::placeholders::_1),
        std::bind(&GiantSword::TeleportINEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "TeleportOut",
        std::bind(&GiantSword::TeleportOutUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&GiantSword::TeleportOutStart, this, std::placeholders::_1),
        std::bind(&GiantSword::TeleportOutEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Visible",
                             std::bind(&GiantSword::VisibleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&GiantSword::VisibleStart, this, std::placeholders::_1),
                             std::bind(&GiantSword::VisibleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Track",
                             std::bind(&GiantSword::TrackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&GiantSword::TrackStart, this, std::placeholders::_1),
                             std::bind(&GiantSword::TrackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("TrunAttack",
                             std::bind(&GiantSword::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&GiantSword::AttackStart, this, std::placeholders::_1),
                             std::bind(&GiantSword::AttackEnd, this, std::placeholders::_1));

    State_.ChangeState("Visible");
}

void GiantSword::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    DetectCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Player,
        CollisionType::CT_OBB2D,
        std::bind(&GiantSword::LookAtPlayer, this, std::placeholders::_1, std::placeholders::_2));

    GameEngineDebug::OutPutString("GiantSword : " + State_.GetCurStateStateName());
}

void GiantSword::End() {}


//화면에서 퇴장
void GiantSword::TeleportINStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("pontiff_giantSword_teleportIN");

    Pontiff_->ChangeMonsterState("Opening");
    BodyCollider_->Off();
}

void GiantSword::TeleportINUpdate(float _DeltaTime, const StateInfo& _Info) {}

void GiantSword::TeleportINEnd(const StateInfo& _Info) {}


//화면에 등장
void GiantSword::TeleportOutStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("pontiff_giantSword_teleportOUT");

    if ("CloseIdle" != Pontiff_->GetState())
    {
        Pontiff_->ChangeMonsterState("Closing");
    }

    BodyCollider_->On();
}

void GiantSword::TeleportOutUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        BloodEffect_->GetTransform().SetWorldPosition({BodyCollider_->GetTransform().GetWorldPosition().x,
                                                       BodyCollider_->GetTransform().GetWorldPosition().y,
                                                       static_cast<int>(ACTORORDER::PlayerEffect)});
        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplatters");
    }

    MonsterBase::DamageCheck(50.f, "TeleportIN");
}

void GiantSword::TeleportOutEnd(const StateInfo& _Info) {}


void GiantSword::VisibleStart(const StateInfo& _Info)
{
    SetHP(100);
    Renderer_->Off();
}

void GiantSword::VisibleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if ("Death" == Pontiff_->GetState())
    {
        return;
    }

    if (5 < _Info.StateTime)
    {
        State_.ChangeState("TeleportOut");
    }
}

void GiantSword::VisibleEnd(const StateInfo& _Info) { Renderer_->On(); }


void GiantSword::AttackStart(const StateInfo& _Info) {}

void GiantSword::AttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void GiantSword::AttackEnd(const StateInfo& _Info) {}


void GiantSword::TrackStart(const StateInfo& _Info) {}

void GiantSword::TrackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void GiantSword::TrackEnd(const StateInfo& _Info) {}


bool GiantSword::LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other) { return false; }
