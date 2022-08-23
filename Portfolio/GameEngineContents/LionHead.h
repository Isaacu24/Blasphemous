#pragma once
#include "NormalMonster.h"

class LionHead : public NormalMonster
{
public:
    LionHead();
    ~LionHead();

    LionHead(const LionHead& _Other)                = delete;
    LionHead(LionHead&& _Other) noexcept            = delete;
    LionHead& operator=(const LionHead& _Other)     = delete;
    LionHead& operator=(LionHead&& _Other) noexcept = delete;

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void IdleEnd(const StateInfo& _Info);

    void ReturnStart(const StateInfo& _Info);
    void ReturnUpdate(float _DeltaTime, const StateInfo& _Info);
    void ReturnEnd(const StateInfo& _Info);

    void TrackStart(const StateInfo& _Info);
    void TrackUpdate(float _DeltaTime, const StateInfo& _Info);
    void TrackEnd(const StateInfo& _Info);

    void AttackStart(const StateInfo& _Info);
    void AttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void AttackEnd(const StateInfo& _Info);

    void DeathStart(const StateInfo& _Info);
    void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void DeathEnd(const StateInfo& _Info);

    inline void SetStartPos(const float4& _StartPos) { StartPos_ = _StartPos; }

    bool CrossroadCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void DamageCheck() override;

private:
    float4 StartPos_;

    float4 PlayerPos_;

    float RestTime_;
    bool  IsRest_;

    bool IsHit_;
};
