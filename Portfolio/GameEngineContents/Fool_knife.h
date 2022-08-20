#pragma once
#include "NormalMonster.h"

class Fool_knife : public NormalMonster
{
public:
    Fool_knife();
    ~Fool_knife();

    Fool_knife(const Fool_knife& _Other)                = delete;
    Fool_knife(Fool_knife&& _Other) noexcept            = delete;
    Fool_knife& operator=(const Fool_knife& _Other)     = delete;
    Fool_knife& operator=(Fool_knife&& _Other) noexcept = delete;

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

    void PatrolStart(const StateInfo& _Info);
    void PatrolUpdate(float _DeltaTime, const StateInfo& _Info);

    void TrackStart(const StateInfo& _Info);
    void TrackUpdate(float _DeltaTime, const StateInfo& _Info);

    void HurtStart(const StateInfo& _Info);
    void HurtUpdate(float _DeltaTime, const StateInfo& _Info);

    void TurnStart(const StateInfo& _Info);
    void TurnUpdate(float _DeltaTime, const StateInfo& _Info);

    void DeathStart(const StateInfo& _Info);
    void DeathUpdate(float _DeltaTime, const StateInfo& _Info);

    inline void TurnEnd(const FrameAnimation_DESC& _Info)
    {
        ChangeMonsterState("Patrol");
    }

    inline void DeathEnd(const FrameAnimation_DESC& _Info) { Death(); }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void PatrolMoveX(float _DeltaTime) override;

private:
    float4 Dir_;
};
