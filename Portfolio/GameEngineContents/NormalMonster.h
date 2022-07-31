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

	inline void SetPatrolStart(bool _Start)
	{
		PatrolStart_ = _Start;
	}

	inline void SetPatrolEnd(bool _End)
	{
		PatrolEnd_ = _End;
	}

protected:
	bool PatrolStart_;
	bool PatrolEnd_;

	virtual void PatrolMoveX() {};

	bool LeftObstacleCheck(int _X, int _Y);
	bool RightObstacleCheck(int _X, int _Y);

private:
};

