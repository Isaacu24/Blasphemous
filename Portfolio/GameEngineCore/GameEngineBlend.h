#pragma once
#include "GameEngineRes.h"

// ���� �ȼ� ���̴��� ��� ����� ���� Ÿ�ٿ� ����Ҷ� ���� ���տ� ����
class GameEngineBlend : public GameEngineRes<GameEngineBlend>
{
public:
	GameEngineBlend();
	~GameEngineBlend();

	GameEngineBlend(const GameEngineBlend& _Other) = delete;
	GameEngineBlend(GameEngineBlend&& _Other) noexcept = delete;
	GameEngineBlend& operator=(const GameEngineBlend& _Other) = delete;
	GameEngineBlend& operator=(GameEngineBlend&& _Other) noexcept = delete;

protected:

private:

};

