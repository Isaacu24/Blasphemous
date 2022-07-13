#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerFSM
{
	Idle, //유저가 조작하지 않는 상태
	Move, //유저가 움직이는 상태(더 세분화될 가능성이 높다(Jump, Climb...)
	Attack, //유저가 무기를 휘두른 상태(더 세분화될 가능성이 높다(처형)
	Parring, 
	Hit, //플레이어가 적 몬스터에게 맞은 상태
	Death //플레이어가 죽은 상태
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

