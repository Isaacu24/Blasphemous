#pragma once
#include "NormalMonster.h"

class Crosscrawler : public NormalMonster
{
public:
    Crosscrawler();
    ~Crosscrawler();

    Crosscrawler(const Crosscrawler& _Other)                = delete;
    Crosscrawler(Crosscrawler&& _Other) noexcept            = delete;
    Crosscrawler& operator=(const Crosscrawler& _Other)     = delete;
    Crosscrawler& operator=(Crosscrawler&& _Other) noexcept = delete;

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void IdleEnd(const StateInfo& _Info);

    void PatrolStart(const StateInfo& _Info);
    void PatrolUpdate(float _DeltaTime, const StateInfo& _Info);
    void PatrolEnd(const StateInfo& _Info);

    void TurnStart(const StateInfo& _Info);
    void TurnUpdate(float _DeltaTime, const StateInfo& _Info);
    void TurnEnd(const StateInfo& _Info);

    void TrackStart(const StateInfo& _Info);
    void TrackUpdate(float _DeltaTime, const StateInfo& _Info);
    void TrackEnd(const StateInfo& _Info);

     void AttackStart(const StateInfo& _Info);
     void AttackUpdate(float _DeltaTime, const StateInfo& _Info);
     void AttackEnd(const StateInfo& _Info);

     void StunStart(const StateInfo& _Info);
     void StunUpdate(float _DeltaTime, const StateInfo& _Info);
     void StunEnd(const StateInfo& _Info);

     void ExecutionStart(const StateInfo& _Info);
     void ExecutionUpdate(float _DeltaTime, const StateInfo& _Info);
     void ExecutionEnd(const StateInfo& _Info);

     void DeathStart(const StateInfo& _Info);
     void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
     void DeathEnd(const StateInfo& _Info);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void PatrolMoveX(float _DeltaTime) override;

    // bool LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other) override;

private:
};
