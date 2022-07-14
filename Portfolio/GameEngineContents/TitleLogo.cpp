#include "TitleLogo.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetWorldScale({ 800, 300 });
	Renderer->SetTexture("GameLogo.png");
}

void TitleLogo::Update(float _DeltaTime)
{
}

void TitleLogo::End()
{
}
