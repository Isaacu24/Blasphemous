#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
	: LocalScale(float4::ONE)
	, LocalPosition(float4::ZERO)
	, LocalRotation(float4::ZERO)
	, Parent(nullptr)
{
}

GameEngineTransform::~GameEngineTransform()
{
}


void GameEngineTransform::CalculateWorld()
{
	//로컬 크기
	LocalWorldMat = LocalScaleMat * LocalRotateMat * LocalPositionMat;

	if (nullptr != Parent) //부모가 있을 경우 부모의 크기를 곱한다
	{
		WorldWorldMat = LocalWorldMat * Parent->GetWorldWorld();
	}
	else
	{
		WorldWorldMat = LocalWorldMat;
	}
}

void GameEngineTransform::PushChild(GameEngineTransform* _Child)
{
	_Child->Parent = this;
	Childs.push_back(_Child);
}