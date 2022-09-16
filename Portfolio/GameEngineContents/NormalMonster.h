#pragma once
#include "MonsterBase.h"
#include <GameEngineCore/GameEngineActor.h>

class Penitent;
class NormalMonster
    : public MonsterBase
    , public GameEngineActor
{
public:
    NormalMonster();
    ~NormalMonster();

    NormalMonster(const NormalMonster& _Other)                = delete;
    NormalMonster(NormalMonster&& _Other) noexcept            = delete;
    NormalMonster& operator=(const NormalMonster& _Other)     = delete;
    NormalMonster& operator=(NormalMonster&& _Other) noexcept = delete;

    inline void PatrolStartEnd(bool _Start, bool _End)
    {
        PatrolStart_ = _Start;
        PatrolEnd_   = _End;
    }

protected:
    void Start() = 0;
    void Update(float _DeltaTime) override;
    void End() override;

    void DamageCheck(float _Damage, float _Offset) override;

    float4 Dir_;

    bool PatrolStart_;
    bool PatrolEnd_;

    bool IsPlayerLeft_;
    bool IsPlayerRight_;

    float TrackLimit_;  // X축 사정거리
    float Crossroad_;

    GameEngineCollision* ExecutionCollider_;

    virtual void PatrolMoveX(float _DeltaTime){};
    virtual void PatrolMoveY(float _DeltaTime){};

    bool LeftObstacleCheck(float _X, float _Y);
    bool RightObstacleCheck(float _X, float _Y);

    virtual bool LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);
    virtual bool TrackPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);

    virtual bool DetectPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);

    virtual bool CrossroadCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

    virtual bool ExecutionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

    inline void SetTrackDistance(float _Distance) { TrackLimit_ = _Distance; }

    inline void SetCrossroad(float _Distance) { Crossroad_ = _Distance; }

private:
};
