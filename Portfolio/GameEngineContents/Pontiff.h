#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

enum class PontiffState
{
	OpenIdle,
	CloseIdle,
	Death
};

//�ι�° ��Ȳ
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


//�÷��� ������ Ŭ������ ������ ��. 
//�װ� �÷���������(Ȥ�� ��������. �ٵ� �Ƹ� ���� Ŭ������ ����� ���� ����.)�� �� ��. 
//��Ȳ�� ���� �ȴ�.