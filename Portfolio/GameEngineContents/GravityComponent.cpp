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
	GetActor()->GetTransform().SetLocalMove(GetTransform().GetDownVector() * 250.f * _DeltaTime);
}

void GravityComponent::End()
{
}
