#include "PreCompile.h"
#include "FireBall.h"

FireBall::FireBall() 
{
}

FireBall::~FireBall() 
{
}




void FireBall::Start()
{ 
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_fireBall", {"pope_fireBall.png", 0, 9, 0.1f, true});
    Renderer_->ChangeFrameAnimation("pope_fireBall");
    Renderer_->GetTransform().SetWorldScale({60.f, 40.f});

        Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::Projectile);
    Collider_->GetTransform().SetWorldScale({10.0f, 10.0f, 1.0f});

    //State_.CreateStateMember(
    //    "Shoot",
    //    std::bind(&VioletProjectile::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2),
    //    std::bind(&VioletProjectile::ShootStart, this, std::placeholders::_1));
    //State_.CreateStateMember(
    //    "Explosion",
    //    std::bind(&VioletProjectile::ExplosionUpdate, this, std::placeholders::_1, std::placeholders::_2),
    //    std::bind(&VioletProjectile::ExplosionStart, this, std::placeholders::_1));
    //State_.ChangeState("Shoot");
}

void FireBall::Update(float _DetalTime) 
{

}

void FireBall::End()
{

}