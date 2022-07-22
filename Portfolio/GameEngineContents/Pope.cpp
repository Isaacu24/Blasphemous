#include "PreCompile.h"
#include "Pope.h"

Pope::Pope() 
{
}

Pope::~Pope() 
{
}

//GameEngineTexture::Cut("pope_idle.png", 4, 4);
//GameEngineTexture::Cut("pope_appear.png", 4, 4);
//GameEngineTexture::Cut("pope_death.png", 6, 6);
//GameEngineTexture::Cut("pope_hitReaction.png", 4, 3);
//GameEngineTexture::Cut("pope_spellCast.png", 8, 7);
//GameEngineTexture::Cut("pope_vanishing.png", 4, 4);

void Pope::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimation("pope_vanishing", { "pope_vanishing.png", 0, 13, 0.1f, true });
	Renderer_->ChangeFrameAnimation("pope_vanishing");

	Renderer_->GetTransform().SetWorldScale({250, 250 });
}

void Pope::Update(float _DeltaTime)
{
}

void Pope::End()
{
}
