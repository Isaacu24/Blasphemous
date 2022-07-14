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
	DescRenderer->GetTransform().SetWorldPosition({30.f, -200.f, 0 });
	DescRenderer->GetTransform().SetWorldScale({ 900, 124 });

}

void TitleActor::Update(float _DeltaTime)
{
}

void TitleActor::End()
{
}
