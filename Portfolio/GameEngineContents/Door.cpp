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
	Renderer_->CreateFrameAnimation("brotherhood_door_anim_Close", { "brotherhood_door_anim 1.png", 0, 0, 0.1f, false });
	Renderer_->CreateFrameAnimation("brotherhood_door_anim_Open", { "brotherhood_door_anim 1.png", 0, 14, 0.1f, false });
	Renderer_->ChangeFrameAnimation("brotherhood_door_anim_Close");
	Renderer_->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Object) });
	Renderer_->GetTransform().SetWorldScale({ 450, 450 });
}

void Door::Update(float _DeltaTime)
{

}

void Door::End()
{
	Renderer_->ChangeFrameAnimation("brotherhood_door_anim_Open");
}
