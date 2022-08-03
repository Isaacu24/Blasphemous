#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

//첫 번째 교황
class Pope : public GameEngineActor, public BossMonster
{
public:
	Pope();
	~Pope();

	Pope(const Pope& _Other) = delete;
	Pope(Pope&& _Other) noexcept = delete;
	Pope& operator=(const Pope& _Other) = delete;
	Pope& operator=(Pope&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

	bool DecideState(GameEngineCollision* _This, GameEngineCollision* _Other);
};

