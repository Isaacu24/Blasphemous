#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MonsterHitEffect.h"
#include "MonsterBase.h"
#include "BossUI.h"

class BossUI;
class BossMonster
    : public GameEngineActor
    , public MonsterBase
{
public:
    BossMonster();
    ~BossMonster();

    BossMonster(const BossMonster& _Other)                = delete;
    BossMonster(BossMonster&& _Other) noexcept            = delete;
    BossMonster& operator=(const BossMonster& _Other)     = delete;
    BossMonster& operator=(BossMonster&& _Other) noexcept = delete;

    inline void GetBossEvent(bool _Event) { BossEvent_ = _Event; }

    inline bool GetBossEvent() { return BossEvent_; }

    inline bool GetLose() { return IsLose_; }

    bool ReverseBloodEffect(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:
    void Start() = 0;
    void Update(float _DeltaTime) override;
    void End() override;

    BossUI* BossUI_;
    bool    BossEvent_;

    GameEngineTextureRenderer* Backgorund_;

    void DamageCheck(float _Damage) override;

    void DamageCheck(float _Damage, const std::string& _State) override;

    // void DamageCheck(float _Damage, std::function<void>()) override;

    virtual void BossDeathEvent();

    bool IsLose_;

    bool BossDeathEvent_;

    float EventTime_;

    bool DeathSlow_;

private:
};
