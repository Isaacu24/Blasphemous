#include "Penitent.h"
#include "PreCompile.h"
#include "GravityComponent.h"
#include "PlayerUI.h"

Penitent* Penitent::MainPlayer_ = nullptr;

Penitent::Penitent() 
	: State_{}
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
		Renderer_->CreateFrameAnimationCutTexture("penintent_idle_anim", { "penintent_idle_anim.png", 0, 12, 0.1f, true });
		Renderer_->CreateFrameAnimationCutTexture("penitent_sheathedIdle", { "penitent_sheathedIdle.png", 0, 45, 0.1f, true });
		Renderer_->CreateFrameAnimationCutTexture("penitent_verticalattack_LVL3_anim", { "penitent_verticalattack_LVL3_anim.png", 0, 23, 0.05f, true });
		Renderer_->CreateFrameAnimationCutTexture("penitent_climbledge_reviewed", { "penitent_climbledge_reviewed.png", 0, 11, 0.1f, true });
		Renderer_->CreateFrameAnimationCutTexture("penitent_dodge_attack_LVL3", { "penitent_dodge_attack_LVL3.png", 0, 26, 0.1f, true });
		Renderer_->CreateFrameAnimationCutTexture("penitent_falling_ahead_anim 1", { "penitent_falling_ahead_anim 1.png", 0, 5, 0.1f, true });
		Renderer_->CreateFrameAnimationCutTexture("penitent_jumpoff_new", { "penitent_jumpoff_new.png", 0, 4, 0.1f, true });
	}

	State_.CreateStateMember("Freeze", std::bind(&Penitent::FreezeUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Penitent::FreezeStart, this, std::placeholders::_1));
	State_.CreateStateMember("Idle", std::bind(&Penitent::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Penitent::IdleStart, this, std::placeholders::_1));
	State_.CreateStateMember("LadderClimb", std::bind(&Penitent::LadderClimbUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Penitent::LadderClimbStart, this, std::placeholders::_1));
	State_.CreateStateMember("Jump", std::bind(&Penitent::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Penitent::JumpStart, this, std::placeholders::_1));
	State_.CreateStateMember("Slide", std::bind(&Penitent::SlideUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Penitent::SlideStart, this, std::placeholders::_1));
	State_.CreateStateMember("Crouch", std::bind(&Penitent::RecoveryUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Penitent::RecoveryStart, this, std::placeholders::_1));
	State_.CreateStateMember("Recovery", std::bind(&Penitent::RecoveryUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Penitent::RecoveryStart, this, std::placeholders::_1));
	State_.CreateStateMember("Hit", std::bind(&Penitent::HitUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Penitent::HitStart, this, std::placeholders::_1));
	State_.CreateStateMember("Death", std::bind(&Penitent::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Penitent::DeathStart, this, std::placeholders::_1));
	State_.ChangeState("Idle");

	PlayerUI_->SetTear(Tear_);
}

void Penitent::Update(float _DeltaTime)
{ 
	State_.Update(_DeltaTime);

	GroundCheck(); 
	LadderCheck(); 
	CollisionCheck();

	if (true == GameEngineInput::GetInst()->IsDownKey("FreeCamera"))
	{
		GetLevel()->GetMainCameraActor()->FreeCameraModeOnOff();
	}

	GameEngineDebug::OutPutString("PlayerState: " + State_.GetCurStateStateName());
}

void Penitent::End()
{

}


