#pragma once
#include <GameEngineCore/GameEngineStateManager.h>
#include "Projectile.h"
#include <GameEngineCore/GameEngineActor.h>

class GameEngineCollision;
class GameEngineTextureRenderer;
class VioletProjectile : public Projectile, public GameEngineActor
{
public:
    VioletProjectile();
    ~VioletProjectile();

	VioletProjectile(const VioletProjectile& _Other)          = delete;
    VioletProjectile(VioletProjectile&& _Other) noexcept      = delete;
    VioletProjectile& operator=(const VioletProjectile& _Other) = delete;
    VioletProjectile& operator=(VioletProjectile&& _Other) noexcept = delete;
	
	void ShootStart(const StateInfo& _Info);
	void ShootUpdate(float _DeltaTime, const StateInfo& _Info);

	void ExplosionStart(const StateInfo& _Info);
	void ExplosionUpdate(float _DeltaTime, const StateInfo& _Info);
    void ExplosionEnd(const StateInfo& _Info);

	bool Explosion(GameEngineCollision* _This, GameEngineCollision* _Other)
	{
        IsExplosion_ = true;
		State_.ChangeState("Explosion");
		return true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	
	void Shoot(float _DeltaTime) override
	{ 
        GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime); 
    }

private:

};

