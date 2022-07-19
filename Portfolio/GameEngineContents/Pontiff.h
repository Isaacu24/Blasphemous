#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

enum class PontiffState
{
	OpenIdle,
	CloseIdle,
	Death
};

//두번째 교황
class Pontiff : public GameEngineActor, public BossMonster
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


//플랫폼 생성기 클래스도 만들어야 함. 
//그건 플랫폼스포너(혹은 스테이지. 근데 아마 따로 클래스를 만드는 편이 좋다.)가 할 일. 
//교황은 몰라도 된다.