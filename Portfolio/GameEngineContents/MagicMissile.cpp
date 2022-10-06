#include "PreCompile.h"
#include "MagicMissile.h"

MagicMissile::MagicMissile() {}

MagicMissile::~MagicMissile() {}

void MagicMissile::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();

    Renderer_->CreateFrameAnimationCutTexture("Create", {"pope_magicMissile.png", 0, 6, 0.1f, false});
    Renderer_->AnimationBindEnd("Create",
                                [&](const FrameAnimation_DESC& _Info) { Renderer_->ChangeFrameAnimation("Shoot"); });

    Renderer_->CreateFrameAnimationCutTexture("Shoot", {"pope_magicMissile.png", 7, 19, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("Death", {"pope_magicMissile.png", 19, 28, 0.1f, true});
    Renderer_->AnimationBindEnd("Death", [&](const FrameAnimation_DESC& _Info) { Death(); });

    State_.CreateStateMember("Shoot",
                             std::bind(&MagicMissile::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&MagicMissile::ShootStart, this, std::placeholders::_1),
                             std::bind(&MagicMissile::ShootEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "Explosion",
        std::bind(&MagicMissile::ExplosionUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&MagicMissile::ExplosionStart, this, std::placeholders::_1),
        std::bind(&MagicMissile::ExplosionEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "GroundExplosion",
        std::bind(&MagicMissile::GroundExplosionUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&MagicMissile::GroundExplosionStart, this, std::placeholders::_1),
        std::bind(&MagicMissile::GroundExplosionEnd, this, std::placeholders::_1));

    State_.ChangeState("Shoot");

    Renderer_->ChangeFrameAnimation("Create");
    Renderer_->GetTransform().SetWorldScale({200.f, 200.f});
    Renderer_->SetPivot(PIVOTMODE::CENTER);

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::BossMonsterAttack);
    Collider_->GetTransform().SetWorldScale({10.0f, 10.0f, 1.0f});

    SetSpeed(200.f);
}

void MagicMissile::Update(float _DeltaTime) { State_.Update(_DeltaTime); }

void MagicMissile::End() {}


void MagicMissile::ShootStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("Shoot");

    SoundPlayer_ = GameEngineSound::SoundPlayControl("MAGIC_SHOT.wav");
    SoundPlayer_.Volume(0.05f);
}

void MagicMissile::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                              -(GetTransform().GetWorldPosition().y));

    if (Color.CompareInt4D(float4::BLACK))
    {
        IsExplosion_ = true;
        State_.ChangeState("GroundExplosion");
    }

    Speed_ += _DeltaTime * 400.f;
    GetTransform().SetWorldMove({(Dir_.x * Speed_ * _DeltaTime), (Dir_.y * Speed_ * _DeltaTime)});

    float4 Distance    = StartPos_ - GetTransform().GetWorldPosition();
    float4 ABSDistance = float4::ABS3DReturn(Distance);

    if (3000.f < ABSDistance.x || 3000.f < ABSDistance.y)
    {
        Death();
    }
}

void MagicMissile::ShootEnd(const StateInfo& _Info) {}


void MagicMissile::ExplosionStart(const StateInfo& _Info) { Collider_->Off(); }

void MagicMissile::ExplosionUpdate(float _DeltaTime, const StateInfo& _Info) 
{
    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                              -(GetTransform().GetWorldPosition().y));

    if (Color.CompareInt4D(float4::BLACK))
    {
        IsExplosion_ = true;
        State_.ChangeState("GroundExplosion");
    }

    Speed_ += _DeltaTime * 400.f;
    GetTransform().SetWorldMove({(Dir_.x * Speed_ * _DeltaTime), (Dir_.y * Speed_ * _DeltaTime)});

    float4 Distance    = StartPos_ - GetTransform().GetWorldPosition();
    float4 ABSDistance = float4::ABS3DReturn(Distance);

    if (3000.f < ABSDistance.x || 3000.f < ABSDistance.y)
    {
        Death();
    }
}

void MagicMissile::ExplosionEnd(const StateInfo& _Info) {}


void MagicMissile::GroundExplosionStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("Death"); }

void MagicMissile::GroundExplosionUpdate(float _DeltaTime, const StateInfo& _Info) {}

void MagicMissile::GroundExplosionEnd(const StateInfo& _Info) {}
