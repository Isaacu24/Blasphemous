#pragma once

enum class MonsterFSM
{
	Idle, //�̵� ����
	Move, //�÷��̾� ���� ����
	//���� �غ� ����?
	Attack, //�÷��̾� ���� ����
	Hit, //�ǰ� ����
	Death //���� ����
};

//�Ϲ� ������ �⺻���� ������ ���� Ŭ����
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

	int Money_; //�÷��̾�� ������ ��
};

