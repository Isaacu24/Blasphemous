#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerFSM
{
	Idle, //������ �������� �ʴ� ����
	Move, //������ �����̴� ����(�� ����ȭ�� ���ɼ��� ����(Jump, Climb...)
	Attack, //������ ���⸦ �ֵθ� ����(�� ����ȭ�� ���ɼ��� ����(ó��)
	Parring, 
	Hit, //�÷��̾ �� ���Ϳ��� ���� ����
	Death //�÷��̾ ���� ����
};

class GameEngineDefaultRenderer;
class Penitent : public GameEngineActor
{
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

	GameEngineDefaultRenderer* DefaultRenderer_;

	PlayerFSM PrevState_;
	PlayerFSM CurrentState_;

	GameEngineDefaultRenderer* Renderer;

	float4 Time_;

	int HP_;
	int MP_;
	int Speed_;

	int Money_; 

	std::vector<bool> Flasks_;
};

