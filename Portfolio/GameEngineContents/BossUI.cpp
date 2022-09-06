#include "PreCompile.h"
#include "BossUI.h"
#include "BossMonster.h"

BossUI::BossUI() {}

BossUI::~BossUI() {}


void BossUI::Start() {}

void BossUI::SetBossUI()
{
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
    BarFrame_->GetTransform().SetWorldPosition({-350, -277});

    Font_ = CreateComponent<GameEngineFontRenderer>();
    Font_->SetColor({0.65f, 0.65f, 0.45f, 1.0f});
    Font_->SetScreenPostion({450, 590, static_cast<int>(UIORDER::BossUI)});
    Font_->SetSize(30);
}

void BossUI::Update(float _DeltaTime) {}

void BossUI::End() {}
