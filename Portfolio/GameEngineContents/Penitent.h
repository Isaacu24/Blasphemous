#pragma once
#include <GameEngineCore/CoreMinimal.h>

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

	void PixelCheck();

	void GroundCheck();
	void LadderCheck();
	void UphillRoadCheck();

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void LadderClimbStart(const StateInfo& _Info);
	void LadderClimbUpdate(float _DeltaTime, const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);


private:
	GameEngineStateManager StateManager_;

	class PlayerUI* PlayerUI_;

	class GravityComponent* Gravity_;

	GameEngineTextureRenderer* Renderer_;

	GameEngineTextureRenderer* Ground_;

	float4 MoveDir_;

	int HP_;
	int MP_;
	float Speed_;

	int Money_; 

	bool IsGround_;
	bool IsJump_;
	bool IsLadder_;

	float JumpTime_;

	std::vector<bool> Flasks_;
};

