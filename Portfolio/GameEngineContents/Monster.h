#pragma once

enum class MonsterFSM
{
	Idle, //이동 상태
	Move, //플레이어 추적 상태
	//공격 준비 상태?
	Attack, //플레이어 공격 상태
	Hit, //피격 상태
	Death //죽음 상태
};

//일반 몬스터의 기본적인 정보를 가진 클래스
class Monster
{
public:
	Monster();
	~Monster();

	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	inline void SetHP(int _Value)
	{
		HP_ = _Value;
	}

	inline int GetHP()
	{
		return HP_;
	}

	inline void SetMoney(int _Value)
	{
		Money_ = _Value;
	}

protected:

private:
	MonsterFSM CurrentState_;

	int HP_;
	int Speed_;

	int Money_; //플레이어에게 전달한 돈
};

