#include "PreCompile.h"
#include "VioletProjectile.h"

VioletProjectile::VioletProjectile()
{}

VioletProjectile::~VioletProjectile() {}

void VioletProjectile::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("TakeBackProyectile", {"TakeBackProyectile.png", 0, 9, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("TakeBackProyectileExplosion",
                                              {"TakeBackProyectileExplosion.png", 0, 14, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("TakeBackProyectileHead",
                                              {"TakeBackProyectileHead.png", 0, 9, 0.1f, true});
    Renderer_->ChangeFrameAnimation("TakeBackProyectile");
    Renderer_->GetTransform().SetWorldScale({60.f, 40.f});

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::Projectile);
    Collider_->GetTransform().SetWorldScale({10.0f, 10.0f, 1.0f});

    State_.CreateStateMember("Shoot",
        std::bind(&VioletProjectile::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&VioletProjectile::ShootStart, this, std::placeholders::_1));
    State_.CreateStateMember(
        "Explosion",
        std::bind(&VioletProjectile::ExplosionUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&VioletProjectile::ExplosionStart, this, std::placeholders::_1));
    State_.ChangeState("Shoot");
}

void VioletProjectile::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                              -(GetTransform().GetWorldPosition().y));

    if (Color.CompareInt4D(float4::BLACK))
    {
        State_.ChangeState("Explosion");
    }

    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::Player,
                           CollisionType::CT_OBB2D,
                           std::bind(&VioletProjectile::Explosion, this, std::placeholders::_1, std::placeholders::_2));
}


void VioletProjectile::End() {}


void VioletProjectile::ShootStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("TakeBackProyectile"); }

void VioletProjectile::ShootUpdate(float _DeltaTime, const StateInfo& _Info) { Shoot(_DeltaTime); }

void VioletProjectile::ExplosionStart(const StateInfo& _Info)
{
    Renderer_->GetTransform().SetWorldScale({200.f, 200.f});
    Renderer_->ChangeFrameAnimation("TakeBackProyectileExplosion");
    Renderer_->AnimationBindEnd("TakeBackProyectileExplosion",
                                std::bind(&VioletProjectile::ExplosionEnd, this, std::placeholders::_1));
}

void VioletProjectile::ExplosionUpdate(float _DeltaTime, const StateInfo& _Info) {}
