#include "PreCompile.h"
#include "MainMenuActor.h"

MainMenuActor::MainMenuActor() 
	: Background_(nullptr)
	, BigPetal_(nullptr)
	, Petal_(nullptr)
	, Crisanta_(nullptr)
	, BackgroundTime_(0.0f)
	, PetalTime_(0.0f)
	, BigPetalTime_(0.0f)
	, CrisantaTime_(0.0f)
	, BackgroundFrame_(0)
	, PetalFrame_(0)
	, BigPetalFrame_(0)
	, CrisantaFrame_(0)
{

}

MainMenuActor::~MainMenuActor() 
{
}

void MainMenuActor::Start()
{
	Background_ = CreateComponent<GameEngineTextureRenderer>();
	Background_->GetTransform().SetWorldScale(GameEngineWindow::GetScale());
	Background_->SetTexture("TitleBackgorund_0.png");

	Petal_ = CreateComponent<GameEngineTextureRenderer>();
	Petal_->GetTransform().SetWorldScale(GameEngineWindow::GetScale());
	Petal_->SetTexture("Crisanta_Petal_0.png");

	Crisanta_ = CreateComponent<GameEngineTextureRenderer>();
	Crisanta_->GetTransform().SetWorldScale({ 878, 720 });
	Crisanta_->GetTransform().SetWorldPosition({-200, 0, 0});
	Crisanta_->SetTexture("Crisanta_0.png");

	BigPetal_ = CreateComponent<GameEngineTextureRenderer>();
	BigPetal_->GetTransform().SetWorldScale(GameEngineWindow::GetScale());
	BigPetal_->SetTexture("Crisanta_BigPetal_0.png");
}

void MainMenuActor::Update(float _DeltaTime)
{
	BackgroundAnimation(_DeltaTime);
	PetalAnimation(_DeltaTime);
	CrisantaAnimation(_DeltaTime);
	BigPetalAnimation(_DeltaTime);
}

void MainMenuActor::End()
{
}

void MainMenuActor::BackgroundAnimation(float _DeltaTime)
{
	BackgroundTime_ += _DeltaTime;

	if (0.1f <= BackgroundTime_)
	{
		BackgroundTime_ -= 0.1f;
		++BackgroundFrame_;

		if (15 == BackgroundFrame_)
		{
			BackgroundFrame_ = 0;
		}
		Background_->SetTexture("TitleBackgorund_" + std::to_string(BackgroundFrame_) + ".png");
	}

}

void MainMenuActor::PetalAnimation(float _DeltaTime)
{
	PetalTime_ += _DeltaTime;

	if (0.1f <= PetalTime_)
	{
		PetalTime_ -= 0.1f;
		++PetalFrame_;

		if (44 == PetalFrame_)
		{
			PetalFrame_ = 0;
		}

		Petal_->SetTexture("Crisanta_Petal_" + std::to_string(PetalFrame_) + ".png");
	}
}

void MainMenuActor::BigPetalAnimation(float _DeltaTime)
{
	BigPetalTime_ += _DeltaTime;

	if (0.2f <= BigPetalTime_)
	{
		BigPetalTime_ -= 0.2f;
		++BigPetalFrame_;

		if (6 == BigPetalFrame_)
		{
			BigPetalFrame_ = 0;
		}

		BigPetal_->SetTexture("Crisanta_BigPetal_" + std::to_string(BigPetalFrame_) + ".png");
	}
}

void MainMenuActor::CrisantaAnimation(float _DeltaTime)
{
	CrisantaTime_ += _DeltaTime;

	if (0.2f <= CrisantaTime_)
	{
		CrisantaTime_ -= 0.2f;
		++CrisantaFrame_;

		if (14 == CrisantaFrame_)
		{
			CrisantaFrame_ = 0;
		}

		Crisanta_->SetTexture("Crisanta_" + std::to_string(CrisantaFrame_) + ".png");
	}
}
