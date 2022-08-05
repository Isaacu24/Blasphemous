#include "ElderBrother.h"
#include "PreCompile.h"

ElderBrother::ElderBrother() 
{
}

ElderBrother::~ElderBrother() 
{
}

void ElderBrother::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationCutTexture("elderBrother_idle", {"elderBrother_idle.png", 0, 9, 0.15f, true});
	Renderer_->CreateFrameAnimationCutTexture("elderBrother_jump", { "elderBrother_jump.png", 0, 24, 0.15f, true });
	Renderer_->CreateFrameAnimationCutTexture("elderBrother_attack", { "elderBrother_attack.png", 0, 23, 0.1f, true });
	Renderer_->CreateFrameAnimationCutTexture("elderBrother_death", { "elderBrother_death.png", 0, 48, 0.1f, false });
	Renderer_->GetTransform().SetWorldScale({1200, 700});
	Renderer_->SetPivot(PIVOTMODE::BOT);

	State_.CreateStateMember("Idle", std::bind(&ElderBrother::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&ElderBrother::IdleStart, this, std::placeholders::_1));
	State_.CreateStateMember("Jump", std::bind(&ElderBrother::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&ElderBrother::JumpStart, this, std::placeholders::_1));
	State_.CreateStateMember("Attack", std::bind(&ElderBrother::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&ElderBrother::AttackStart, this, std::placeholders::_1));
	State_.CreateStateMember("Death", std::bind(&ElderBrother::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&ElderBrother::DeathStart, this, std::placeholders::_1));
	State_.ChangeState("Idle");

	Gravity_ = CreateComponent<GravityComponent>();

	DetectCollider_ = CreateComponent<GameEngineCollision>();
	DetectCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
	DetectCollider_->GetTransform().SetWorldScale({ 2000.0f, 500.0f, 1.0f });
}

void ElderBrother::Update(float _DeltaTime)
{
	State_.Update(_DeltaTime);

	if (true == GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 89.f)))
	{
		if (true == UphillRoadCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 90.f)))
		{
			GetTransform().SetWorldMove(float4::UP);
		}
	}

	Gravity_->SetActive(!IsGround_);
}

void ElderBrother::End()
{
}

void ElderBrother::IdleStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("elderBrother_idle");
}

void ElderBrother::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	DetectCollider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D,
		std::bind(&ElderBrother::DecideState, this, std::placeholders::_1, std::placeholders::_2));
}

void ElderBrother::JumpStart(const StateInfo& _Info)
{
	Speed_ = 600.f;
	Renderer_->ChangeFrameAnimation("elderBrother_jump");
	Renderer_->AnimationBindEnd("elderBrother_jump", std::bind(&ElderBrother::ChangeIdle, this, std::placeholders::_1));

}

void ElderBrother::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Speed_ -= 1.f;
	GetTransform().SetWorldMove(float4::UP * Speed_ * _DeltaTime);
	GetTransform().SetWorldMove(float4::LEFT * 50 * _DeltaTime);
}

void ElderBrother::AttackStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("elderBrother_attack");
	Renderer_->AnimationBindEnd("elderBrother_attack", std::bind(&ElderBrother::ChangeIdle, this, std::placeholders::_1));
}

void ElderBrother::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void ElderBrother::DeathStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("elderBrother_death");
}

void ElderBrother::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

bool ElderBrother::DecideState(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	//if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
	//{
	//	Renderer_->GetTransform().PixLocalPositiveX();
	//}

	//else
	//{
	//	State_.ChangeState("Jump");
	//	Renderer_->GetTransform().PixLocalNegativeX();
	//}

	//float Distance = abs(_This->GetTransform().GetWorldPosition().x - _Other->GetTransform().GetWorldPosition().x);

	//if (500 >= Distance)
	//{
	//	State_.ChangeState("Attack");
	//}

	return true;
}
