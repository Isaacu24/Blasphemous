#pragma once
#include "Projectile.h"
#include <GameEngineCore/GameEngineActor.h>

class FireBall
    : public Projectile
    , public GameEngineActor
{
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

    inline void ExplosionEnd(const FrameAnimation_DESC& _Info) { Death(); }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void Shoot(float _DeltaTime) override { GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime); }

private:
};
