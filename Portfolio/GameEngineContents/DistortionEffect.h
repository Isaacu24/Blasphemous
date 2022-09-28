#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>

struct DeltaTimeData
{
    float Time;
    float ScreenXY[2];
    int   padding;
};

class DistortionEffect : public GameEnginePostEffect
{
public:
    DistortionEffect();
    ~DistortionEffect();

    DistortionEffect(const DistortionEffect& _Other)                = delete;
    DistortionEffect(DistortionEffect&& _Other) noexcept            = delete;
    DistortionEffect& operator=(const DistortionEffect& _Other)     = delete;
    DistortionEffect& operator=(DistortionEffect&& _Other) noexcept = delete;

    GameEngineRenderTarget* CopyTarget_;


protected:
    void EffectInit();
    void Effect(class GameEngineRenderTarget* _Target);

private:
    GameEngineRenderSet EffectSet_;
    GameEngineRenderingPipeLine* DistortionPipe_;

    DeltaTimeData Data_;
};
