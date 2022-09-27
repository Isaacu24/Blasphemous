#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Cloud : public GameEngineActor
{
public:
    Cloud();
    ~Cloud();

    Cloud(const Cloud& _Other)                = delete;
    Cloud(Cloud&& _Other) noexcept            = delete;
    Cloud& operator=(const Cloud& _Other)     = delete;
    Cloud& operator=(Cloud&& _Other) noexcept = delete;

    void SetDirection(float4 _Dir) { Dir_ = _Dir; }

    GameEngineTextureRenderer* GetRenderer() { return Renderer_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class GameEngineTextureRenderer* Renderer_;
    float4                           Dir_;

    float AccSpeed_;
};
