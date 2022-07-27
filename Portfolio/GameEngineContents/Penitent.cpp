#include "Penitent.h"
#include "PreCompile.h"
#include "GravityComponent.h"
#include "PlayerUI.h"

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
	PlayerUI_ = GetLevel()->CreateActor<PlayerUI>();

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

	StateManager_.CreateStateMember("Idle", this, &Penitent::IdleUpdate, &Penitent::IdleStart);
	StateManager_.CreateStateMember("LadderClimb", this, &Penitent::LadderClimbUpdate, &Penitent::LadderClimbStart);
	StateManager_.CreateStateMember("Jump", this, &Penitent::JumpUpdate, &Penitent::JumpStart);
	StateManager_.ChangeState("Idle");
}

void Penitent::Update(float _DeltaTime)
{ 
	StateManager_.Update(_DeltaTime);

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
		StateManager_.ChangeState("Jump");
	}

	LadderCheck(); //사다리 체크
	UphillRoadCheck(); //오르막길 체크
}

void Penitent::PixelCheck()
{

}

void Penitent::GroundCheck()
{
	float4 Color = Ground_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 95));

	if (true == Color.CompareInt4D(float4::BLACK)) //땅이라면 
	{
		IsJump_ = false;
		IsGround_ = true;
	}

	else
	{
		IsGround_ = false;
	}
}

void Penitent::LadderCheck()
{
	float4 MiddleColor = Ground_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 200));
	float4 LowColor = Ground_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));

	if (true == LowColor.CompareInt4D(float4::GREEN)
		|| true == MiddleColor.CompareInt4D(float4::GREEN))
	{
		if (GameEngineInput::GetInst()->IsDownKey("PenitentDown"))
		{
			StateManager_.ChangeState("LadderClimb");
		}
	}
}

void Penitent::UphillRoadCheck()
{
	while (true)
	{
		float4 RightColor = Ground_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 94));
		
		if (true == RightColor.CompareInt4D(float4::BLACK))
		{
			GetTransform().SetWorldMove(float4{ 0, 1 ,0, 0 });
			continue;
		}

		else
		{
			break;
		}
	}
}

void Penitent::End()
{

}

void Penitent::IdleStart(const StateInfo& _Info)
{
}

void Penitent::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GroundCheck(); //지면 체크
	Gravity_->SetActive(!IsGround_);
}



void Penitent::LadderClimbStart(const StateInfo& _Info)
{
	IsLadder_ = true;
}

void Penitent::LadderClimbUpdate(float _DeltaTime, const StateInfo& _Info)
{
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

	if (true == IsGround_)
	{
		IsLadder_ = false;
		StateManager_.ChangeState("Idle");
	}
}



void Penitent::JumpStart(const StateInfo& _Info)
{
	IsJump_ = true;
}

void Penitent::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	JumpTime_ += _DeltaTime;
	GetTransform().SetWorldMove(GetTransform().GetUpVector() * 350 * _DeltaTime);

	if (0.5f <= JumpTime_)
	{
		JumpTime_ = 0.f;

		StateManager_.ChangeState("Idle");
	}
}




