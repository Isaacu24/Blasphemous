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
	GetTransform().SetScale({ 100, 50, 100 });
	GetTransform().SetPosition({ 300, 300, 100 });
	{
		GameEngineRenderer* Renderer = CreateComponent<GameEngineRenderer>();
		// Renderer->ChangeOrder();
	}

	TimeAngle = 0.0f;

	// 액터는 => 존재
	// 특화하지 않으면
	// 컴포넌트의 뜻 => 기능

}

void Otus::Update(float _DeltaTime)
{
	TimeAngle += _DeltaTime * 20.0f;

	GetTransform().SetRotationXDegree(TimeAngle);
	GetTransform().SetRotationYDegree(TimeAngle);
	GetTransform().SetRotationZDegree(TimeAngle);
}

void Otus::End()
{
}
