#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "NormalMonster.h"

class Fool_knife : public GameEngineActor, public NormalMonster
{
public:
	Fool_knife();
	~Fool_knife();

	Fool_knife(const Fool_knife& _Other) = delete;
	Fool_knife(Fool_knife&& _Other) noexcept = delete;
	Fool_knife& operator=(const Fool_knife& _Other) = delete;
	Fool_knife& operator=(Fool_knife&& _Other) noexcept = delete;

protected:

private:

};

