#pragma once

//몬스터의 기본적인 클래스
class MonsterBase
{
public:
	MonsterBase();
	~MonsterBase();

	MonsterBase(const MonsterBase& _Other) = delete;
	MonsterBase(MonsterBase&& _Other) noexcept = delete;
	MonsterBase& operator=(const MonsterBase& _Other) = delete;
	MonsterBase& operator=(MonsterBase&& _Other) noexcept = delete;

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

	inline int GetMoney()
	{
		return Money_;
	}

protected:

private:
	int HP_;
	int Speed_;

	int Money_; //플레이어에게 전달한 돈
};

