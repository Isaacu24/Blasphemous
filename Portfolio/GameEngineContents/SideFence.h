#pragma once
#include <GameEngineCore/GameEngineActor.h>

class SideFence : public GameEngineActor
{
public:
	SideFence();
	~SideFence();

	SideFence(const SideFence& _Other) = delete;
	SideFence(SideFence&& _Other) noexcept = delete;
	SideFence& operator=(const SideFence& _Other) = delete;
	SideFence& operator=(SideFence&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* Rendrerer_;
    GameEngineCollision*       Collider_;
};
