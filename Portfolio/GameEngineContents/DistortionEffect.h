#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>

struct DistortionData
{
    float AccTime;
    float ScreenXY[2];
    float Offset;
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

    void SetEffectLocalPos(float _Offset) { Data_.Offset = _Offset; }

protected:
    void EffectInit();
    void Effect(class GameEngineRenderTarget* _Target);

private:
    GameEngineRenderSet          EffectSet_;

    GameEngineRenderTarget* CopyTarget_;

    DistortionData Data_;

    float AccTime_;
};
