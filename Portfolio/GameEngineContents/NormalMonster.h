#pragma once
#include "MonsterBase.h"

//ó�� ����̳� �и� ���׼��� �ִ� ���Ͱ� ���⵵ ��
enum class MonsterFSM
{
	Idle, //�̵� Ȥ�� ���� ����
	Follow, //�÷��̾� ���� ����
	Attack, //�÷��̾� ���� ����
	ParryReaction,
	Stun,
	Hit, //�ǰ� ����
	Death //���� ����
};

class NormalMonster : public MonsterBase
{
public:
	NormalMonster();
	~NormalMonster();

	NormalMonster(const NormalMonster& _Other) = delete;
	NormalMonster(NormalMonster&& _Other) noexcept = delete;
	NormalMonster& operator=(const NormalMonster& _Other) = delete;
	NormalMonster& operator=(NormalMonster&& _Other) noexcept = delete;

	inline void SetCurrentState(MonsterFSM _State)
	{
		CurrentState_ = _State;
	}

	inline MonsterFSM GetCurrentState()
	{
		return CurrentState_;
	}

	inline MonsterFSM GetPrevState()
	{
		return PrevState_;
	}

protected:

private:
	MonsterFSM PrevState_;
	MonsterFSM CurrentState_;


};

