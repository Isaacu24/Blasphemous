#pragma once
#include <GameEngineCore/GameEngineActor.h>

class LightiningBolt : public GameEngineActor
{
public:
    LightiningBolt();
    ~LightiningBolt();

    LightiningBolt(const LightiningBolt& _Other)                = delete;
    LightiningBolt(LightiningBolt&& _Other) noexcept            = delete;
    LightiningBolt& operator=(const LightiningBolt& _Other)     = delete;
    LightiningBolt& operator=(LightiningBolt&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;


private:
    GameEngineTextureRenderer* Renderer_;
    GameEngineTextureRenderer* FXSRenderer_;

    GameEngineCollision* Collider_;

    void StrikeEnd(const FrameAnimation_DESC& _Info) { Death(); }
};
