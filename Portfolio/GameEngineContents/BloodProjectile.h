#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BloodProjectile : public GameEngineActor
{
public:
    BloodProjectile();
    ~BloodProjectile();

    BloodProjectile(const BloodProjectile& _Other)                = delete;
    BloodProjectile(BloodProjectile&& _Other) noexcept            = delete;
    BloodProjectile& operator=(const BloodProjectile& _Other)     = delete;
    BloodProjectile& operator=(BloodProjectile&& _Other) noexcept = delete;

    inline void SetDirection(float Dir)
    {
        if (0 > Dir)
        {
            Dir_ = float4::LEFT;
            GetTransform().PixLocalNegativeX();
        }

        else
        {
            Dir_ = float4::RIGHT;
            GetTransform().PixLocalPositiveX();
        }

        StartPos_ = GetTransform().GetWorldPosition();
    }

    inline void SetGround(GameEngineTextureRenderer* _ColMap) { ColMap_ = _ColMap; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void ShootStart(const StateInfo& _Info);
    void ShootUpdate(float _DeltaTime, const StateInfo& _Info);
    void ShootEnd(const StateInfo& _Info);

    void ExplodeStart(const StateInfo& _Info);
    void ExplodeUpdate(float _DeltaTime, const StateInfo& _Info);
    void ExplodeEnd(const StateInfo& _Info);

    void VanishStart(const StateInfo& _Info);
    void VanishUpdate(float _DeltaTime, const StateInfo& _Info);
    void VanishEnd(const StateInfo& _Info);

    void MonsterCheck();

private:
    class MetaTextureRenderer* MetaRenderer_;

    GameEngineStateManager State_;

    class GameEngineCollision* Collider_;

    class GameEngineTextureRenderer* ColMap_;

    float4 Dir_;

    float4 StartPos_;

    GameEngineSoundPlayer SoundPlayer_;
};
