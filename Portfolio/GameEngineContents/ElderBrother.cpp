#include "ElderBrother.h"
#include "PreCompile.h"

ElderBrother::ElderBrother() 
{
}

ElderBrother::~ElderBrother() 
{
}

//GameEngineTexture::Cut("elderBrother_idle.png", 3, 4);
//GameEngineTexture::Cut("elderBrother_jump.png", 4, 7);
//GameEngineTexture::Cut("elderBrother_attack.png", 4, 6);
//GameEngineTexture::Cut("elderBrother_death.png", 5, 10);
//GameEngineTexture::Cut("elderBrother_corpse.png", 4, 3);

void ElderBrother::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimation("elderBrother_idle", {"elderBrother_idle.png", 0, 9, 0.15f, true});
	Renderer_->ChangeFrameAnimation("elderBrother_idle");
}

void ElderBrother::Update(float _DeltaTime)
{
}

void ElderBrother::End()
{
}
