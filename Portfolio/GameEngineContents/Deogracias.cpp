#include "PreCompile.h"
#include "Deogracias.h"

Deogracias::Deogracias() 
{
}

Deogracias::~Deogracias() 
{
}

void Deogracias::Start()
{
	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetWorldScale({ 200, 400 });
	Renderer->CreateFrameAnimation("Deosgracias_idle", { "Deosgracias_idle.png", 0, 18, 0.1f, true });
	Renderer->ChangeFrameAnimation("Deosgracias_idle");
}

void Deogracias::Update(float _DeltaTime)
{
}

void Deogracias::End()
{
}
