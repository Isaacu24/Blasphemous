#pragma once
#include "GameEngineRes.h"

// 최종 픽셀 셰이더의 출력 결과를 랜더타겟에 출력할 때 깊이 버퍼링 처리
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

