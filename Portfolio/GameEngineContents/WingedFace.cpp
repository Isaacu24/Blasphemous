#include "PreCompile.h"
#include "WingedFace.h"
#include "Projectile.h"

WingedFace::WingedFace() 
{
}

WingedFace::~WingedFace() 
{
}


void WingedFace::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationFolder("WingedFaceIdle", FrameAnimation_DESC{ "WingedFaceIdle", 0.1f });
	Renderer_->CreateFrameAnimationFolder("WingedFaceDeath", FrameAnimation_DESC{ "WingedFaceDeath", 0.1f, false });
	Renderer_->ChangeFrameAnimation("WingedFaceDeath");
	Renderer_->ScaleToTexture();
	Renderer_->SetScaleModeImage();
	Renderer_->SetPivot(PIVOTMODE::CENTER);

	Gravity_ = CreateComponent<GravityComponent>();
	Collider_ = CreateComponent<GameEngineCollision>();
	Collider_->ChangeOrder(COLLISIONORDER::Monster);
	Collider_->GetTransform().SetWorldScale({ 300.0f, 300.0f, 1.0f });

	State_.CreateStateMember("Patrol", this, &WingedFace::PatrolUpdate, &WingedFace::PatrolStart);
	State_.CreateStateMember("Shoot", this, &WingedFace::ShootUpdate, &WingedFace::ShootStart);
	State_.CreateStateMember("Death", this, &WingedFace::DeathUpdate, &WingedFace::DeathStart);
	State_.ChangeState("Patrol");

	SetSpeed(150.f);

	PatrolStart_ = true;
	PatrolEnd_ = false;
}

void WingedFace::Update(float _DeltaTime)
{
	State_.Update(_DeltaTime);

	Collider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, 
		std::bind(&WingedFace::LookAtPlayer, this, std::placeholders::_1, std::placeholders::_2));

	//GameEngineDebug::OutPutString("FaceY : " + std::to_string(GetTransform().GetWorldPosition().y));
}

void WingedFace::End()
{
}

void WingedFace::PatrolMoveX(float _DeltaTime)
{
}

void WingedFace::PatrolMoveY(float _DeltaTime)
{
	if (true == PatrolStart_)
	{
		if (GetTransform().GetWorldPosition().y < StartPos_)
		{
			GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
		}

		else
		{
			State_.ChangeState("Shoot");

			PatrolStart_ = false;
			PatrolEnd_ = true;
		}
	}

	else if (true == PatrolEnd_)
	{
		if (GetTransform().GetWorldPosition().y > EndPos_)
		{
			GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
		}

		else
		{
			State_.ChangeState("Shoot");

			PatrolStart_ = true;
			PatrolEnd_ = false;
		}
	}
}


void WingedFace::PatrolStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("WingedFaceIdle");
	Renderer_->ScaleToTexture();
	Renderer_->SetScaleModeImage();
	Renderer_->SetPivot(PIVOTMODE::CENTER);
}

void WingedFace::PatrolUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PatrolMoveY(_DeltaTime);
}

void WingedFace::ShootStart(const StateInfo& _Info)
{
	Projectile* LeftProjectile = GetLevel()->CreateActor<Projectile>();
	LeftProjectile->SetGround(ColMap_);
	LeftProjectile->SetDirection(float4::LEFT);
	LeftProjectile->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x - 50.f, GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::AfterParallax5)});
	LeftProjectile->GetTransform().SetWorldScale({ 2, 2 });

	Projectile* RightProjectile = GetLevel()->CreateActor<Projectile>();
	RightProjectile->SetGround(ColMap_);
	RightProjectile->SetDirection(float4::RIGHT);
	RightProjectile->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x + 50.f, GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::AfterParallax5) });
	RightProjectile->GetTransform().SetWorldScale({ 2, 2 });
}

void WingedFace::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0.5f <= _Info.StateTime)
	{
		State_.ChangeState("Patrol");
	}
}

void WingedFace::DeathStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("WingedFaceDeath");
	Renderer_->ScaleToTexture();
	Renderer_->SetScaleModeImage();
	Renderer_->SetPivot(PIVOTMODE::CENTER);

	Renderer_->AnimationBindEnd("WingedFaceDeath", &WingedFace::DeathEnd, this);
}

void WingedFace::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}