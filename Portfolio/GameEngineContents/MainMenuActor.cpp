#include "PreCompile.h"
#include "MainMenuActor.h"
#include "Stage01.h"

MainMenuActor::MainMenuActor()
	: Background_(nullptr)
	, BigPetal_(nullptr)
	, Petal_(nullptr)
	, Crisanta_(nullptr)
	, Pilgrimage_(nullptr)
	, Option_(nullptr)
	, Exit_(nullptr)
	, CurrentType_(MainMenuType::Pilgrimage)
	, MenuIndex_(1)
	, BackgroundTime_(0.0f)
	, PetalTime_(0.0f)
	, BigPetalTime_(0.0f)
	, CrisantaTime_(0.0f)
	, BackgroundFrame_(0)
	, PetalFrame_(0)
	, BigPetalFrame_(0)
	, CrisantaFrame_(0)
{

}

MainMenuActor::~MainMenuActor() 
{

}

void MainMenuActor::Start()
{
	Background_ = CreateComponent<GameEngineTextureRenderer>();
	Background_->GetTransform().SetWorldScale(GameEngineWindow::GetScale());
	Background_->SetTexture("TitleBackgorund_0.png");

	Petal_ = CreateComponent<GameEngineTextureRenderer>();
	Petal_->GetTransform().SetWorldScale(GameEngineWindow::GetScale());
	Petal_->SetTexture("Crisanta_Petal_0.png");

	Crisanta_ = CreateComponent<GameEngineTextureRenderer>();
	Crisanta_->GetTransform().SetWorldScale({ 878, 720 });
	Crisanta_->GetTransform().SetWorldPosition({-200, 0, 0.0f});
	Crisanta_->SetTexture("Crisanta_0.png");

	BigPetal_ = CreateComponent<GameEngineTextureRenderer>();
	BigPetal_->GetTransform().SetWorldScale(GameEngineWindow::GetScale());
	BigPetal_->SetTexture("Crisanta_BigPetal_0.png");

	Pilgrimage_ = CreateComponent<GameEngineTextureRenderer>();
	Pilgrimage_->GetTransform().SetWorldScale({ 58, 30 });
	Pilgrimage_->GetTransform().SetWorldPosition({ 440, -50, 0.0f });
	Pilgrimage_->SetTexture("Pilgrimage_Select.png");

	Option_ = CreateComponent<GameEngineTextureRenderer>();
	Option_->GetTransform().SetWorldScale({ 58, 30 });
	Option_->GetTransform().SetWorldPosition({ 440, -125, 0.0f });
	Option_->SetTexture("Option.png");

	Exit_ = CreateComponent<GameEngineTextureRenderer>();
	Exit_->GetTransform().SetWorldScale({ 84, 30 });
	Exit_->GetTransform().SetWorldPosition({ 425, -200, 0.0f });
	Exit_->SetTexture("Exit.png");

	GameEngineInput::GetInst()->CreateKey("MainMenuUpKey", VK_UP);
	GameEngineInput::GetInst()->CreateKey("MainMenuDownKey", VK_DOWN);
	GameEngineInput::GetInst()->CreateKey("MainMenuSelectKey", VK_SPACE);

	Selecter_ = CreateComponent<GameEngineTextureRenderer>();
	Selecter_->CreateFrameAnimationCutTexture("alliedCherub", {"alliedCherub.png", 0, 10, 0.1f, true});
	Selecter_->ChangeFrameAnimation("alliedCherub");
	Selecter_->GetTransform().SetWorldScale({ 170, 170 });
	Selecter_->GetTransform().SetWorldPosition({ 520, -45, 0.0f });
	Selecter_->GetTransform().PixLocalNegativeX();
}

void MainMenuActor::Update(float _DeltaTime)
{
	Selecter_;

	BackgroundAnimation(_DeltaTime);
	PetalAnimation(_DeltaTime);
	CrisantaAnimation(_DeltaTime);
	BigPetalAnimation(_DeltaTime);

	SelectMenu();

	if (true == GameEngineInput::GetInst()->IsDownKey("MainMenuUpKey"))
	{
		if (1 == MenuIndex_)
		{
			MenuIndex_ = 3;
			ChangeMenuIndex();
			return;
		}

		--MenuIndex_;
		ChangeMenuIndex();
	}

	else if (true == GameEngineInput::GetInst()->IsDownKey("MainMenuDownKey"))
	{
		if (3 == MenuIndex_)
		{
			MenuIndex_ = 1;
			ChangeMenuIndex();
			return;
		}
		
		++MenuIndex_;
		ChangeMenuIndex();
	}
}

