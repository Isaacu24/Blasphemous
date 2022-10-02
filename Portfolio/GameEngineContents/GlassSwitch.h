#pragma once
#include "ObjectBase.h"

class GlassSwitch : public ObjectBase
{
    friend class SideFence;

public:
    GlassSwitch();
    ~GlassSwitch();

    GlassSwitch(const GlassSwitch& _Other)                = delete;
    GlassSwitch(GlassSwitch&& _Other) noexcept            = delete;
    GlassSwitch& operator=(const GlassSwitch& _Other)     = delete;
    GlassSwitch& operator=(GlassSwitch&& _Other) noexcept = delete;

    void SetSideFence(SideFence* _Fence) { Fence_ = _Fence; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* Renderer_;
    GameEngineCollision*       Collider_;

    SideFence* Fence_;

    bool On(GameEngineCollision* _This, GameEngineCollision* _Other);
};
