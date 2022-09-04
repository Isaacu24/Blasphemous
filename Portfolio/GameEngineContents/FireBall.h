#pragma once
#include "Projectile.h"
#include <GameEngineCore/GameEngineActor.h>

class FireBall
    : public Projectile
    , public GameEngineActor
{
    friend class FireBallSpawner;

public:
    FireBall();
    ~FireBall();

    FireBall(const FireBall& _Other)                = delete;
    FireBall(FireBall&& _Other) noexcept            = delete;
    FireBall& operator=(const FireBall& _Other)     = delete;
    FireBall& operator=(FireBall&& _Other) noexcept = delete;

    void ShootStart(const StateInfo& _Info);
    void ShootUpdate(float _DeltaTime, const StateInfo& _Info);

    void ExplosionStart(const StateInfo& _Info);
    void ExplosionUpdate(float _DeltaTime, const StateInfo& _Info);

    bool Explosion(GameEngineCollision* _This, GameEngineCollision* _Other)
    {
        State_.ChangeState("Explosion");

        return true;
    }

    inline void SetWeight(float _Value) { Weight_ = _Value; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void Shoot(float _DeltaTime) override
    {
        Speed_ += _DeltaTime * Weight_;
        GetTransform().SetWorldMove({(Dir_.x * Speed_ * _DeltaTime), (Dir_.y * Speed_ * _DeltaTime)});
    }

    void SetDirection(float4 _Dir) override { Dir_ = _Dir; };

private:
    MetaTextureRenderer* MetaRenderer_;

    float Weight_;
};
