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
	//CutRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//CutRenderer_->GetTransform().SetWorldScale({GameEngineWindow::GetScale()});
	//CutRenderer_->SetTexture("CutScene003_0.png");
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
	}
}

void CutScenePlayer::End()
{
}

void CutScenePlayer::PalyIntro(float DeltaTime_)
{
	//PlayTime_ += DeltaTime_;

	//if (0.1f <= PlayTime_)
	//{
	//	PlayTime_ -= 0.1f;

	//	++CurrentFrame_;

	//	if (1104 == CurrentFrame_)
	//	{
	//		//다음 레벨로 이동(함수 포인터)
	//		CurrentFrame_ = 0;
	//		return;
	//	}

	//	CutRenderer_->SetTexture("CutScene003_" + std::to_string(CurrentFrame_) + ".png");
	//}
}
