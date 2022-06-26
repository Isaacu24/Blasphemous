#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonsterBase.h"

class ElderBrother : public GameEngineActor, public BossMonsterBase
{
public:
	ElderBrother();
	~ElderBrother();

	ElderBrother(const ElderBrother& _Other) = delete;
	ElderBrother(ElderBrother&& _Other) noexcept = delete;
	ElderBrother& operator=(const ElderBrother& _Other) = delete;
	ElderBrother& operator=(ElderBrother&& _Other) noexcept = delete;

protected:

private:

};

