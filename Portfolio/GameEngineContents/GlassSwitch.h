#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GlassSwitch : public GameEngineActor
{
public:
    GlassSwitch();
    ~GlassSwitch();

    GlassSwitch(const GlassSwitch& _Other)                = delete;
    GlassSwitch(GlassSwitch&& _Other) noexcept            = delete;
    GlassSwitch& operator=(const GlassSwitch& _Other)     = delete;
    GlassSwitch& operator=(GlassSwitch&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* Renderer_;
    GameEngineCollision*       Collider_;
};
