#include "PreCompile.h"
#include "MonsterBase.h"

MonsterBase::MonsterBase() 
{
}

MonsterBase::~MonsterBase() 
{
}

void MonsterBase::SetGround(GameEngineTextureRenderer* _Ground)
{
	ColMap_ = _Ground;
}

bool MonsterBase::GroundCheck(int _X, int _Y)
{
	float4 Color = ColMap_->GetCurTexture()->GetPixel(_X, _Y);

	if (Color.CompareInt4D(float4::BLACK))
	{
		return true;
	}

	else if (Color.CompareInt4D(float4::MAGENTA))
	{
		return true;
	}

	return false;
}


