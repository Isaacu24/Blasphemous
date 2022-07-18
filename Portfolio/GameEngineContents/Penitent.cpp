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
		Renderer->SetTexture("penintent_idle_anim_1.png", 0);
		Renderer->CreateFrameAnimation("penintent_idle_anim_1", { "penintent_idle_anim_1.png", 0, 12, 0.1f, true });
		Renderer->ChangeFrameAnimation("penintent_idle_anim_1");
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





