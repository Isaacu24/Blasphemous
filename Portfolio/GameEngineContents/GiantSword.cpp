#include "PreCompile.h"
#include "GiantSword.h"

GiantSword::GiantSword() 
{
}

GiantSword::~GiantSword() 
{
}

//GameEngineTexture::Cut("pontiff_giantSword_teleportOUT.png", 9, 3);
//GameEngineTexture::Cut("pontiff_giantSword_teleportIN.png", 9, 3);

void GiantSword::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->CreateFrameAnimation("pontiff_giantSword_teleportOUT", { "pontiff_giantSword_teleportOUT.png", 0, 19, 0.1f, true });
	Renderer_->CreateFrameAnimation("pontiff_giantSword_teleportIN", { "pontiff_giantSword_teleportIN.png", 0, 17, 0.1f, true });
	Renderer_->ChangeFrameAnimation("pontiff_giantSword_teleportOUT");
	Renderer_->GetTransform().SetLocalScale({ 125, 400 });
	Renderer_->GetTransform().SetLocalMove({ 0, 10 });
}

void GiantSword::Update(float _DeltaTime)
{
}

void GiantSword::End()
{
}
