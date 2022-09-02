#pragma once
#include "MonsterBase.h"
#include "BossUI.h"

class BossUI;
class BossMonster : public MonsterBase
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

protected:
    BossUI* BossUI_;
    bool BossEvent_;

    void DamageCheck(float _Damage) override;

private:
};
