#pragma once
#include <GameEngineCore/CoreMinimal.h>

class Penitent : public GameEngineActor
{
private:
	static Penitent* MainPlayer_;

public:
	static Penitent* GetMainPlayer()
	{
		return MainPlayer_;
	}

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

	inline void PlusHP(int _Value)
	{
		HP_ += _Value;

		if (100 < HP_)
		{
			HP_ = 100;
		}
	}

	inline void SerTear(int _Value)
	{
		Tear_ = _Value;
	}

	inline void SetGround(GameEngineTextureRenderer* _Ground)
	{
		ColMap_ = _Ground;
	}

	inline void ChangeState(const std::string& _State)
	{
		State_.ChangeState(_State);
	}

	inline void SetDamege(int _Damage)
	{
		HP_ -= _Damage;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	bool HealthCheck();

	void GroundCheck();
	void LadderCheck();
	void UphillRoadCheck();

	bool LeftObstacleCheck();
	bool RightObstacleCheck();

	void CollisionCheck();

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void CrouchStart(const StateInfo& _Info);
	void CrouchUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrouchEnd(const StateInfo& _Info);

	void FreezeStart(const StateInfo& _Info);
	void FreezeUpdate(float _DeltaTime, const StateInfo& _Info);

	void LadderClimbStart(const StateInfo& _Info);
	void LadderClimbUpdate(float _DeltaTime, const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);

	void SlideStart(const StateInfo& _Info);
	void SlideUpdate(float _DeltaTime, const StateInfo& _Info);
	void SlideEnd(const StateInfo& _Info);

	void RecoveryStart(const StateInfo& _Info);
	void RecoveryUpdate(float _DeltaTime, const StateInfo& _Info);

	void DeathStart(const StateInfo& _Info);
	void DeathUpdate(float _DeltaTime, const StateInfo& _Info);

	void HitStart(const StateInfo& _Info);
	void HitUpdate(float _DeltaTime, const StateInfo& _Info);

	//피격 함수
	bool HitMonster(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool HitProjectile(GameEngineCollision* _This, GameEngineCollision* _Other);

private:
	GameEngineStateManager State_;

	class PlayerUI* PlayerUI_;

	class GravityComponent* Gravity_;
	class GameEngineCollision* Collider_;

	GameEngineTextureRenderer* Renderer_;

	GameEngineTextureRenderer* ColMap_;

	class GameEngineFontRederer* Font_;

	int HP_;
	int MP_;
	float Speed_;

	float4 Dir_;

	int Tear_; 

	bool IsGround_;
	bool IsJump_;
	bool IsLadder_;
	bool IsSlide_;

	float JumpTime_;
	float SlideTime_;

	std::vector<bool> Flasks_;
};

