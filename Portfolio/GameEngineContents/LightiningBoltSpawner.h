#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "SpawnerBase.h"

enum class BOLTTYPE
{
    Pair,
    Alone
};

class LightiningBoltSpawner 
    : public GameEngineActor
    , public SpawnerBase
{
public:
    LightiningBoltSpawner();
    ~LightiningBoltSpawner();

    LightiningBoltSpawner(const LightiningBoltSpawner& _Other)                = delete;
    LightiningBoltSpawner(LightiningBoltSpawner&& _Other) noexcept            = delete;
    LightiningBoltSpawner& operator=(const LightiningBoltSpawner& _Other)     = delete;
    LightiningBoltSpawner& operator=(LightiningBoltSpawner&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    BOLTTYPE CurType_;

    bool IsStrike_;

    float PosY_;

    class LightiningBolt*  Bolt_;

    float DelayTime_;
    int   StrikeCount_;

    float LimitTime_;
};
