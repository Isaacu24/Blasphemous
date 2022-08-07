#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

class AttackCorpseEffecter;
class ElderBrother : public GameEngineActor, public BossMonster
{
public:
	ElderBrother();
	~ElderBrother();

	ElderBrother(const ElderBrother& _Other) = delete;
	ElderBrother(ElderBrother&& _Other) noexcept = delete;
	ElderBrother& operator=(const ElderBrother& _Other) = delete;
	ElderBrother& operator=(ElderBrother&& _Other) noexcept = delete;

	void FreezeStart(const StateInfo& _Info);
	void FreezeUpdate(float _DeltaTime, const StateInfo& _Info);

	void AppearStart(const StateInfo& _Info);
	void AppearUpdate(float _DeltaTime, const StateInfo& _Info);

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackStart(const StateInfo& _Info);
	void AttackUpdate(float _DeltaTime, const StateInfo& _Info);

	void DeathStart(const StateInfo& _Info);
	void DeathUpdate(float _DeltaTime, const StateInfo& _Info);

	bool DecideState(GameEngineCollision* _This, GameEngineCollision* _Other);

	inline void ChangeIdle(const FrameAnimation_DESC& _Info)
	{
		State_.ChangeState("Idle");
	}

	inline void ChangeState(const std::string& _State)
	{
		State_.ChangeState(_State);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	float4 Dir_;

	AttackCorpseEffecter* AttackEffecter_;

	bool IsDecide_;

	float DecideTime_;
	float AppearTime_;

};

