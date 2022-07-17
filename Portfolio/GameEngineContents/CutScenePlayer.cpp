#include "PreCompile.h"
#include "CutScenePlayer.h"

CutScenePlayer::CutScenePlayer() 
	: CutRenderer_(nullptr)
	, CurrentType_(CutSceneType::Intro)
	, PlayTime_(0.0f)
	, CurrentFrame_(0)
{
}

CutScenePlayer::~CutScenePlayer() 
{
}


void CutScenePlayer::Start()
{
	CutRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	CutRenderer_->GetTransform().SetWorldScale({GameEngineWindow::GetScale()});
	CutRenderer_->SetTexture("CutScene_0.png");

	CurrentType_ = CutSceneType::DeadBrotherhood;
}

void CutScenePlayer::Update(float _DeltaTime)
{
	switch (CurrentType_)
	{
	case CutSceneType::Intro:
		PalyIntro(_DeltaTime);
		break;
	case CutSceneType::FallPenitent:
		break;
	case CutSceneType::DeadBrotherhood:
		PalyIntro(_DeltaTime);
		break;
	}
}

void CutScenePlayer::End()
{
}

void CutScenePlayer::PalyIntro(float DeltaTime_)
{
	PlayTime_ += DeltaTime_;

	if (0.02f <= PlayTime_)
	{
		PlayTime_ -= 0.02f;

		++CurrentFrame_;

		if (664 == CurrentFrame_)
		{
			Death();
			return;
		}

		CutRenderer_->SetTexture("CutScene_" + std::to_string(CurrentFrame_) + ".png");
	}
}
