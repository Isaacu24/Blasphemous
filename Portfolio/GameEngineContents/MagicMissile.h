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

    inline void SetWeight(float _Speed) { Weight_ = _Speed; }

    inline void SetStartPosition(float4 _Pos) { StartPos_ = _Pos; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* Renderer_;
    GameEngineCollision*       Collider_;

    float Speed_;
    float Weight_;

    float4 StartPos_;

    bool IsExplosion_;

    float4 Dir_;
};
