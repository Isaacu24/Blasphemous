#include "Penitent.h"
#include "PreCompile.h"
#include "GravityComponent.h"

Penitent::Penitent() 
	: Speed_(250.0f)
	, JumpTime_(0.0f)
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
		GameEngineInput::GetInst()->CreateKey("PenitentJump", VK_LSHIFT);

		GameEngineInput::GetInst()->CreateKey("PenitentAnimation", '1');
	}

	Gravity_ = CreateComponent<GravityComponent>();

	GetTransform().SetLocalScale({1, 1, 1});

	{
		Renderer_ = CreateComponent<GameEngineTextureRenderer>();

		Renderer_->GetTransform().SetWorldScale({250, 250 });
		Renderer_->CreateFrameAnimation("penintent_idle_anim", { "penintent_idle_anim.png", 0, 12, 0.1f, true });
		Renderer_->CreateFrameAnimation("penitent_sheathedIdle", { "penitent_sheathedIdle.png", 0, 45, 0.1f, true });
		Renderer_->CreateFrameAnimation("penitent_verticalattack_LVL3_anim", { "penitent_verticalattack_LVL3_anim.png", 0, 23, 0.05f, true });
		Renderer_->CreateFrameAnimation("penitent_climbledge_reviewed", { "penitent_climbledge_reviewed.png", 0, 11, 0.1f, true });
		Renderer_->CreateFrameAnimation("penitent_dodge_attack_LVL3", { "penitent_dodge_attack_LVL3.png", 0, 26, 0.1f, true });
		Renderer_->CreateFrameAnimation("penitent_falling_ahead_anim 1", { "penitent_falling_ahead_anim 1.png", 0, 5, 0.1f, true });
		Renderer_->CreateFrameAnimation("penitent_jumpoff_new", { "penitent_jumpoff_new.png", 0, 4, 0.1f, true });
		Renderer_->ChangeFrameAnimation("penintent_idle_anim");
	}
}

void Penitent::Update(float _DeltaTime)
{ 
	InputCheck(_DeltaTime);

	switch (CurrentState_)
	{
	case PlayerState::Idle:
		if (true == GroundCheck() || true == IsJump_) //∂•¿Ã∂Û∏È 
		{
			Gravity_->SetActive(false);
		}

		else //∂•¿Ã æ∆¥œ∂Û∏È 
		{
			IsJump_ = false;
			Gravity_->SetActive(true);
			return;
		}
		UphillRoadCheck();
		break;
	case PlayerState::Run:
		UphillRoadCheck();
		break;
	case PlayerState::Jump:
		IsJump_ = true;
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * 350 * _DeltaTime);
		JumpTime_ += _DeltaTime;
		
		if (0.5f <= JumpTime_)
		{
			IsJump_ = false;
			JumpTime_ = 0.0f;
			CurrentState_ = PlayerState::Idle;
		}
		break;
	case PlayerState::Fall:
		break;
	case PlayerState::LadderClimb:
		Gravity_->SetActive(false);

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

		if (true == GroundCheck()) //∂•¿Ã∂Û∏È 
		{
			CurrentState_ = PlayerState::Idle;
		}
		break;
	case PlayerState::Slide:
		break;
	case PlayerState::Attack:
		break;
	case PlayerState::Parring:
		break;
	case PlayerState::Hit:
		break;
	case PlayerState::Death:
		break;
	default:
		break;
	}

	LadderCheck();
	
	GameEngineDebug::OutPutString("PlayerState : " + std::to_string(static_cast<int>(CurrentState_)));

	//GameEngineDebug::OutPutString("x : " + std::to_string(GetTransform().GetLocalPosition().x));
	//GameEngineDebug::OutPutString("y : " + std::to_string(GetTransform().GetLocalPosition().y));
}


void Penitent::InputCheck(float _DeltaTime)
{
	if (20000 < GameEngineInput::GetInst()->GetThumbLX()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	if (0 > GameEngineInput::GetInst()->GetThumbLX()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
		Renderer_->GetTransform().PixLocalNegativeX();
	}

	if (GameEngineInput::GetInst()->IsDownKey("PenitentJump") && false == IsJump_)
	{
		CurrentState_ = PlayerState::Jump;
	}

	if (GameEngineInput::GetInst()->IsDownKey("PenitentAnimation"))
	{
		Renderer_->ChangeFrameAnimation("penitent_verticalattack_LVL3_anim");
	}

	else if (GameEngineInput::GetInst()->IsUpKey("PenitentAnimation"))
	{
		Renderer_->GetTransform().SetWorldScale({ 250, 250 });
		Renderer_->ChangeFrameAnimation("penintent_idle_anim");
	}
}

bool Bool_ = false;

bool Penitent::GroundCheck()
{
	float4 Color = Ground_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 90));

	if (Color.CompareInt4D(float4::BLACK))
	{
		Bool_= false;
		return true;
	}

	else if (Color.CompareInt4D(float4{1.0f, 0.0f, 1.0f, 1.0f}) && false == Bool_)
	{
		if (0 > GameEngineInput::GetInst()->GetThumbLY()
			|| GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
		{
			Bool_ = true;
			return true;
		}

		return true;
	}

	return false;
}

void Penitent::UphillRoadCheck()
{
	while (true)
	{
		float4 Color = Ground_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 89));

		if (Color.CompareInt4D(float4::BLACK)
			|| Color.CompareInt4D(float4{ 1.0f, 0.0f, 1.0f, 1.0f }) && false == Bool_)
		{
			GetTransform().SetWorldMove({ 0, 1, 0.0f });
			continue;
		}

		if (Color.CompareInt4D(float4{ 1.0f, 1.0f, 1.0f, 0.0f })
			|| Color.CompareInt4D(float4::GREEN))
		{
			break;
		}
	}
}

void Penitent::LadderCheck()
{
	float4 Color = Ground_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 150));

	if (Color.CompareInt4D(float4::GREEN))
	{
		if (0 > GameEngineInput::GetInst()->GetThumbLY()
			|| GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
		{
			CurrentState_ = PlayerState::LadderClimb;
		}
	}

	Color = Ground_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));

	if (Color.CompareInt4D(float4::GREEN))
	{
		if (0 > GameEngineInput::GetInst()->GetThumbLY()
			|| GameEngineInput::GetInst()->IsPressKey("PenitentUp"))
		{
			CurrentState_ = PlayerState::LadderClimb;
		}
	}

	GameEngineDebug::OutPutString("Color : " + std::to_string(Color.x) + " " + std::to_string(Color.y) + " " + std::to_string(Color.z) + " " + std::to_string(Color.w));
}

void Penitent::End()
{

}




