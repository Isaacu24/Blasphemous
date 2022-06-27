#pragma once
#include "MonsterBase.h"

enum class MonsterFSM
{
	Idle, //이동 혹은 정지 상태
	Follow, //플레이어 추적 상태
	Attack, //플레이어 공격 상태
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

