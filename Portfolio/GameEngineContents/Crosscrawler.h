#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "NormalMonster.h"

class Crosscrawler : public GameEngineActor, public NormalMonster
{
public:
	Crosscrawler();
	~Crosscrawler();

	Crosscrawler(const Crosscrawler& _Other) = delete;
	Crosscrawler(Crosscrawler&& _Other) noexcept = delete;
	Crosscrawler& operator=(const Crosscrawler& _Other) = delete;
	Crosscrawler& operator=(Crosscrawler&& _Other) noexcept = delete;

protected:

private:

};

