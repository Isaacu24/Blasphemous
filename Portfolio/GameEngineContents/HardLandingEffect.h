#pragma once
#include <GameEngineCore/GameEngineActor.h>

class HardLandingEffect : public GameEngineActor
{
public:
    HardLandingEffect();
    ~HardLandingEffect();

    HardLandingEffect(const HardLandingEffect& _Other)                = delete;
    HardLandingEffect(HardLandingEffect&& _Other) noexcept            = delete;
    HardLandingEffect& operator=(const HardLandingEffect& _Other)     = delete;
    HardLandingEffect& operator=(HardLandingEffect&& _Other) noexcept = delete;

    MetaTextureRenderer* GetRenderer() { return Renderer_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class MetaTextureRenderer* Renderer_;
};
