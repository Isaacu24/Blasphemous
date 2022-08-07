#include "PreCompile.h"
#include "GiantSword.h"

GiantSword::GiantSword() 
{
}

GiantSword::~GiantSword() 
{
}


void GiantSword::Start()
{
	EyeRenderer_ = CreateComponent<GameEngineTextureRenderer>(); 
	EyeRenderer_->SetTexture("pontiff_giantSword_eyeGlobeSprite.png");
	EyeRenderer_->GetTransform().SetLocalScale({ 125, 400 });

	IrisRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	IrisRenderer_->SetTexture("pontiff_giantSword_irisSprite.png");
	IrisRenderer_->GetTransform().SetLocalScale({ 125, 400 });

	//EyeLidRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//EyeLidRenderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_eyeLids", { "pontiff_giantSword_eyeLids.png", 0, 19, 0.1f, true });
	//EyeLidRenderer_->GetTransform().SetLocalMove({0, 120.f});
	//EyeLidRenderer_->GetTransform().SetLocalScale({ 150, 200 });

	IrisRenderer_->Off();
	EyeRenderer_->Off();
	//EyeLidRenderer_->Off();

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_teleportOUT", { "pontiff_giantSword_teleportOUT.png", 0, 19, 0.1f, false });
	Renderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_teleportIN", { "pontiff_giantSword_teleportIN.png", 0, 17, 0.1f, false });
	Renderer_->GetTransform().SetLocalScale({ 125, 400 });

	State_.CreateStateMember("TeleportIN", std::bind(&GiantSword::TeleportINUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&GiantSword::TeleportINStart, this, std::placeholders::_1));
	State_.CreateStateMember("TeleportOut", std::bind(&GiantSword::TeleportOutUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&GiantSword::TeleportOutStart, this, std::placeholders::_1));
	State_.CreateStateMember("TeleportAttack", std::bind(&GiantSword::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&GiantSword::AttackStart, this, std::placeholders::_1), std::bind(&GiantSword::AttackEnd, this, std::placeholders::_1));
	State_.ChangeState("TeleportAttack");
}

void GiantSword::Update(float _DeltaTime)
{
	State_.Update(_DeltaTime);

}

void GiantSword::End()
{
}


void GiantSword::TeleportINStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("pontiff_giantSword_teleportOut");
}

void GiantSword::TeleportINUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void GiantSword::TeleportOutStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("pontiff_giantSword_teleportIN");
}

void GiantSword::TeleportOutUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void GiantSword::AttackStart(const StateInfo& _Info)
{
	Renderer_->SetTexture("pontiff_giantSword_swordSprite.png");

	IrisRenderer_->On();
	EyeRenderer_->On();
	//EyeLidRenderer_->On();

	//EyeLidRenderer_->ChangeFrameAnimation("pontiff_giantSword_eyeLids");
}

void GiantSword::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Time_ += _DeltaTime;

	if (5.f < Time_)
	{
		Time_ = 0.f;
		State_.ChangeState("TeleportOut");
	}
}

void GiantSword::AttackEnd(const StateInfo& _Info)
{
	IrisRenderer_->Off();
	EyeRenderer_->Off();
	//EyeLidRenderer_->Off();
}
