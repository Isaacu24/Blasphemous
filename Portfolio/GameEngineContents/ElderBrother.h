#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"
#include "AttackCorpseEffecter.h"
#include "JumpCorpseEffecter.h"
#include "GravityActor.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "MetaTextureRenderer.h"

enum class APPEARFLOW
{
    Attack,
    JumpStart,
    Jump,
    Fall,
    Appear
};

class GravityActor;
class JumpCorpseEffecter;
class AttackCorpseEffecter;
class ElderBrother
    : public GameEngineActor
    , public BossMonster
{
public:
    ElderBrother();
    ~ElderBrother();

    ElderBrother(const ElderBrother& _Other)                = delete;
    ElderBrother(ElderBrother&& _Other) noexcept            = delete;
    ElderBrother& operator=(const ElderBrother& _Other)     = delete;
    ElderBrother& operator=(ElderBrother&& _Other) noexcept = delete;

    void AppearStart(const StateInfo& _Info);
    void AppearUpdate(float _DeltaTime, const StateInfo& _Info);
    void AppearEnd(const StateInfo& _Info);

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void IdleEnd(const StateInfo& _Info);

    void JumpStart(const StateInfo& _Info);
    void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
    void JumpEnd(const StateInfo& _Info);

    void FallStart(const StateInfo& _Info);
    void FallUpdate(float _DeltaTime, const StateInfo& _Info);
    void FallEnd(const StateInfo& _Info);

    void LandStart(const StateInfo& _Info);
    void LandUpdate(float _DeltaTime, const StateInfo& _Info);
    void LandEnd(const StateInfo& _Info);

    void AttackStart(const StateInfo& _Info);
    void AttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void AttackEnd(const StateInfo& _Info);

    void DeathStart(const StateInfo& _Info);
    void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void DeathEnd(const StateInfo& _Info);

    bool DetectPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);

    inline void ChangeState(const std::string& _State) { State_.ChangeState(_State); }

    inline void EventOn() { EventOn_ = true; }

    inline bool GetDeathEvent() { return DeathEventOn_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void DamageCheck() override;

private:
    float4 Dir_;

    AttackCorpseEffecter* AttackEffecter_;
    JumpCorpseEffecter*   JumpEffecter_;

    GravityActor* AffectChecker;

    class HardLandingEffect* LandEffect_;

    float4 Target_;

    APPEARFLOW Flow_;

    bool IsDecide_;

    float4 JumpForce_;

    float DecideTime_;
    float JumpHoldTime_;

    float RealXDir_;

    float Alpha_;
    bool  IsJump_;
    bool  EventOn_;
    bool  DeathEventOn_;

    float Distance_;

    int AttackCount_;

    GameEngineRandom Random_;
};
