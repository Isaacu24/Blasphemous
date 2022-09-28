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
        BehindHPBar_->Off();
        HPBar_->Off();
        BackHPBar_->Off();
        BarFrame_->Off();
        Off();
    }

    void AllOn()
    {
        On();
        BehindHPBar_->On();
        HPBar_->On();
        BarFrame_->On();
        BackHPBar_->On();
    }

    void SetBossName(const std::string& _Name) { Font_->SetText(_Name, "NeoµÕ±Ù¸ð"); }

    void SetFontPosition(float4 _Value) { Font_->SetScreenPostion(_Value); }

    void SetFontSize(float _Value) { Font_->SetSize(_Value); }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void DamageCheck(float _DeltaTime);

private:
    LeftTopUI* BarFrame_;
    LeftTopUI* HPBar_;

    LeftTopUI* BehindHPBar_;

    LeftTopUI* BackHPBar_;

    BossMonster* Boss_;

    GameEngineFontRenderer* Font_;

    int BossCurHP_;
    int BossPrevHP_ = 100;

    float Alpha_;

    float LerpHP_ = 100.0f;

    int BehindBossCurHP_;
    int BehindBossPrevHP_ = 100;

    float BehindAlpha_;

    float BehindLerpHP_ = 100.0f;
    // class GameEngineFontRenderer* TitleName_;

    bool IsEnd_;
};
