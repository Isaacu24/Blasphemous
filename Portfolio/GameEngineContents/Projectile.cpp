#include "PreCompile.h"
#include "Projectile.h"

Projectile::Projectile() 
	: State_{}
	, Renderer_(nullptr)
	, Collider_(nullptr)
	, ColMap_(nullptr)
	, Dir_(float4::ZERO)
	, Speed_(200.f)
{
}

Projectile::~Projectile() 
{
}

//GameEngineTexture::Cut("TakeBackProyectile.png", 6, 2);
//GameEngineTexture::Cut("TakeBackProyectileExplosion.png", 6, 3);
//GameEngineTexture::Cut("TakeBackProyectileHead.png", 6, 2);

void Projectile::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimation("TakeBackProyectile", {"TakeBackProyectile.png", 0, 9, 0.1f, true});
	Renderer_->CreateFrameAnimation("TakeBackProyectileExplosion", { "TakeBackProyectileExplosion.png", 0, 14, 0.1f, true });
	Renderer_->CreateFrameAnimation("TakeBackProyectileHead", { "TakeBackProyectileHead.png", 0, 9, 0.1f, true });
	Renderer_->ChangeFrameAnimation("TakeBackProyectile");
	Renderer_->GetTransform().SetWorldScale({60.f, 40.f });

	Collider_ = CreateComponent<GameEngineCollision>();
	Collider_->ChangeOrder(COLLISIONORDER::Projectile);
	Collider_->GetTransform().SetWorldScale({ 10.0f, 10.0f, 1.0f });

	State_.CreateStateMember("Shoot", this, &Projectile::ShootUpdate, &Projectile::ShootStart);
	State_.CreateStateMember("Explosion", this, &Projectile::ExplosionUpdate, &Projectile::ExplosionStart);
	State_.ChangeState("Shoot");
}

void Projectile::Update(float _DeltaTime)
{
	State_.Update(_DeltaTime);

	float4 Color = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));

	if (Color.CompareInt4D(float4::BLACK))
	{
		State_.ChangeState("Explosion");
	}

	Collider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D,
		std::bind(&Projectile::Explosion, this, std::placeholders::_1, std::placeholders::_2));
}


void Projectile::Shoot(float _DeltaTime)
{
	GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
}


void Projectile::End()
{
}


void Projectile::ShootStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("TakeBackProyectile");
}

void Projectile::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Shoot(_DeltaTime);
}

void Projectile::ExplosionStart(const StateInfo& _Info)
{
	Renderer_->GetTransform().SetWorldScale({ 200.f, 200.f });
	Renderer_->ChangeFrameAnimation("TakeBackProyectileExplosion");
	Renderer_->AnimationBindEnd("TakeBackProyectileExplosion", &Projectile::ExplosionEnd, this);
}

void Projectile::ExplosionUpdate(float _DeltaTime, const StateInfo& _Info)
{

}
