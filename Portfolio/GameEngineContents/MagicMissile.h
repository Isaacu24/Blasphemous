#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MagicMissile : public GameEngineActor
{
public:
    MagicMissile();
    ~MagicMissile();

    MagicMissile(const MagicMissile& _Other)                = delete;
    MagicMissile(MagicMissile&& _Other) noexcept            = delete;
    MagicMissile& operator=(const MagicMissile& _Other)     = delete;
    MagicMissile& operator=(MagicMissile&& _Other) noexcept = delete;

    void SetDirection(float4 _Dir) { Dir_ = _Dir; }

    inline void SetSpeed(float _Speed) { Speed_ = _Speed; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void MissileEnd(const FrameAnimation_DESC& _Info) { Death(); }


private:
    GameEngineTextureRenderer* Renderer_;
    GameEngineCollision*       Collider_;

    float Speed_;

    float4 Dir_;
};
