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

	// ���ʹ� => ����
	// Ưȭ���� ������
	// ������Ʈ�� �� => ���

}

void Otus::Update(float _DeltaTime)
{
	TimeAngle += _DeltaTime * 20.0f;

}

void Otus::End()
{
}
