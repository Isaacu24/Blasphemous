#include "Penitent.h"
#include "PreCompile.h"

Penitent::Penitent() 
	: Speed_(250.0f)
{
}

Penitent::~Penitent() 
{
}

void Penitent::Start()
{
	if (false == GameEngineInput::GetInst()->IsButton("PenitentA"))
	{
		GameEngineInput::GetInst()->CreateButton("PenitentA", GAMEPAD_A);
		GameEngineInput::GetInst()->CreateButton("PenitentX", GAMEPAD_X);
		GameEngineInput::GetInst()->CreateButton("PenitentB", GAMEPAD_B);
		GameEngineInput::GetInst()->CreateButton("PenitentY", GAMEPAD_Y);
	}

	if (false == GameEngineInput::GetInst()->IsKey("PenitentLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PenitentLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("PenitentRight", 'D');
		GameEngineInput::GetInst()->CreateKey("PenitentUp", 'W');
		GameEngineInput::GetInst()->CreateKey("PenitentDown", 'S');

		GameEngineInput::GetInst()->CreateKey("PenitentAnimation", '1');
	}

	GetTransform().SetLocalScale({1, 1, 1});

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->GetTransform().SetWorldScale({250, 250 });
		Renderer->CreateFrameAnimation("penintent_idle_anim", { "penintent_idle_anim.png", 0, 12, 0.1f, true });
		Renderer->CreateFrameAnimation("penitent_sheathedIdle", { "penitent_sheathedIdle.png", 0, 45, 0.1f, true });
		Renderer->CreateFrameAnimation("penitent_verticalattack_LVL3_anim", { "penitent_verticalattack_LVL3_anim.png", 0, 23, 0.1f, true });
		Renderer->CreateFrameAnimation("penitent_climbledge_reviewed", { "penitent_climbledge_reviewed.png", 0, 11, 0.1f, true });
		//Renderer->CreateFrameAnimation("penitent_respawning_hw", { "penitent_respawning_hw.png", 0, 31, 0.1f, true });
		Renderer->ChangeFrameAnimation("penintent_idle_anim");
	}
}

void Penitent::Update(float _DeltaTime)
{ 
	if (20000 < GameEngineInput::GetInst()->GetThumbLX()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
		Renderer->GetTransform().PixLocalPositiveX();
	}

	if (0 > GameEngineInput::GetInst()->GetThumbLX()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
 	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
		Renderer->GetTransform().PixLocalNegativeX();
	}

	if (20000 < GameEngineInput::GetInst()->GetThumbLY()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
	}

	if (0 > GameEngineInput::GetInst()->GetThumbLY()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
	}

	ButtonCheck();
}


void Penitent::ButtonCheck()
{
	if (GameEngineInput::GetInst()->IsDownKey("PenitentAnimation"))
	{
		Renderer->ChangeFrameAnimation("penitent_verticalattack_LVL3_anim");
	}

	else if (GameEngineInput::GetInst()->IsUpKey("PenitentAnimation"))
	{
		Renderer->ChangeFrameAnimation("penintent_idle_anim");
	}
}



void Penitent::End()
{
}




