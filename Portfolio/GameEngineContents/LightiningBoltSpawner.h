#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BOLTTYPE
{
    Pair,
    Alone
};

class LightiningBoltSpawner : public GameEngineActor
{
public:
    LightiningBoltSpawner();
    ~LightiningBoltSpawner();

    LightiningBoltSpawner(const LightiningBoltSpawner& _Other)                = delete;
    LightiningBoltSpawner(LightiningBoltSpawner&& _Other) noexcept            = delete;
    LightiningBoltSpawner& operator=(const LightiningBoltSpawner& _Other)     = delete;
    LightiningBoltSpawner& operator=(LightiningBoltSpawner&& _Other) noexcept = delete;

    inline void Strike() { IsStrike_ = true; }

    inline void SetTarget(GameEngineActor* _Target) { Target_ = _Target; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    BOLTTYPE CurType_;

    bool IsStrike_;

    float PosY_;

    GameEngineActor* Target_;

    float DelayTime_;
    int   StrikeCount_;
};
