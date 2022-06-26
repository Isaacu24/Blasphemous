#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonsterBase.h"

//두번째 교황
class Pontiff : public GameEngineActor, public BossMonsterBase
{
public:
	Pontiff();
	~Pontiff();

	Pontiff(const Pontiff& _Other) = delete;
	Pontiff(Pontiff&& _Other) noexcept = delete;
	Pontiff& operator=(const Pontiff& _Other) = delete;
	Pontiff& operator=(Pontiff&& _Other) noexcept = delete;

protected:

private:

};

