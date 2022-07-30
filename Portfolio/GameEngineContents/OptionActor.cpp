#include "PreCompile.h"
#include "OptionActor.h"

OptionActor::OptionActor()
	: Option_(nullptr)
	, Game_(nullptr)
	, Sound_(nullptr)
	, Acces_(nullptr)
	, OptionIndex_(0)
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

	}

	if (true == GameEngineInput::GetInst()->IsDownKey("OptionDownKey"))
	{

	}

	if (true == GameEngineInput::GetInst()->IsDownKey("OptionSelectKey"))
	{

	}

	if (true == GameEngineInput::GetInst()->IsDownKey("OptionEscape"))
	{

	}
}

void OptionActor::End()
{
}
