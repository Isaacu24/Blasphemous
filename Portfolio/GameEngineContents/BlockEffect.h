#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BlockEffect : public GameEngineActor
{
    friend class ShieldMaiden;

public:
	BlockEffect();
	~BlockEffect();

	BlockEffect(const BlockEffect& _Other) = delete;
	BlockEffect(BlockEffect&& _Other) noexcept = delete;
	BlockEffect& operator=(const BlockEffect& _Other) = delete;
	BlockEffect& operator=(BlockEffect&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class MetaTextureRenderer* Renderer_;

};

