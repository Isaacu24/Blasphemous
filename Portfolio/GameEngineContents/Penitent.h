#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerState
{
	Idle, 
	Run, 
	Fall,
	Jump,
	LadderClimb, //사다리 타기
	Slide, //무적 상태
	Attack, 
	Parring, //무적 상태
	Hit, 
	Death //무적 상태
};

class GameEngineTextureRenderer;
class Penitent : public GameEngineActor
{
public:
	Penitent();
	~Penitent();

	Penitent(const Penitent& _Other) = delete;
	Penitent(Penitent&& _Other) noexcept = delete;
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

	inline void SetGround(GameEngineTextureRenderer* _Ground)
	{
		Ground_ = _Ground;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void InputCheck(float _DeltaTime);

	bool GroundCheck();
	void UphillRoadCheck();
	void LadderCheck();

private:
	PlayerState PrevState_;
	PlayerState CurrentState_;

	float MoveDir_;

	class GravityComponent* Gravity_;

	GameEngineTextureRenderer* Renderer_;

	GameEngineTextureRenderer* Ground_;

	int HP_;
	int MP_;
	float Speed_;

	int Money_; 

	bool IsJump_;

	float JumpTime_;

	std::vector<bool> Flasks_;
};

