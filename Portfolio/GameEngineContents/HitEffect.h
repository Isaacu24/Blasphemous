#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MetaTextureRenderer;
class HitEffect : public GameEngineActor
{
    friend class Penitent;

public:
	HitEffect();
	~HitEffect();

	HitEffect(const HitEffect& _Other) = delete;
	HitEffect(HitEffect&& _Other) noexcept = delete;
	HitEffect& operator=(const HitEffect& _Other) = delete;
	HitEffect& operator=(HitEffect&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    MetaTextureRenderer* Renderer_;
};

