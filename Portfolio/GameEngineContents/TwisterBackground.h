#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TwisterBackground : public GameEngineActor
{
public:
    TwisterBackground();
    ~TwisterBackground();

    TwisterBackground(const TwisterBackground& _Other)                = delete;
    TwisterBackground(TwisterBackground&& _Other) noexcept            = delete;
    TwisterBackground& operator=(const TwisterBackground& _Other)     = delete;
    TwisterBackground& operator=(TwisterBackground&& _Other) noexcept = delete;

    inline GameEngineTextureRenderer* GetRenderer() { return Renderer_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class GameEngineTextureRenderer* Renderer_;
};
