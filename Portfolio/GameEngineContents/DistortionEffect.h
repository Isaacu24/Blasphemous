#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>

struct DistortionData
{
    float AccTime;
    float ScreenXY[2];
    float fPadding;
};

struct OffsetData
{
    float Offset[2];
    float Padding[2];
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

    void SetScreenPos(float _XPos, float _YPos)
    {
        Data_.ScreenXY[0] = _XPos;
        Data_.ScreenXY[1] = _YPos;
    }

    void SetEffectLocalPos(float _OffsetX, float _OffsetY)
    {
        OffsetData_.Offset[0] = _OffsetX;
        OffsetData_.Offset[1] = _OffsetY;
    }

    void SetDelayTime(float _Delay) { Delay_ = _Delay; }

protected:
    void EffectInit();
    void Effect(class GameEngineRenderTarget* _Target);

private:
    GameEngineRenderSet EffectSet_;

    GameEngineRenderTarget* CopyTarget_;

    DistortionData Data_;
    OffsetData     OffsetData_;

    float AccTime_;
    float Delay_;
};
