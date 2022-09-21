#include "PreCompile.h"
#include "BossUI.h"
#include "BossMonster.h"

BossUI::BossUI() {}

BossUI::~BossUI() {}


void BossUI::Start() {}

void BossUI::SetBossUI()
{
    BehindHPBar_ = GetLevel()->CreateActor<LeftTopUI>();
    BehindHPBar_->Renderer_->SetTexture("BossHPBar.png");
    BehindHPBar_->Renderer_->ScaleToTexture();
    BehindHPBar_->Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
    BehindHPBar_->Renderer_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(UIORDER::BossUI)});
    BehindHPBar_->Renderer_->GetColorData().PlusColor = float4{-0.5f, -0.5f, -0.5f, 0.0f};

    HPBar_ = GetLevel()->CreateActor<LeftTopUI>();
    HPBar_->Renderer_->SetTexture("BossHPBar.png");
    HPBar_->Renderer_->ScaleToTexture();
    HPBar_->Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
    HPBar_->Renderer_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(UIORDER::BossUI)});

    float HP = Boss_->GetHP() / 100.f;

    HPBar_->Renderer_->SetUVData(HP);

    BarFrame_ = GetLevel()->CreateActor<LeftTopUI>();
    BarFrame_->Renderer_->SetTexture("Boss_HpBarFrame.png");
    BarFrame_->Renderer_->ScaleToTexture();
    BarFrame_->Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
    BarFrame_->Renderer_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(UIORDER::BossUI)});

    HPBar_->GetTransform().SetWorldPosition({-292, -300});
    BehindHPBar_->GetTransform().SetWorldPosition({-292, -300});
    BarFrame_->GetTransform().SetWorldPosition({-350, -277});

    Font_ = CreateComponent<GameEngineFontRenderer>();
    Font_->SetColor({0.65f, 0.65f, 0.45f, 1.0f});
    Font_->SetScreenPostion({450, 590, static_cast<int>(UIORDER::BossUI)});
    Font_->SetSize(30);
    Font_->ChangeCamera(CAMERAORDER::UICAMERA);
}

void BossUI::Update(float _DeltaTime)
{
    // float HP = Boss_->GetHP() / 100.f;
    // HPBar_->Renderer_->SetUVData(HP);
    DamageCheck(_DeltaTime);
}

void BossUI::End() {}

void BossUI::DamageCheck(float _DeltaTime)
{
    BossCurHP_ = Boss_->GetHP();
    BehindBossCurHP_ = Boss_->GetHP();

    if (BossPrevHP_ != BossCurHP_)
    {
        Alpha_ += _DeltaTime;

        float CurHP  = static_cast<float>(BossCurHP_);
        float PrevHP = static_cast<float>(BossPrevHP_);

        LerpHP_ = GameEngineMath::LerpLimit(PrevHP, CurHP, Alpha_);

        if (LerpHP_ - CurHP <= 0.01f)
        {
            Alpha_      = 0.f;
            LerpHP_     = CurHP;
            BossPrevHP_ = BossCurHP_;
            IsEnd_      = true;
        }
    }

    HPBar_->Renderer_->SetUVData(LerpHP_ / 100.f);

    if (false == IsEnd_)
    {
        return;
    }

    if (BehindBossPrevHP_ != BehindBossCurHP_)
    {
        BehindAlpha_ += _DeltaTime;

        float CurHP  = static_cast<float>(BehindBossCurHP_);
        float PrevHP = static_cast<float>(BehindBossPrevHP_);

        BehindLerpHP_ = GameEngineMath::LerpLimit(PrevHP, CurHP, BehindAlpha_);

        if (BehindLerpHP_ - CurHP <= 0.01f)
        {
            BehindAlpha_      = 0.f;
            BehindLerpHP_     = CurHP;
            BehindBossPrevHP_ = BehindBossCurHP_;
            IsEnd_            = false;
        }
    }

    GameEngineDebug::OutPutString(std::to_string(BehindLerpHP_));
    BehindHPBar_->Renderer_->SetUVData(BehindLerpHP_ / 100.f);
}
