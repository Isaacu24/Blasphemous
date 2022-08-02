#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineStateManager.h>

class GameEngineTextureRenderer;
class GameEngineCollision;
class Projectile : public GameEngineActor
{
public:
	Projectile();
	~Projectile();

	Projectile(const Projectile& _Other) = delete;
	Projectile(Projectile&& _Other) noexcept = delete;
	Projectile& operator=(const Projectile& _Other) = delete;
	Projectile& operator=(Projectile&& _Other) noexcept = delete;

	void ShootStart(const StateInfo& _Info);
	void ShootUpdate(float _DeltaTime, const StateInfo& _Info);

	void ExplosionStart(const StateInfo& _Info);
	void ExplosionUpdate(float _DeltaTime, const StateInfo& _Info);

	void Shoot(float _DeltaTime);

	bool Explosion(GameEngineCollision* _This, GameEngineCollision* _Other)
	{
		State_.ChangeState("Explosion");

		return true;
	}

	void SetGround(GameEngineTextureRenderer* _Texture)
	{
		ColMap_ = _Texture;
	}

	inline void SetDirection(float4 _Dir)
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

	inline void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
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
	GameEngineStateManager State_;
	GameEngineTextureRenderer* Renderer_;

	GameEngineCollision* Collider_;

	GameEngineTextureRenderer* ColMap_;

	float4 Dir_;
	float Speed_;
};

