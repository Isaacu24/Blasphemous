#include "PreCompile.h"
#include "TitleActor.h"

TitleActor::TitleActor() 
{
}

TitleActor::~TitleActor() 
{
}

void TitleActor::Start()
{
	GameEngineTextureRenderer* TitleRenderer = CreateComponent<GameEngineTextureRenderer>();
	TitleRenderer->SetTexture("TitleBackground.png");
	TitleRenderer->GetTransform().SetWorldScale({ GameEngineWindow::GetScale() });

	GameEngineTextureRenderer* DescRenderer = CreateComponent<GameEngineTextureRenderer>();
	DescRenderer->SetTexture("StartCopyRight.png");
	DescRenderer->GetTransform().SetWorldMove({0.f, -270.f, 0 });
	DescRenderer->GetTransform().SetWorldScale({ 900, 124 });

	ButttonShadow_ = CreateComponent<GameEngineTextureRenderer>();
	ButttonShadow_->SetTexture("PressAnyButttonShadow.png");
	ButttonShadow_->GetTransform().SetWorldScale({ 214, 24 });
	ButttonShadow_->GetTransform().SetWorldMove({ 0.f, -150.f, 0.f });

	GameEngineTextureRenderer* PressAnyKey = CreateComponent<GameEngineTextureRenderer>();
	PressAnyKey->SetTexture("PressAnyButton.png");
	PressAnyKey->GetTransform().SetWorldScale({ 250, 20 });
	PressAnyKey->GetTransform().SetWorldMove({ 0.f, -150.f, 0.f });
}

void TitleActor::Update(float _DeltaTime)
{
}

void TitleActor::End()
{
}
