#include "PreCompile.h"
#include "OptionActor.h"

OptionActor::OptionActor()
	: CurrentState_(OptionType::Game)
	, Option_(nullptr)
	, Game_(nullptr)
	, Sound_(nullptr)
	, Acces_(nullptr)
	, OptionIndex_(1)
{
}

OptionActor::~OptionActor()
{
}

void OptionActor::Start()
{
	Option_ = CreateComponent<GameEngineTextureRenderer>();
	Option_->SetTexture("OptionBackground.png");
	Option_->ScaleToTexture();

	Selecter_ = CreateComponent<GameEngineTextureRenderer>();
	Selecter_->SetTexture("OP_Selecter.png");
	Selecter_->ScaleToTexture();
	Selecter_->GetTransform().SetWorldPosition({ -165, 100, -1.0f });

	Game_ = CreateComponent<GameEngineTextureRenderer>();
	Game_->SetTexture("OP_Game.png");
	Game_->ScaleToTexture();
	Game_->GetTransform().SetWorldPosition({-165, 100, -1.0f});

	Sound_ = CreateComponent<GameEngineTextureRenderer>();
	Sound_->SetTexture("OP_Sound.png");
	Sound_->ScaleToTexture();
	Sound_->GetTransform().SetWorldPosition({ -150, 0, -1.0f });

	Acces_ = CreateComponent<GameEngineTextureRenderer>();
	Acces_->SetTexture("OP_Acces.png");
	Acces_->ScaleToTexture();
	Acces_->GetTransform().SetWorldPosition({ -150, -100, -1.0f });

	GameEngineInput::GetInst()->CreateKey("OptionUpKey", VK_UP);
	GameEngineInput::GetInst()->CreateKey("OptionDownKey", VK_DOWN);
	GameEngineInput::GetInst()->CreateKey("OptionSelectKey", VK_SPACE);
	GameEngineInput::GetInst()->CreateKey("OptionEscape", VK_ESCAPE);
}

void OptionActor::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("OptionUpKey"))
	{
		if (1 == OptionIndex_)
		{
			OptionIndex_ = 3;
			ChangeIndex();
			return;
		}

		--OptionIndex_;
		ChangeIndex();
	}

	if (true == GameEngineInput::GetInst()->IsDownKey("OptionDownKey"))
	{
		if (3 == OptionIndex_)
		{
			OptionIndex_ = 1;
			ChangeIndex();
			return;
		}

		++OptionIndex_;
		ChangeIndex();
	}

	if (true == GameEngineInput::GetInst()->IsDownKey("OptionSelectKey"))
	{
	}

	if (true == GameEngineInput::GetInst()->IsDownKey("OptionEscape"))
	{
		GEngine::ChangeLevel("MainMenu");
	}
}

void OptionActor::End()
{
}

void OptionActor::ChangeIndex()
{
	switch (OptionIndex_)
	{
	case 1:
		CurrentState_ = OptionType::Game;
		break;
	case 2:
		CurrentState_ = OptionType::Sound;
		break;
	case 3:
		CurrentState_ = OptionType::Acces;
		break;
	default:
		break;
	}

	UpdateOptionMenu();
}

void OptionActor::UpdateOptionMenu()
{
	switch (CurrentState_)
	{
	case OptionType::Game:
		Game_->SetTexture("OP_Game_Select.png");
		Sound_->SetTexture("OP_Sound.png");
		Acces_->SetTexture("OP_Acces.png");

		Selecter_->GetTransform().SetWorldPosition({ -240, 100, -1.0f });
		break;
	case OptionType::Sound:
		Game_->SetTexture("OP_Game.png");
		Sound_->SetTexture("OP_Sound_Select.png");
		Acces_->SetTexture("OP_Acces.png");
		
		Selecter_->GetTransform().SetWorldPosition({ -240, 0, -1.0f });
		break;
	case OptionType::Acces:
		Game_->SetTexture("OP_Game.png");
		Sound_->SetTexture("OP_Sound.png");
		Acces_->SetTexture("OP_Acces_Select.png");
		
		Selecter_->GetTransform().SetWorldPosition({ -240, -100, -1.0f });
		break;
	default:
		break;
	}
}
