#include "PreCompile.h"
#include "Door.h"

Door::Door() 
{
}

Door::~Door() 
{
}

void Door::Open()
{
}

void Door::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationCutTexture("brotherhood_door_anim_Close", { "brotherhood_door_anim 1.png", 0, 1, 0.1f, false });
	Renderer_->CreateFrameAnimationCutTexture("brotherhood_door_anim_Open", { "brotherhood_door_anim 1.png", 0, 14, 0.1f, false });
	Renderer_->ChangeFrameAnimation("brotherhood_door_anim_Close");
	Renderer_->GetTransform().SetWorldScale({ 450, 450 });
}

void Door::Update(float _DeltaTime)
{

}

void Door::End()
{
	Renderer_->ChangeFrameAnimation("brotherhood_door_anim_Open");
}
