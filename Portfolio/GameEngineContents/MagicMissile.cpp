#include "PreCompile.h"
#include "MagicMissile.h"

MagicMissile::MagicMissile()
    : Speed_(200.f)
{}

MagicMissile::~MagicMissile() {}

void MagicMissile::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_magicMissile", {"pope_magicMissile.png", 0, 28, 0.1f, true});
    Renderer_->ChangeFrameAnimation("pope_magicMissile");
    Renderer_->ChangeFrameAnimation("pope_magicMissile");
    Renderer_->AnimationBindEnd("pope_magicMissile", std::bind(&MagicMissile::MissileEnd, this, std::placeholders::_1));

    Renderer_->GetTransform().SetWorldScale({200.f, 200.f});
    Renderer_->SetPivot(PIVOTMODE::CENTER);

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::Projectile);
    Collider_->GetTransform().SetWorldScale({10.0f, 10.0f, 1.0f});
}

void MagicMissile::Update(float _DeltaTime) 
{ 
    Speed_ += _DeltaTime * 300.f;
    GetTransform().SetWorldMove({(Dir_.x * Speed_ * _DeltaTime), (Dir_.y * Speed_ * _DeltaTime)});
}

void MagicMissile::End() {}
