#include "PreCompile.h"
#include "MagicMissile.h"

MagicMissile::MagicMissile()
    : Speed_(200.f)
{}

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

    Renderer_->ChangeFrameAnimation("Create");
    Renderer_->GetTransform().SetWorldScale({200.f, 200.f});
    Renderer_->SetPivot(PIVOTMODE::CENTER);

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::Projectile);
    Collider_->GetTransform().SetWorldScale({10.0f, 10.0f, 1.0f});
}

void MagicMissile::Update(float _DeltaTime)
{
    if (true == IsExplosion_)
    {
        return;
    }

    Speed_ += _DeltaTime * 300.f;
    GetTransform().SetWorldMove({(Dir_.x * Speed_ * _DeltaTime), (Dir_.y * Speed_ * _DeltaTime)});

    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::Player,
                           CollisionType::CT_OBB2D,
                           [&](GameEngineCollision* _This, GameEngineCollision* _Other)
                           {
                               Renderer_->ChangeFrameAnimation("Death"); 

                               Collider_->Off();

                               IsExplosion_ = true;
                               return true;
                           });
}

void MagicMissile::End() {}
