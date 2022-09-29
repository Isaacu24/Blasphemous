#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>

struct DistortionData
{
    float AccTime;
    float ScreenXY[2];
    float WaveProgress;
};

class SinWaveEffect : public GameEnginePostEffect
{
public:
    SinWaveEffect();
    ~SinWaveEffect();

    SinWaveEffect(const SinWaveEffect& _Other)                = delete;
    SinWaveEffect(SinWaveEffect&& _Other) noexcept            = delete;
    SinWaveEffect& operator=(const SinWaveEffect& _Other)     = delete;
    SinWaveEffect& operator=(SinWaveEffect&& _Other) noexcept = delete;

protected:
    void EffectInit();
    void Effect(class GameEngineRenderTarget* _Target);

private:
    GameEngineRenderSet EffectSet_;

    GameEngineRenderTarget* CopyTarget_;

    DistortionData Data_;

    float AccTime_;
};
