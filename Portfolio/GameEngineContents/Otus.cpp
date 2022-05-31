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

}

void Otus::End()
{
}
