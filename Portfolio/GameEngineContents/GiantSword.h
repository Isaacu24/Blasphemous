#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

enum class GiantSwordState
{

};

class GiantSword : public GameEngineActor, public BossMonster
{
public:
	GiantSword();
	~GiantSword();

	GiantSword(const GiantSword& _Other) = delete;
	GiantSword(GiantSword&& _Other) noexcept = delete;
	GiantSword& operator=(const GiantSword& _Other) = delete;
	GiantSword& operator=(GiantSword&& _Other) noexcept = delete;

	void TeleportINStart(const StateInfo& _Info);
	void TeleportINUpdate(float _DeltaTime, const StateInfo& _Info);

	void TeleportOutStart(const StateInfo& _Info);
	void TeleportOutUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackStart(const StateInfo& _Info);
	void AttackUpdate(float _DeltaTime, const StateInfo& _Info);
	void AttackEnd(const StateInfo& _Info);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GiantSwordState CurrentState_;

	GameEngineTextureRenderer* IrisRenderer_; //µ¿°ø
	GameEngineTextureRenderer* EyeRenderer_; //´«
	GameEngineTextureRenderer* EyeLidRenderer_; //´«²¨Ç®(Animation

	float Time_;

};

