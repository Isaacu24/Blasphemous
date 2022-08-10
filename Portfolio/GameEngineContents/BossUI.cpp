#include "PreCompile.h"
#include "BossUI.h"
#include "LeftTopUI.h"

BossUI::BossUI() 
{
}

BossUI::~BossUI() 
{
}

void BossUI::Start()
{
	HPBar_ = GetLevel()->CreateActor<LeftTopUI>();
	HPBar_->Renderer_->SetTexture("BossHPBar.png");
	HPBar_->Renderer_->ScaleToTexture();
	HPBar_->Renderer_->SetPivot(PIVOTMODE::LEFTTOP);

	BarFrame_ = GetLevel()->CreateActor<LeftTopUI>();
	BarFrame_->Renderer_->SetTexture("Boss_HpBarFrame.png");
	BarFrame_->Renderer_->ScaleToTexture();
	BarFrame_->Renderer_->SetPivot(PIVOTMODE::LEFTTOP);

	float4 UIPos = { -350, -275 };

	HPBar_->GetTransform().SetWorldPosition(UIPos);
	BarFrame_->GetTransform().SetWorldPosition(UIPos);
}

void BossUI::Update(float _DeltaTime)
{
}

void BossUI::End()
{
}
