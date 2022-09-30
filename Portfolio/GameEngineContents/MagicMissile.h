#pragma once
#include "Projectile.h"
#include <GameEngineCore/GameEngineActor.h>

class MagicMissile : public Projectile
{
public:
    MagicMissile();
    ~MagicMissile();

    MagicMissile(const MagicMissile& _Other)                = delete;
    MagicMissile(MagicMissile&& _Other) noexcept            = delete;
    MagicMissile& operator=(const MagicMissile& _Other)     = delete;
    MagicMissile& operator=(MagicMissile&& _Other) noexcept = delete;

    virtual void SetDirection(float4 _Dir)
    {
        if (0 > _Dir.x)
        {
            GetTransform().PixLocalNegativeX();
        }

        else
        {
            GetTransform().PixLocalPositiveX();
        }

        Dir_ = _Dir;
    }

    inline void SetWeight(float _Speed) { Weight_ = _Speed; }

    inline void SetStartPosition(float4 _Pos) { StartPos_ = _Pos; }

    void ShootStart(const StateInfo& _Info);
    void ShootUpdate(float _DeltaTime, const StateInfo& _Info);
    void ShootEnd(const StateInfo& _Info);

    void ExplosionStart(const StateInfo& _Info);
    void ExplosionUpdate(float _DeltaTime, const StateInfo& _Info);
    void ExplosionEnd(const StateInfo& _Info);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* Renderer_;
    GameEngineCollision*       Collider_;

    float4 StartPos_;
    float4 Dir_;

    float Weight_;

    bool IsExplosion_;

};
