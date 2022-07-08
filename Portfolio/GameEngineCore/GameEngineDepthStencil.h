#pragma once
#include "GameEngineRes.h"

// ���� �ȼ� ���̴��� ��� ����� ����Ÿ�ٿ� ����� �� ���� ���۸� ó��
class GameEngineDepthStencil : public GameEngineRes<GameEngineDepthStencil>
{
public:
	GameEngineDepthStencil();
	~GameEngineDepthStencil();

	GameEngineDepthStencil(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil(GameEngineDepthStencil&& _Other) noexcept = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil& operator=(GameEngineDepthStencil&& _Other) noexcept = delete;

protected:

private:

};

