#include "PreCompile.h"
#include "NormalMonster.h"

NormalMonster::NormalMonster()
	: IsCollision_(false)
{
}

NormalMonster::~NormalMonster() 
{
}

bool NormalMonster::LeftObstacleCheck(int _X, int _Y)
{
	float4 LeftColor = ColMap_->GetCurTexture()->GetPixel(_X, _Y);

	if (true == LeftColor.CompareInt4D(float4::BLACK))
	{
		return true;
	}

	if (true == LeftColor.CompareInt4D(float4::MAGENTA))
	{
		return true;
	}

	return false;
}

bool NormalMonster::RightObstacleCheck(int _X, int _Y)
{
	float4 RightColor = ColMap_->GetCurTexture()->GetPixel(_X, _Y);

	if (true == RightColor.CompareInt4D(float4::BLACK))
	{
		return true;
	}

	if (true == RightColor.CompareInt4D(float4::MAGENTA))
	{
		return true;
	}

	return false;
}

bool NormalMonster::LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
	{
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	else
	{
		Renderer_->GetTransform().PixLocalNegativeX();
	}

	return false;
}

bool NormalMonster::TrackPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	State_.ChangeState("Track");

	LookAtPlayer(_This, _Other);

	float Distance = abs(_This->GetTransform().GetWorldPosition().x - _Other->GetTransform().GetWorldPosition().x);

	if (70.f > Distance)
	{
		IsPlayerLeft_ = false;
		IsPlayerRight_ = false;
		return false;
	}

	if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
	{
		IsPlayerLeft_ = true;
		IsPlayerRight_ = false;
	}

	else
	{
		IsPlayerRight_ = true;
		IsPlayerLeft_ = false;
	}

	return true;
}


