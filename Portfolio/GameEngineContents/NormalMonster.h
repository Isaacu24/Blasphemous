#pragma once
#include "MonsterBase.h"

//처형 모션이나 패링 리액션이 있는 몬스터가 없기도 함
enum class MonsterFSM
{
	Idle, //이동 혹은 정지 상태
	Follow, //플레이어 추적 상태
	Attack, //플레이어 공격 상태
	ParryReaction,
	Stun,
	Hit, //피격 상태
	Death //죽음 상태
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

