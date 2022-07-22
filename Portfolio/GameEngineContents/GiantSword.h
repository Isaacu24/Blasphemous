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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GiantSwordState CurrentState_;

	class GameEngineTextureRenderer* Renderer_;
};

