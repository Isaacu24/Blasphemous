#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

//첫 번째 교황
class Pope : public GameEngineActor, public BossMonster
{
public:
	Pope();
	~Pope();

	Pope(const Pope& _Other) = delete;
	Pope(Pope&& _Other) noexcept = delete;
	Pope& operator=(const Pope& _Other) = delete;
	Pope& operator=(Pope&& _Other) noexcept = delete;

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void IdleEnd(const StateInfo& _Info);

    void AppearStart(const StateInfo& _Info);
    void AppearUpdate(float _DeltaTime, const StateInfo& _Info);
    void AppearEnd(const StateInfo& _Info);

    void VanishingStart(const StateInfo& _Info);
    void VanishingUpdate(float _DeltaTime, const StateInfo& _Info);
    void VanishingEnd(const StateInfo& _Info);

    void SpellCastStart(const StateInfo& _Info);
    void SpellCastUpdate(float _DeltaTime, const StateInfo& _Info);
    void SpellCastEnd(const StateInfo& _Info);

    void HitStart(const StateInfo& _Info);
    void HitUpdate(float _DeltaTime, const StateInfo& _Info);
    void HitEnd(const StateInfo& _Info);

    void DeathStart(const StateInfo& _Info);
    void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void DeathEnd(const StateInfo& _Info);

    inline void ChangeIdle(const FrameAnimation_DESC& _Info) 
    { 
        State_.ChangeState("Idle");
    }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
    float4 TeleportPos_[3];

	bool DecideState(GameEngineCollision* _This, GameEngineCollision* _Other);
};

