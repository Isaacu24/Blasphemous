#include "ElderBrother.h"
#include "PreCompile.h"

ElderBrother::ElderBrother() 
{
}

ElderBrother::~ElderBrother() 
{
}

//GameEngineTexture::Cut("elderBrother_idle.png", 3, 4);
//GameEngineTexture::Cut("elderBrother_jump.png", 4, 7);
//GameEngineTexture::Cut("elderBrother_attack.png", 4, 6);
//GameEngineTexture::Cut("elderBrother_death.png", 5, 10);
//GameEngineTexture::Cut("elderBrother_corpse.png", 4, 3);

void ElderBrother::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimation("elderBrother_idle", {"elderBrother_idle.png", 0, 9, 0.15f, true});
	Renderer_->CreateFrameAnimation("elderBrother_jump", { "elderBrother_jump.png", 0, 24, 0.15f, true });
	Renderer_->CreateFrameAnimation("elderBrother_attack", { "elderBrother_attack.png", 0, 23, 0.1f, true });
	Renderer_->CreateFrameAnimation("elderBrother_death", { "elderBrother_death.png", 0, 48, 0.1f, true });
	Renderer_->ChangeFrameAnimation("elderBrother_idle");
	Renderer_->SetPivot(PIVOTMODE::CENTER);

	State_.CreateStateMember("Idle", this, &ElderBrother::IdleUpdate, &ElderBrother::IdleStart);
	State_.CreateStateMember("Jump", this, &ElderBrother::JumpUpdate, &ElderBrother::JumpStart);
	State_.CreateStateMember("Attack", this, &ElderBrother::AttackUpdate, &ElderBrother::AttackStart);
	State_.CreateStateMember("Death", this, &ElderBrother::DeathUpdate, &ElderBrother::DeathStart);
	State_.ChangeState("Idle");

	DetectCollider_ = CreateComponent<GameEngineCollision>();
	DetectCollider_->GetTransform().SetWorldScale({500, 500});
	DetectCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
}

void ElderBrother::Update(float _DeltaTime)
{
	Renderer_;
	State_.Update(_DeltaTime);
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
	Renderer_->ChangeFrameAnimation("elderBrother_jump");

}

void ElderBrother::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void ElderBrother::AttackStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("elderBrother_attack");

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
	if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
	{
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	else
	{
		Renderer_->GetTransform().PixLocalNegativeX();
	}

	return false;
}
