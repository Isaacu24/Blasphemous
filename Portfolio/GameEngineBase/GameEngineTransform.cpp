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
	//���� ũ��
	LocalWorldMat = LocalScaleMat * LocalRotateMat * LocalPositionMat;

	if (nullptr != Parent) //�θ� ���� ��� �θ��� ũ�⸦ ���Ѵ�
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