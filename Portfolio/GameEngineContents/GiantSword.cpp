#include "PreCompile.h"
#include "GiantSword.h"

GiantSword::GiantSword() {}

GiantSword::~GiantSword() {}


void GiantSword::Start()
{
    EyeRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    EyeRenderer_->SetTexture("pontiff_giantSword_eyeGlobeSprite.png");
    EyeRenderer_->GetTransform().SetLocalScale({125, 400});

    IrisRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    IrisRenderer_->SetTexture("pontiff_giantSword_irisSprite.png");
    IrisRenderer_->GetTransform().SetLocalScale({125, 400});
    IrisRenderer_->SetPivot(PIVOTMODE::CUSTOM);

    // EyeLidRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    // EyeLidRenderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_eyeLids", { "pontiff_giantSword_eyeLids.png",
    // 0, 19, 0.1f, true }); EyeLidRenderer_->GetTransform().SetLocalMove({0, 120.f});
    // EyeLidRenderer_->GetTransform().SetLocalScale({ 150, 200 });

    // IrisRenderer_->Off();
    // EyeRenderer_->Off();
    //  EyeLidRenderer_->Off();

    Renderer_ = CreateComponent<GameEngineTextureRenderer>();

    Renderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_teleportOUT",
                                              {"pontiff_giantSword_teleportOUT.png", 0, 19, 0.1f, false});
    Renderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_teleportIN",
                                              {"pontiff_giantSword_teleportIN.png", 0, 26, 0.1f, false});
    Renderer_->GetTransform().SetLocalScale({125, 400});

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.9f, 0.0f, 0.25f});
    DetectCollider_->GetTransform().SetWorldScale({1500.f, 1000.f, 1.0f});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.97f, 0.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({50.f, 300.f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({0, 100});

    State_.CreateStateMember(
        "TeleportIN",
        std::bind(&GiantSword::TeleportINUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&GiantSword::TeleportINStart, this, std::placeholders::_1),
        std::bind(&GiantSword::AttackEnd, this, std::placeholders::_1));
    State_.CreateStateMember(
        "TeleportOut",
        std::bind(&GiantSword::TeleportOutUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&GiantSword::TeleportOutStart, this, std::placeholders::_1),
        std::bind(&GiantSword::AttackEnd, this, std::placeholders::_1));
    State_.CreateStateMember("TrunAttack",
                             std::bind(&GiantSword::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&GiantSword::AttackStart, this, std::placeholders::_1),
                             std::bind(&GiantSword::AttackEnd, this, std::placeholders::_1));
    State_.ChangeState("TeleportIN");
}

void GiantSword::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    DetectCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Player,
        CollisionType::CT_OBB2D,
        std::bind(&GiantSword::LookAtPlayer, this, std::placeholders::_1, std::placeholders::_2));
}

void GiantSword::End() {}


void GiantSword::TeleportINStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("pontiff_giantSword_teleportOut");
    BodyCollider_->Off();
}

void GiantSword::TeleportINUpdate(float _DeltaTime, const StateInfo& _Info) {}

void GiantSword::TeleportINEnd(const StateInfo& _Info) {}

void GiantSword::TeleportOutStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("pontiff_giantSword_teleportIN");
    BodyCollider_->On();
}

void GiantSword::TeleportOutUpdate(float _DeltaTime, const StateInfo& _Info) {}

void GiantSword::TeleportOutEnd(const StateInfo& _Info) {}

void GiantSword::AttackStart(const StateInfo& _Info)
{
    Renderer_->SetTexture("pontiff_giantSword_swordSprite.png");

    // IrisRenderer_->On();
    // EyeRenderer_->On();
    //  EyeLidRenderer_->On();
    //  EyeLidRenderer_->ChangeFrameAnimation("pontiff_giantSword_eyeLids");
}

void GiantSword::AttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void GiantSword::AttackEnd(const StateInfo& _Info)
{
    // IrisRenderer_->Off();
    // EyeRenderer_->Off();
    //  EyeLidRenderer_->Off();
}

bool GiantSword::LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    float4 Dir = _Other->GetTransform().GetWorldPosition() - _This->GetTransform().GetWorldPosition();

    Dir.Normalize();

    float4 LimitDistance = (EyeRenderer_->GetTransform().GetWorldPosition() + float4{0, 10})
                         - IrisRenderer_->GetTransform().GetWorldPosition();

    if (10 > LimitDistance.x && 10 > LimitDistance.y && -10 < LimitDistance.x && -10 < LimitDistance.y)
    {
        IrisRenderer_->GetTransform().SetWorldMove(Dir * 150 * GameEngineTime::GetDeltaTime());
    }

    else
    {
        LimitDistance.Normalize();
        IrisRenderer_->GetTransform().SetWorldMove(LimitDistance * 150 * GameEngineTime::GetDeltaTime());
    }

    return true;
}
