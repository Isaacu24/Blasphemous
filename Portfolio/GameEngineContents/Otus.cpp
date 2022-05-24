#include "Otus.h"
#include <GameEngineCore/GameEngineRenderer.h>


Otus::Otus() 
{
}

Otus::~Otus() 
{
}

void Otus::Start()
{
	GetTransform().SetScale({ 100, 100, 100 });
	GetTransform().SetPosition({ 300, 300, 100 });
	GameEngineRenderer* Renderer = CreateComponent<GameEngineRenderer>();

}

void Otus::Update(float _DeltaTime)
{
}

void Otus::End()
{
}
