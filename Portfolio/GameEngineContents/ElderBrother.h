#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

enum class ElderState
{
	Idle,
	Jump,
	Attack,
	Death
};

class ElderBrother : public GameEngineActor, public BossMonster
{
public:
	ElderBrother();
	~ElderBrother();

	ElderBrother(const ElderBrother& _Other) = delete;
	ElderBrother(ElderBrother&& _Other) noexcept = delete;
	ElderBrother& operator=(const ElderBrother& _Other) = delete;
	ElderBrother& operator=(ElderBrother&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	ElderState CurrentState_;

};

