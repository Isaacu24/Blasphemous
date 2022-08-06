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
	HPBar_->SetLevelOverOn();

	MPBar_ = GetLevel()->CreateActor<LeftTopUI>();
	MPBar_->Renderer_->SetTexture("Player_MP.png");
	MPBar_->Renderer_->ScaleToTexture();
	MPBar_->SetLevelOverOn();

	BarFrame_ = GetLevel()->CreateActor<LeftTopUI>();
	BarFrame_->Renderer_->SetTexture("Player_HpBar.png");
	BarFrame_->Renderer_->ScaleToTexture();
	BarFrame_->SetLevelOverOn();

	TearFrame_ = CreateComponent<GameEngineUIRenderer>();
	TearFrame_->SetTexture("TearFrame.png");
	TearFrame_->ScaleToTexture();

	HPBar_->GetTransform().SetWorldPosition({ -450, 290, static_cast<int>(UIORDER::PlayerUI)});
	MPBar_->GetTransform().SetWorldPosition({ -450, 290, static_cast<int>(UIORDER::PlayerUI) });
	BarFrame_->GetTransform().SetWorldPosition({ -450, 290, static_cast<int>(UIORDER::PlayerUIFrame) });
	TearFrame_->GetTransform().SetWorldPosition({ 500, 270, static_cast<int>(UIORDER::PlayerUIFrame) });

	for (size_t i = 0; i < 3; i++)
	{
		Flasks_[i] = CreateComponent<GameEngineUIRenderer>();
		Flasks_[i]->SetTexture("Full_Flask.png");
		Flasks_[i]->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(UIORDER::PlayerUI) });
		Flasks_[i]->ScaleToTexture();

		Flasks_[i]->GetTransform().SetWorldMove({ -470.f + (40.f * i), 260 });
	}

	TearRenderers_.resize(10);
}

void PlayerUI::Update(float _DeltaTime)
{

}

void PlayerUI::End()
{
}


void PlayerUI::SetTear(int _Value)
{
	std::vector<int> Numbers;

	while (true)
	{
		int Temp = _Value % 10;

		Numbers.push_back(Temp);

		_Value /= 10;

		if (_Value < 10)
		{
			if (0 != _Value)
			{
				Numbers.push_back(_Value);
			}

			break;
		}
	}

	for (size_t i = 0; i < Numbers.size(); i++)
	{
		if (nullptr == TearRenderers_[i])
		{
			TearRenderers_[i] = CreateComponent<GameEngineUIRenderer>();
		}

		if (i == Numbers.size())
		{
			if (0 == Numbers[i]) //앞 자리가 0이라면
			{
				return;
			}
		}

		TearRenderers_[i]->SetTexture(std::to_string(Numbers[i]) + ".png");
		TearRenderers_[i]->ScaleToTexture();
		TearRenderers_[i]->GetTransform().SetWorldPosition({ 505.f - (10.f * i), 270.f, static_cast<int>(UIORDER::PlayerUI)});
	}
}


void PlayerUI::UseFlask(int _Index)
{
	Flasks_[_Index]->SetTexture("Empty_Flask.png");

	HPBar_->Renderer_->GetTransform().SetWorldScale(HPBar_->Renderer_->GetTransform().GetWorldScale() + float4{100, 0});
	HPBar_->Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
}