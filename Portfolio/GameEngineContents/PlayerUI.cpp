#include "PreCompile.h"
#include "PlayerUI.h"
#include "LeftTopUI.h"

PlayerUI::PlayerUI() 
{
	Flasks_.resize(3);
}

PlayerUI::~PlayerUI() 
{
}

void PlayerUI::Start()
{
	HPBar_ = GetLevel()->CreateActor<LeftTopUI>();
	HPBar_->Renderer_->SetTexture("Player_HP.png");
	HPBar_->Renderer_->ScaleToTexture();
	HPBar_->Renderer_->SetPivot(PIVOTMODE::LEFTTOP);

	MPBar_ = GetLevel()->CreateActor<LeftTopUI>();
	MPBar_->Renderer_->SetTexture("Player_MP.png");
	MPBar_->Renderer_->ScaleToTexture();
	MPBar_->Renderer_->SetPivot(PIVOTMODE::LEFTTOP);

	BarFrame_ = GetLevel()->CreateActor<LeftTopUI>();
	BarFrame_->Renderer_->SetTexture("Player_HpBar.png");
	BarFrame_->Renderer_->ScaleToTexture();
	BarFrame_->Renderer_->SetPivot(PIVOTMODE::LEFTTOP);

	BalanceFrame_ = CreateComponent<GameEngineUIRenderer>();
	BalanceFrame_->SetTexture("Balance.png");
	BalanceFrame_->ScaleToTexture();

	for (size_t i = 0; i < 10; i++)
	{
		GameEngineUIRenderer* Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->SetTexture(std::to_string(i) + ".png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetWorldMove({ 500, 270 });

		Renderer->GetTransform().SetWorldMove({ 500 + (10.f * i), 270 });
	}

	BarFrame_->GetTransform().SetWorldMove({-620, 350});
	HPBar_->GetTransform().SetWorldMove({ -620, 350 });
	MPBar_->GetTransform().SetWorldMove({ -620, 350 });
	BalanceFrame_->GetTransform().SetWorldMove({ 500, 270 });

	for (size_t i = 0; i < 3; i++)
	{
		Flasks_[i] = CreateComponent<GameEngineUIRenderer>();
		Flasks_[i]->SetTexture("Full_Flask.png");
		Flasks_[i]->ScaleToTexture();

		Flasks_[i]->GetTransform().SetWorldMove({-470.f + (40.f * i), 260 });
	}
}

void PlayerUI::Update(float _DeltaTime)
{
}

void PlayerUI::End()
{
}
