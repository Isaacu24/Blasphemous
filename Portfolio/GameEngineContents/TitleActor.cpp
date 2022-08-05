#include "PreCompile.h"
#include "TitleActor.h"

TitleActor::TitleActor() 
	: ButttonShadow_(nullptr)
	, IsReverse_(false)
	, Alpha_(1.0f)
{
}

TitleActor::~TitleActor() 
{
}

void TitleActor::Start()
{
	GameEngineUIRenderer* TitleRenderer = CreateComponent<GameEngineUIRenderer>();
	TitleRenderer->SetTexture("TitleBackground.png");
	TitleRenderer->GetTransform().SetWorldScale({ GameEngineWindow::GetScale() });

	GameEngineUIRenderer* DescRenderer = CreateComponent<GameEngineUIRenderer>();
	DescRenderer->SetTexture("StartCopyRight.png");
	DescRenderer->GetTransform().SetWorldMove({0.f, -270.f, 0 });
	DescRenderer->GetTransform().SetWorldScale({ 900, 124 });

	ButttonShadow_ = CreateComponent<GameEngineUIRenderer>();
	ButttonShadow_->SetTexture("PressAnyButttonShadow.png");
	ButttonShadow_->GetTransform().SetWorldScale({ 214, 24 });
	ButttonShadow_->GetTransform().SetWorldMove({ 0.f, -150.f, 0.f });

	GameEngineUIRenderer* PressAnyKey = CreateComponent<GameEngineUIRenderer>();
	PressAnyKey->SetTexture("PressAnyButton.png");
	PressAnyKey->GetTransform().SetWorldScale({ 250, 20 });
	PressAnyKey->GetTransform().SetWorldMove({ 0.f, -150.f, 0.f });
}

void TitleActor::Update(float _DeltaTime)
{
	if (false == IsReverse_)
	{
		Alpha_ -= _DeltaTime;
		ButttonShadow_->GetColorData().MulColor = float4{ 1.0f, 1.0f, 1.0f, Alpha_ };

		if (0.0f >= Alpha_)
		{
			IsReverse_ = true;
		}
	}

	else
	{
		Alpha_ += _DeltaTime;
		ButttonShadow_->GetColorData().MulColor = float4{ 1.0f, 1.0f, 1.0f, Alpha_ };

		if (1.0f <= Alpha_)
		{
			IsReverse_ = false;
		}
	}



}

void TitleActor::End()
{
}
