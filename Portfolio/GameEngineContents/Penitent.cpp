#include "Penitent.h"
#include "PreCompile.h"
#include "GravityComponent.h"
#include "PlayerUI.h"

Penitent* Penitent::MainPlayer_ = nullptr;

Penitent::Penitent() 
	: StateManager_{}
	, PlayerUI_(nullptr)
	, Gravity_(nullptr)
	, Renderer_(nullptr)
	, ColMap_(nullptr)
	, HP_(100)
	, MP_(100)
	, Speed_(250.0f)
	, Tear_(0)
	, IsGround_(false)
	, IsJump_(false)
	, IsLadder_(false)
	, Flasks_{}
	, JumpTime_(0.0f)
{
	MainPlayer_ = this;
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

		GameEngineInput::GetInst()->CreateButton("PenitentLeftShoulder", GAMEPAD_LEFT_SHOULDER); //LB
		GameEngineInput::GetInst()->CreateButton("PenitentRightShoulder", GAMEPAD_RIGHT_SHOULDER);

		GameEngineInput::GetInst()->CreateButton("PenitentLeftThumb", GAMEPAD_LEFT_THUMB);
		GameEngineInput::GetInst()->CreateButton("PenitentRightThumb", GAMEPAD_RIGHT_THUMB);
	}

	if (false == GameEngineInput::GetInst()->IsKey("PenitentLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PenitentLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("PenitentRight", 'D');
		GameEngineInput::GetInst()->CreateKey("PenitentUp", 'W');
		GameEngineInput::GetInst()->CreateKey("PenitentDown", 'S');
		GameEngineInput::GetInst()->CreateKey("PenitentJump", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("PenitentSlide", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("PenitentRecovery", 'F');
		GameEngineInput::GetInst()->CreateKey("FreeCamera", 'O');

		GameEngineInput::GetInst()->CreateKey("PenitentAnimation", '1');
	}

	Flasks_.resize(3);

	for (size_t i = 0; i < Flasks_.size(); i++)
	{
		Flasks_[i] = true;
	}

	Gravity_ = CreateComponent<GravityComponent>();

	Collider_ = CreateComponent<GameEngineCollision>();
	Collider_->GetTransform().SetWorldScale({100.f, 100.f, 1.0f});
	Collider_->ChangeOrder(COLLISIONORDER::Player);

	PlayerUI_ = GetLevel()->CreateActor<PlayerUI>();
	PlayerUI_->SetLevelOverOn();

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
	}

	StateManager_.CreateStateMember("Idle", this, &Penitent::IdleUpdate, &Penitent::IdleStart);
	StateManager_.CreateStateMember("LadderClimb", this, &Penitent::LadderClimbUpdate, &Penitent::LadderClimbStart);
	StateManager_.CreateStateMember("Jump", this, &Penitent::JumpUpdate, &Penitent::JumpStart);
	StateManager_.CreateStateMember("Slide", this, &Penitent::SlideUpdate, &Penitent::SlideStart);
	StateManager_.CreateStateMember("Crouch", this, &Penitent::RecoveryUpdate, &Penitent::RecoveryStart);
	StateManager_.CreateStateMember("Recovery", this, &Penitent::RecoveryUpdate, &Penitent::RecoveryStart);
	StateManager_.CreateStateMember("Hit", this, &Penitent::HitUpdate, &Penitent::HitStart);
	StateManager_.CreateStateMember("Death", this, &Penitent::DeathUpdate, &Penitent::DeathStart);
	StateManager_.ChangeState("Idle");

	PlayerUI_->SetTear(Tear_);
}

void Penitent::Update(float _DeltaTime)
{ 
	StateManager_.Update(_DeltaTime);

	if (20000 < GameEngineInput::GetInst()->GetThumbLX()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
	{
		Renderer_->GetTransform().PixLocalPositiveX();

		if (false == RightObstacleCheck())
		{
			Dir_ = GetTransform().GetRightVector();
			GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
		}
	}

	if (0 > GameEngineInput::GetInst()->GetThumbLX()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
	{
		Renderer_->GetTransform().PixLocalNegativeX();

		if (false == LeftObstacleCheck())
		{
			Dir_ = GetTransform().GetLeftVector();
			GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
		}
	}

	if (GameEngineInput::GetInst()->IsDownKey("PenitentJump")
		&& false == IsJump_ && true == IsGround_
		|| GameEngineInput::GetInst()->IsDownButton("PenitentA")
		&& false == IsJump_ && true == IsGround_)
	{
		StateManager_.ChangeState("Jump");
		PlayerUI_->SetTear(Tear_ += 123);
	}

	if (GameEngineInput::GetInst()->IsDownKey("PenitentRecovery")
		|| GameEngineInput::GetInst()->IsDownButton("PenitentLeftShoulder"))
	{
		StateManager_.ChangeState("Recovery");
	}

	if (GameEngineInput::GetInst()->IsDownKey("PenitentSlide")
		&& true == IsGround_ && false == IsLadder_)
	{
		StateManager_.ChangeState("Slide");
	}

	Collider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Penitent::HitMonster, this, std::placeholders::_1, std::placeholders::_2)
	);

	Collider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Projectile, CollisionType::CT_OBB2D,
		std::bind(&Penitent::HitProjectile, this, std::placeholders::_1, std::placeholders::_2)
	);

	Collider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::BossMonster, CollisionType::CT_OBB2D,
		std::bind(&Penitent::HitMonster, this, std::placeholders::_1, std::placeholders::_2)
	);

	GroundCheck(); //지면 체크
	LadderCheck(); //사다리 체크

	if (true == GameEngineInput::GetInst()->IsDownKey("FreeCamera"))
	{
		GetLevel()->GetMainCameraActor()->FreeCameraModeOnOff();
	}

	GameEngineDebug::OutPutString("PlayerState: " + StateManager_.GetCurStateStateName());
}

