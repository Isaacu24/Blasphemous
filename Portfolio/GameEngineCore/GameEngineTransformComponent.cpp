#include "PreCompile.h"
#include "GameEngineTransformComponent.h"

GameEngineTransformComponent::GameEngineTransformComponent() 
{
}

GameEngineTransformComponent::~GameEngineTransformComponent() 
{
}

void GameEngineTransformComponent::DetachObject() 
{
	GetTransform().DetachTransform();
}

void GameEngineTransformComponent::SetParent(GameEngineUpdateObject* _Object) 
{
	GameEngineComponent::SetParent(_Object);

	{
		GameEngineActor* Actor = nullptr;
		if (Actor = dynamic_cast<GameEngineActor*>(_Object))
		{
			Transform.SetParentTransform(Actor->GetTransform());
			return;
		}
	}

	{
		GameEngineTransformComponent* Component = nullptr;
		if (Component = dynamic_cast<GameEngineTransformComponent*>(_Object))
		{
			Transform.SetParentTransform(Component->GetTransform());
			return;
		}
	}
}