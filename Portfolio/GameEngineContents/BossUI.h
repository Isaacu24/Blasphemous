#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "LeftTopUI.h"

class LeftTopUI;
class BossMonster;
class BossUI : public GameEngineActor
{
    friend BossMonster;

public:
    BossUI();
    ~BossUI();

    BossUI(const BossUI& _Other)                = delete;
    BossUI(BossUI&& _Other) noexcept            = delete;
    BossUI& operator=(const BossUI& _Other)     = delete;
    BossUI& operator=(BossUI&& _Other) noexcept = delete;

    void SetBossMonster(BossMonster* _Boss) { Boss_ = _Boss; };
    void SetBossUI();

    void AllOff()
    {
        HPBar_->Off();
        BarFrame_->Off();
        Off();
    }

    void AllOn()
    {
        On();
        HPBar_->On();
        BarFrame_->On();
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    LeftTopUI* BarFrame_;
    LeftTopUI* HPBar_;

    BossMonster* Boss_;

    // class GameEngineFontRenderer* TitleName_;
};
