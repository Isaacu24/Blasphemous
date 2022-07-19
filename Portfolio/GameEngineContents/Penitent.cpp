#include "Penitent.h"
#include "PreCompile.h"

Penitent::Penitent() 
	: Speed_(150.0f)
{
}

Penitent::~Penitent() 
{
}

void Penitent::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PenitentA"))
	{
		GameEngineInput::GetInst()->CreateKey("PenitentA", GAMEPAD_A);
		GameEngineInput::GetInst()->CreateKey("PenitentX", GAMEPAD_X);
		GameEngineInput::GetInst()->CreateKey("PenitentB", GAMEPAD_B);
		GameEngineInput::GetInst()->CreateKey("PenitentY", GAMEPAD_Y);
	}

	GetTransform().SetLocalScale({1, 1, 1});

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->GetTransform().SetWorldScale({300, 300});
		Renderer->CreateFrameAnimation("penintent_idle_anim", { "penintent_idle_anim.png", 0, 12, 0.1f, true });
		Renderer->CreateFrameAnimation("penitent_sheathedIdle", { "penitent_sheathedIdle.png", 0, 45, 0.1f, true });
		Renderer->ChangeFrameAnimation("penitent_sheathedIdle");
	}
}

void Penitent::Update(float _DeltaTime)
{ 
	if (20000 < GameEngineInput::GetInst()->GetThumbLX())
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
	}

	if (0 > GameEngineInput::GetInst()->GetThumbLX())
 	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
	}

	if (20000 < GameEngineInput::GetInst()->GetThumbLY())
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
	}

	if (0 > GameEngineInput::GetInst()->GetThumbLY())
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
	}
}

void Penitent::End()
{
}





