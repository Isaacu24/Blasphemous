#include "PreCompile.h"
#include "NormalMonster.h"

NormalMonster::NormalMonster() 
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