void Penitent::GroundCheck()
{
	float4 Color; 

	if (true == IsLadder_)
	{
		Color = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 130));
	}

	else
	{
		Color = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 95));
	}

	if (true == Color.CompareInt4D(float4::BLACK)) //땅이라면 
	{
		IsJump_ = false;
		IsGround_ = true;

		UphillRoadCheck(); //오르막길 체크
	}

	else if (true == Color.CompareInt4D(float4::MAGENTA))
	{
		IsJump_ = false;
		IsGround_ = true;

		if (true == GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
		{
			IsGround_ = false;
		}
	}

	else
	{
		IsGround_ = false;
	}
}

void Penitent::LadderCheck()
{
	float4 LowColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 200));
	float4 MiddleColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));

	if (true == LowColor.CompareInt4D(float4::GREEN))
	{
		if (GameEngineInput::GetInst()->IsDownKey("PenitentDown"))
		{
			StateManager_.ChangeState("LadderClimb");
		}
	}

	if (true == MiddleColor.CompareInt4D(float4::GREEN))
	{
		StateManager_.ChangeState("LadderClimb");
	}
}

void Penitent::UphillRoadCheck()
{
	while (true)
	{
		float4 Color = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 94));
		
		if (true == Color.CompareInt4D(float4::BLACK))
		{
			GetTransform().SetWorldMove(float4::UP);
			continue;
		}

		else
		{
			break;
		}
	}
}

bool Penitent::LeftObstacleCheck()
{
	float4 LeftColor;

	if (true == IsSlide_)
	{
		LeftColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x - 20, -(GetTransform().GetWorldPosition().y - 20));
	}

	else
	{
		LeftColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x - 20, -(GetTransform().GetWorldPosition().y - 10));
	}

	if (true == LeftColor.CompareInt4D(float4::BLACK))
	{
		return true;
	}

	return false;
}

bool Penitent::RightObstacleCheck()
{
	float4 RightColor;

	if (true == IsSlide_)
	{
		RightColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x + 20, -(GetTransform().GetWorldPosition().y - 20));
	}

	else
	{
		RightColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x + 20, -(GetTransform().GetWorldPosition().y - 10));
	}

	if (true == RightColor.CompareInt4D(float4::BLACK))
	{
		return true;
	}

	return false;
}

void Penitent::End()
{

}

void Penitent::IdleStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("penintent_idle_anim");
	Collider_->GetTransform().SetWorldScale({ 100.f, 100.f, 1.0f });
}

void Penitent::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity_->SetActive(!IsGround_);
}

void Penitent::LadderClimbStart(const StateInfo& _Info)
{
	IsLadder_ = true;
	IsGround_ = false;
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

	if (0.6f <= JumpTime_)
	{
		JumpTime_ = 0.f;

		StateManager_.ChangeState("Idle");
	}
}

void Penitent::SlideStart(const StateInfo& _Info)
{
	IsSlide_ = true;
	Collider_->GetTransform().SetWorldScale({ 200.f, 100.f, 1.0f });
}

void Penitent::SlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SlideTime_ += _DeltaTime;
	GetTransform().SetWorldMove(Dir_ * 400 * _DeltaTime);

	if (true == RightObstacleCheck()
		|| true == LeftObstacleCheck())
	{
		IsSlide_ = false;
		StateManager_.ChangeState("Idle");
	}

	if (0.5f <= SlideTime_)
	{
		IsSlide_ = false;
		SlideTime_ = 0.f;
		StateManager_.ChangeState("Idle");
	}

	Gravity_->SetActive(!IsGround_);
}

void Penitent::RecoveryStart(const StateInfo& _Info)
{
	int Size = static_cast<int>(Flasks_.size() - 1);

	if (0 >= Size)
	{
		StateManager_.ChangeState("Idle");
		return;
	}

	for (int i = Size; i >= 0; --i)
	{
		if (true == Flasks_[i])
		{
			PlusHP(10);

			Flasks_[i] = false;
			PlayerUI_->UseFlask(i);
			return;
		}
	}	

	StateManager_.ChangeState("Idle");
}

void Penitent::RecoveryUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Penitent::DeathStart(const StateInfo& _Info)
{
}

void Penitent::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Penitent::HitStart(const StateInfo& _Info)
{
	//GameEngineDebug::OutPutString("Hit!");
	StateManager_.ChangeState("Idle");
}

void Penitent::HitUpdate(float _DeltaTime, const StateInfo& _Info)
{
}


//피격 함수
bool Penitent::HitMonster(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return false;
}

bool Penitent::HitProjectile(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	StateManager_.ChangeState("Hit");
	return false;
}






