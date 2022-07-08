#pragma once
#include "GameEngineRes.h"

// 최종 픽셀 셰이더의 출력 결과를 랜더 타겟에 출력할때 색깔 통합에 관련
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

