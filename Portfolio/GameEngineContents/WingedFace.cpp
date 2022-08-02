#include "PreCompile.h"
#include "WingedFace.h"

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

	State_.CreateStateMember("Patrol", this, &WingedFace::PatrolUpdate, &WingedFace::PatrolStart);
	State_.CreateStateMember("Death", this, &WingedFace::DeathUpdate, &WingedFace::DeathStart);
	State_.ChangeState("Patrol");

	SetSpeed(150.f);

	PatrolStart_ = true;
	PatrolEnd_ = false;
}

void WingedFace::Update(float _DeltaTime)
{
	State_.Update(_DeltaTime);

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