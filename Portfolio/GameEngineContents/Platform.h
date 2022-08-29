#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 5초마다 혼자 알아서 삭제
class Platform : public GameEngineActor
{
public:
    Platform();
    ~Platform();

    Platform(const Platform& _Other)                = delete;
    Platform(Platform&& _Other) noexcept            = delete;
    Platform& operator=(const Platform& _Other)     = delete;
    Platform& operator=(Platform&& _Other) noexcept = delete;

    inline void SetDeathTime(float _Time) { DeathTime_ = _Time; }

    inline MetaTextureRenderer* GetRenderer() { return MetaRenderer_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class MetaTextureRenderer* MetaRenderer_;
    class GameEngineCollision* Collider_;

    float LifeTime_;
    float DeathTime_;
};
