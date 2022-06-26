#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonsterBase.h"

//첫 번째 교황
class Pope : public GameEngineActor, public BossMonsterBase
{
public:
	Pope();
	~Pope();

	Pope(const Pope& _Other) = delete;
	Pope(Pope&& _Other) noexcept = delete;
	Pope& operator=(const Pope& _Other) = delete;
	Pope& operator=(Pope&& _Other) noexcept = delete;

protected:

private:

};

