#include "PreCompile.h"
#include "GravityComponent.h"

GravityComponent::GravityComponent() 
{
}

GravityComponent::~GravityComponent() 
{
}

void GravityComponent::Start()
{
}

void GravityComponent::Update(float _DeltaTime)
{
	if (true == Active_)
	{
		GetActor()->GetTransform().SetLocalMove(GetTransform().GetDownVector() * 350.f * _DeltaTime);
	}
}

void GravityComponent::End()
{
}
