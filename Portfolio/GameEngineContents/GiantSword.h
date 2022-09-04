#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

class GiantSword
    : public GameEngineActor
    , public BossMonster
{
    friend class Pontiff;

public:
    GiantSword();
    ~GiantSword();

    GiantSword(const GiantSword& _Other)                = delete;
    GiantSword(GiantSword&& _Other) noexcept            = delete;
    GiantSword& operator=(const GiantSword& _Other)     = delete;
    GiantSword& operator=(GiantSword&& _Other) noexcept = delete;

    void TeleportINStart(const StateInfo& _Info);
    void TeleportINUpdate(float _DeltaTime, const StateInfo& _Info);
    void TeleportINEnd(const StateInfo& _Info);

    void TeleportOutStart(const StateInfo& _Info);
    void TeleportOutUpdate(float _DeltaTime, const StateInfo& _Info);
    void TeleportOutEnd(const StateInfo& _Info);

    void VisibleStart(const StateInfo& _Info);
    void VisibleUpdate(float _DeltaTime, const StateInfo& _Info);
    void VisibleEnd(const StateInfo& _Info);

    void AttackStart(const StateInfo& _Info);
    void AttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void AttackEnd(const StateInfo& _Info);

    void TrackStart(const StateInfo& _Info);
    void TrackUpdate(float _DeltaTime, const StateInfo& _Info);
    void TrackEnd(const StateInfo& _Info);

    bool LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);
    bool TrackToPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    Pontiff* Pontiff_;

    GameEngineTextureRenderer* IrisRenderer_;  //µ¿°ø
    GameEngineTextureRenderer* EyeRenderer_;   //´«

    inline void SetPontiff(Pontiff* _Pontiff) { Pontiff_ = _Pontiff; }
};
