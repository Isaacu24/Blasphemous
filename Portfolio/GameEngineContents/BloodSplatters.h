#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineStateManager.h>

class BloodSplatters : public GameEngineActor
{
public:
    BloodSplatters();
    ~BloodSplatters();

    BloodSplatters(const BloodSplatters& _Other)                = delete;
    BloodSplatters(BloodSplatters&& _Other) noexcept            = delete;
    BloodSplatters& operator=(const BloodSplatters& _Other)     = delete;
    BloodSplatters& operator=(BloodSplatters&& _Other) noexcept = delete;

    inline GameEngineTextureRenderer* GetRenderer() { return Renderer_; }

    inline void SetScale(float _X, float _Y) 
    { 
        Renderer_->GetTransform().SetWorldScale({_X, _Y}); 
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineStateManager State_;

    class GameEngineTextureRenderer* Renderer_;
};
