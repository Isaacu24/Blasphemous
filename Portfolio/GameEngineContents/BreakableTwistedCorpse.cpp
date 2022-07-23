#include "PreCompile.h"
#include "BreakableTwistedCorpse.h"

BreakableTwistedCorpse::BreakableTwistedCorpse() 
{
}

BreakableTwistedCorpse::~BreakableTwistedCorpse() 
{
}

void BreakableTwistedCorpse::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	//Renderer_->CreateFrameAnimation("breakableTwistedCorpse03", { "breakableTwistedCorpse03.png", 0, 10, 0.1f, true });
	//Renderer_->CreateFrameAnimation("breakableTwistedCorpse04", { "breakableTwistedCorpse04.png", 0, 10, 0.1f, true });
	//Renderer_->ChangeFrameAnimation("breakableTwistedCorpse03");

	Renderer_->GetTransform().SetWorldScale({ 150, 300 });
}

void BreakableTwistedCorpse::Update(float _DeltaTime)
{
}

void BreakableTwistedCorpse::End()
{
}
