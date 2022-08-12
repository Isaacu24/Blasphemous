#include "PreCompile.h"
#include "WingedFace.h"
#include "VioletProjectile.h"

WingedFace::WingedFace() 
	: IsShoot_(false)
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
	DetectCollider_ = CreateComponent<GameEngineCollision>();
	DetectCollider_->ChangeOrder(COLLISIONORDER::Monster);
	DetectCollider_->GetTransform().SetWorldScale({ 300.0f, 300.0f, 1.0f });

	State_.CreateStateMember("Patrol", std::bind(&WingedFace::PatrolUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&WingedFace::PatrolStart, this, std::placeholders::_1));
	State_.CreateStateMember("Shoot", std::bind(&WingedFace::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&WingedFace::ShootStart, this, std::placeholders::_1));
	State_.CreateStateMember("Death", std::bind(&WingedFace::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&WingedFace::DeathStart, this, std::placeholders::_1));
	State_.ChangeState("Patrol");

	SetSpeed(150.f);

	PatrolStart_ = true;
	PatrolEnd_ = false;
}

void WingedFace::Update(float _DeltaTime)
{
	State_.Update(_DeltaTime);

	DetectCollider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, 
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

}

void WingedFace::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0.5f < _Info.StateTime
		&& false == IsShoot_)
	{
		IsShoot_ = true;

		VioletProjectile* LeftProjectile = GetLevel()->CreateActor<VioletProjectile>();
		LeftProjectile->SetGround(ColMap_);
		LeftProjectile->SetDirection(float4::LEFT);
		LeftProjectile->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x - 55.f, GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::AfterParallax5) });
		LeftProjectile->GetTransform().SetWorldScale({ 2, 2 });

		VioletProjectile* RightProjectile = GetLevel()->CreateActor<VioletProjectile>();
		RightProjectile->SetGround(ColMap_);
		RightProjectile->SetDirection(float4::RIGHT);
		RightProjectile->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x + 55.f, GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::AfterParallax5) });
		RightProjectile->GetTransform().SetWorldScale({ 2, 2 });
	}

	if (1.0f <= _Info.StateTime)
	{
		IsShoot_ = false;
		State_.ChangeState("Patrol");
	}
}

void WingedFace::DeathStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("WingedFaceDeath");
	Renderer_->ScaleToTexture();
	Renderer_->SetScaleModeImage();
	Renderer_->SetPivot(PIVOTMODE::CENTER);

	Renderer_->AnimationBindEnd("WingedFaceDeath", std::bind(&WingedFace::DeathEnd, this, std::placeholders::_1));

}

void WingedFace::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}