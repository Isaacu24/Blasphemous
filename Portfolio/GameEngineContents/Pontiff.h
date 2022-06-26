#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonsterBase.h"

//�ι�° ��Ȳ
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

