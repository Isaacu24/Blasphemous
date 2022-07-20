#include "PreCompile.h"
#include "Deogracias.h"

Deogracias::Deogracias() 
{
}

Deogracias::~Deogracias() 
{
}

void Deogracias::ChangeFrontAnimation()
{
	Renderer_->ChangeFrameAnimation("Deosgracias_front");
}

void Deogracias::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetWorldScale({ 200, 400 });
	Renderer_->CreateFrameAnimation("Deosgracias_idle", { "Deosgracias_idle.png", 0, 18, 0.1f, true });
	Renderer_->CreateFrameAnimation("Deosgracias_front", { "Deosgracias_front.png", 0, 78, 0.1f, true });
	Renderer_->ChangeFrameAnimation("Deosgracias_idle");
}

void Deogracias::Update(float _DeltaTime)
{
}

void Deogracias::End()
{
}
