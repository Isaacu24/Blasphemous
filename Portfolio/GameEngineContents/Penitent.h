#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerFSM
{
	Idle, //������ �������� �ʴ� ����
	Move, //������ �����̴� ����(�� ����ȭ�� ���ɼ��� ����(Jump, Climb...)
	Attack, //������ ���⸦ �ֵθ� ����(�� ����ȭ�� ���ɼ��� ����(ó��)
	Hit, //�÷��̾ �� ���Ϳ��� ���� ����
	Death //�÷��̾ ���� ����
};

// �÷��̾�� Static�� ���ϴ�
class Penitent : public GameEngineActor
{
public:
	static Penitent* Player_;

	friend class Flask;

	class Flask 
	{
	public:
		Flask()
		: Value_(0) 
		{

		}
		~Flask() 
		{

		}

		void SetValue();	
		void Recovery();

	private:
		int Value_;
	};

public:
	Penitent();
	~Penitent();

	Penitent(const Penitent& _Other) = delete;
	Penitent(Penitent&& _Other) noexcept = delete;
	Penitent& operator=(const Penitent& _Other) = delete;
	Penitent& operator=(Penitent&& _Other) noexcept = delete;

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
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	PlayerFSM PrevState_;
	PlayerFSM CurrentState_;

	int HP_;
	int MP_;
	int Speed_;

	int Money_; 

	//�ö�ũ
	Flask Flasks_[2];

	//������ ����Ʈ
};

