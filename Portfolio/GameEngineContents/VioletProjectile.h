#pragma once
#include <GameEngineCore/GameEngineStateManager.h>
#include "Projectile.h"

class GameEngineCollision;
class GameEngineTextureRenderer;
class VioletProjectile : public Projectile
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

	bool Explosion(GameEngineCollision* _This, GameEngineCollision* _Other)
	{
		State_.ChangeState("Explosion");

		return true;
	}

	inline void ExplosionEnd(const FrameAnimation_DESC& _Info)
	{
		Death();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
};

