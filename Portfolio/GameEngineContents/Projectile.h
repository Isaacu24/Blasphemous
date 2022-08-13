#pragma once
#include <GameEngineCore/GameEngineStateManager.h>

class GameEngineCollision;
class GameEngineTextureRenderer;
class Projectile 
{
public:
    Projectile();
    ~Projectile();

    Projectile(const Projectile& _Other)                = delete;
    Projectile(Projectile&& _Other) noexcept            = delete;
    Projectile& operator=(const Projectile& _Other)     = delete;
    Projectile& operator=(Projectile&& _Other) noexcept = delete;

    virtual void SetGround(GameEngineTextureRenderer* _Texture) { ColMap_ = _Texture; }

    virtual void SetDirection(float4 _Dir)
    {
        Dir_ = _Dir;

        if (0 < Dir_.x)
        {
            Renderer_->GetTransform().PixLocalPositiveX();
        }

        else if (0 > Dir_.x)
        {
            Renderer_->GetTransform().PixLocalNegativeX();
        }
    }

    virtual void SetSpeed(float _Speed) { Speed_ = _Speed; }

protected:
    GameEngineStateManager     State_;
    GameEngineTextureRenderer* Renderer_;

    GameEngineCollision* Collider_;

    GameEngineTextureRenderer* ColMap_;

    float4 Dir_;
    float  Speed_;

    virtual void Shoot(float _DeltaTime){};

private:

};
