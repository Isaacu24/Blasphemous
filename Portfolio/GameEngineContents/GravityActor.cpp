#include "PreCompile.h"
#include "GravityActor.h"

GravityActor::GravityActor()
	: Gravity_(nullptr)
	, IsMove_(false)
	, Speed_(100.f)
{
}

GravityActor::~GravityActor() 
{
}




void GravityActor::Start()
{
	Gravity_ = CreateComponent<GravityComponent>();
}

void GravityActor::Update(float _DeltaTime)
{
	if (true == IsMove_)
	{
		GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
	}

	GroundCheck();
	Gravity_->SetActive(!IsGround_);
}

void GravityActor::End()
{

}

void GravityActor::GroundCheck()
{
	float4 Color;

	Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));

	if (true == Color.CompareInt4D(float4::BLACK)
		|| true == Color.CompareInt4D(float4::MAGENTA)) //∂•¿Ã∂Û∏È 
	{
		IsGround_ = true;
	}

	else
	{
		IsGround_ = false;
	}
}