void MainMenuActor::End()
{
}

void MainMenuActor::BackgroundAnimation(float _DeltaTime)
{
	BackgroundTime_ += _DeltaTime;

	if (0.1f <= BackgroundTime_)
	{
		BackgroundTime_ -= 0.1f;
		++BackgroundFrame_;

		if (15 == BackgroundFrame_)
		{
			BackgroundFrame_ = 0;
		}
		Background_->SetTexture("TitleBackgorund_" + std::to_string(BackgroundFrame_) + ".png");
	}
}

void MainMenuActor::PetalAnimation(float _DeltaTime)
{
	PetalTime_ += _DeltaTime;

	if (0.1f <= PetalTime_)
	{
		PetalTime_ -= 0.1f;
		++PetalFrame_;

		if (44 == PetalFrame_)
		{
			PetalFrame_ = 0;
		}

		Petal_->SetTexture("Crisanta_Petal_" + std::to_string(PetalFrame_) + ".png");
	}
}

void MainMenuActor::BigPetalAnimation(float _DeltaTime)
{
	BigPetalTime_ += _DeltaTime;

	if (0.2f <= BigPetalTime_)
	{
		BigPetalTime_ -= 0.2f;
		++BigPetalFrame_;

		if (6 == BigPetalFrame_)
		{
			BigPetalFrame_ = -30;
		}

		if (0 > BigPetalFrame_)
		{
			return;
		}

		BigPetal_->SetTexture("Crisanta_BigPetal_" + std::to_string(BigPetalFrame_) + ".png");
	}
}

void MainMenuActor::CrisantaAnimation(float _DeltaTime)
{
	CrisantaTime_ += _DeltaTime;

	if (0.2f <= CrisantaTime_)
	{
		CrisantaTime_ -= 0.2f;
		++CrisantaFrame_;

		if (14 == CrisantaFrame_)
		{
			CrisantaFrame_ = 0;
		}

		Crisanta_->SetTexture("Crisanta_" + std::to_string(CrisantaFrame_) + ".png");
	}
}

void MainMenuActor::ChangeMenuIndex()
{
	switch (MenuIndex_)
	{
	case 1:
		CurrentType_ = MainMenuType::Pilgrimage;
		break;
	case 2:
		CurrentType_ = MainMenuType::Option_;
		break;
	case 3:
		CurrentType_ = MainMenuType::Exit_;
		break;
	default:
		MenuIndex_ = 1;
		break;
	}

	ChangeMenuSelect();
}

void MainMenuActor::ChangeMenuSelect()
{
	//셰이더 처리 혹은 텍스쳐 변경
	switch (CurrentType_)
	{
	case MainMenuType::Pilgrimage:
		Pilgrimage_->SetTexture("Pilgrimage_Select.png");
		Option_->SetTexture("Option.png");
		Exit_->SetTexture("Exit.png");

		Selecter_->GetTransform().SetWorldPosition({ 520, -45, 0.0f });
		break;
	case MainMenuType::Option_:
		Option_->SetTexture("Option_Select.png");
		Pilgrimage_->SetTexture("Pilgrimage.png");
		Exit_->SetTexture("Exit.png");

		Selecter_->GetTransform().SetWorldPosition({ 520, -120, 0.0f });
		break;
	case MainMenuType::Exit_:
		Exit_->SetTexture("Exit_Select.png");
		Pilgrimage_->SetTexture("Pilgrimage.png");
		Option_->SetTexture("Option.png");

		Selecter_->GetTransform().SetWorldPosition({ 520, -195, 0.0f });
		break;
	default:
		break;
	}
}

void MainMenuActor::SelectMenu()
{
	if (true == GameEngineInput::GetInst()->IsDownKey("MainMenuSelectKey"))
	{
		switch (CurrentType_)
		{
		case MainMenuType::Pilgrimage:
			GEngine::ChangeLevel("Stage01");
			break;
		case MainMenuType::Option_:
			GEngine::ChangeLevel("Option");
			break;
		case MainMenuType::Exit_:
			break;
		default:
			break;
		}
	}
}
