#include "PreCompile.h"
#include "TitleLogo.h"

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	Renderer = CreateComponent<GameEngineUIRenderer>();
	Renderer->GetTransform().SetWorldScale({ 800, 300 });
	Renderer->SetTexture("GameLogo.png");
}

void TitleLogo::Update(float _DeltaTime)
{
}

void TitleLogo::End()
{
}
