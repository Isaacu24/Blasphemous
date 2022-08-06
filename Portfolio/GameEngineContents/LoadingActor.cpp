#include "PreCompile.h"
#include "LoadingActor.h"


LoadingActor::LoadingActor()
	: RendererTime_(0.f)
	, Alpha_(1.0f)
	, IsEntrance_(false)
{
}

LoadingActor::~LoadingActor() 
{
}

void LoadingActor::Start()
{
	Background_ = CreateComponent<GameEngineUIRenderer>();
	Background_->SetTexture("BlackBackground.png");
	Background_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(UIORDER::LodingUI)});
	Background_->ScaleToTexture();

	Icon_ = CreateComponent<GameEngineUIRenderer>();
	Icon_->SetTexture("LoadingSpinningIco_0.png");
	Icon_->GetTransform().SetWorldPosition({ 520, -250, static_cast<int>(UIORDER::LodingUI) });
	Icon_->GetTransform().SetWorldScale({ 150, 150 });
}

void LoadingActor::Update(float _DeltaTime)
{
	RendererTime_ += _DeltaTime;

	if (0.1f <= RendererTime_)
	{
		RendererTime_ -= 0.1f;
		++CurrentFrame_;

		if (25 == CurrentFrame_)
		{
			CurrentFrame_ = 0;
		}

		Icon_->SetTexture("LoadingSpinningIco_" + std::to_string(CurrentFrame_) + ".png");
	}

	if (true == IsEntrance_)
	{
		Entrance(_DeltaTime);
	}

	else if (true == IsExit_)
	{
		ChangeTime_ += _DeltaTime;

		if (1.f <= ChangeTime_)
		{
			GEngine::ChangeLevel(NextLevel_);
		}
	}
}

void LoadingActor::Entrance(float _DeltaTime)
{
	DeathTime_ += _DeltaTime;

	if (1.f < DeathTime_)
	{
		Alpha_ -= _DeltaTime;
		Icon_->GetColorData().MulColor = float4{ 1.0f, 1.0f, 1.0f, Alpha_ };
		Background_->GetColorData().MulColor = float4{ 1.0f, 1.0f, 1.0f, Alpha_ };

		if (0.f >= Alpha_)
		{
			IsEntrance_ = false;
			Off();
		}
	}
}

void LoadingActor::Exit(const std::string& _Level)
{
	IsExit_ = true;
	NextLevel_ = _Level;
}

void LoadingActor::End()
{
}
