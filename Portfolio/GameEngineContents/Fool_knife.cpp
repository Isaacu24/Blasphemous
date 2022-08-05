#include "PreCompile.h"
#include "Fool_knife.h"

Fool_knife::Fool_knife()
{
}

Fool_knife::~Fool_knife()
{
}

void Fool_knife::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationCutTexture("fool_idle_knife", { "fool_idle_knife.png", 0, 11, 0.1f, true });
	Renderer_->CreateFrameAnimationCutTexture("Fool_hurt_knife", { "Fool_hurt_knife.png", 0, 8, 0.1f, false });
	Renderer_->CreateFrameAnimationCutTexture("Fool_turn_knife", { "Fool_turn_knife.png", 0, 6, 0.1f, false });
	Renderer_->CreateFrameAnimationCutTexture("Fool_walk_knife", { "Fool_walk_knife.png", 0, 8, 0.1f, true });
	Renderer_->CreateFrameAnimationCutTexture("Fool_death_knife", { "Fool_death_knife.png", 0, 13, 0.1f, false });
	Renderer_->ChangeFrameAnimation("fool_idle_knife");
	Renderer_->GetTransform().SetWorldScale({ 400, 300 });
	Renderer_->SetPivot(PIVOTMODE::BOT);

	Gravity_ = CreateComponent<GravityComponent>();

	DetectCollider_ = CreateComponent<GameEngineCollision>();
	DetectCollider_->ChangeOrder(COLLISIONORDER::Monster);
	DetectCollider_->GetTransform().SetWorldScale({ 600.0f, 300.0f, 1.0f });

	State_.CreateStateMember("Idle", std::bind(&Fool_knife::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Fool_knife::IdleStart, this, std::placeholders::_1));
	State_.CreateStateMember("Patrol", std::bind(&Fool_knife::PatrolUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Fool_knife::PatrolStart, this, std::placeholders::_1));
	State_.CreateStateMember("Track", std::bind(&Fool_knife::TrackUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Fool_knife::TrackStart, this, std::placeholders::_1));
	State_.CreateStateMember("Death", std::bind(&Fool_knife::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Fool_knife::DeathStart, this, std::placeholders::_1));
	State_.CreateStateMember("Turn", std::bind(&Fool_knife::TurnUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Fool_knife::TurnStart, this, std::placeholders::_1));
	State_.CreateStateMember("Hurt", std::bind(&Fool_knife::HurtUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Fool_knife::HurtStart, this, std::placeholders::_1));
	State_.ChangeState("Patrol");

	SetSpeed(70.f);

	PatrolStart_ = true;
}

void Fool_knife::Update(float _DeltaTime)
{
	State_.Update(_DeltaTime);

	IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 35));

	Gravity_->SetActive(!IsGround_);

	if (true == DetectCollider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D,
		std::bind(&Fool_knife::TrackPlayer, this, std::placeholders::_1, std::placeholders::_2)))
	{
		IsCollision_ = true;
	}

	else
	{
		if (true == IsCollision_)
		{
			IsCollision_ = false;

			State_.ChangeState("Patrol");
		}
	}
}

void Fool_knife::End()
{
}


void Fool_knife::PatrolMoveX(float _DeltaTime)
{
	if (true == PatrolStart_
		&& false == PatrolEnd_)
	{
		if (true == RightObstacleCheck(GetTransform().GetWorldPosition().x + 50, -(GetTransform().GetWorldPosition().y + 35)))
		{
			GetTransform().SetWorldMove(float4::RIGHT * Speed_ * _DeltaTime);
		}

		else if (true == RightObstacleCheck(GetTransform().GetWorldPosition().x + 50, -(GetTransform().GetWorldPosition().y)))
		{
			State_.ChangeState("Turn");

			PatrolStart_ = true;
			PatrolEnd_ = false;
		}

		else
		{
			State_.ChangeState("Turn");

			PatrolEnd_ = true;
			PatrolStart_ = false;
		}
	}

	else if (false == PatrolStart_
		&& true == PatrolEnd_)
	{
		if (true == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 50, -(GetTransform().GetWorldPosition().y + 35)))
		{
			GetTransform().SetWorldMove(float4::LEFT * Speed_ * _DeltaTime);
		}

		else if (true == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 50, -(GetTransform().GetWorldPosition().y)))
		{
			State_.ChangeState("Turn");

			PatrolStart_ = true;
			PatrolEnd_ = false;
		}

		else
		{
			State_.ChangeState("Turn");

			PatrolStart_ = true;
			PatrolEnd_ = false;
		}
	}
}

void Fool_knife::IdleStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("fool_idle_knife");
}

void Fool_knife::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Fool_knife::PatrolStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("Fool_walk_knife");

	if (true == PatrolStart_)
	{
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	else if (true == PatrolEnd_)
	{
		Renderer_->GetTransform().PixLocalNegativeX();
	}
}

void Fool_knife::PatrolUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PatrolMoveX(_DeltaTime);
}

void Fool_knife::TrackStart(const StateInfo& _Info)
{
	if ("Track" == _Info.PrevState)
	{
		return;
	}

	Renderer_->ChangeFrameAnimation("Fool_walk_knife");
}

void Fool_knife::TrackUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsPlayerLeft_)
	{
		if (false == RightObstacleCheck(GetTransform().GetWorldPosition().x + 50, -(GetTransform().GetWorldPosition().y + 35)))
		{
			Renderer_->ChangeFrameAnimation("fool_idle_knife");
			return;
		}

		GetTransform().SetWorldMove(float4::RIGHT * Speed_ * _DeltaTime);
	}

	else if (true == IsPlayerRight_)
	{

		if (false == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 50, -(GetTransform().GetWorldPosition().y + 35)))
		{
			Renderer_->ChangeFrameAnimation("fool_idle_knife");
			return;
		}

		GetTransform().SetWorldMove(float4::LEFT * Speed_ * _DeltaTime);
	}
}

void Fool_knife::HurtStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("Fool_hurt_knife");
}

void Fool_knife::HurtUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Fool_knife::TurnStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("Fool_turn_knife");
	Renderer_->AnimationBindEnd("Fool_turn_knife", std::bind(&Fool_knife::TurnEnd, this, std::placeholders::_1));
}

void Fool_knife::TurnUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

void Fool_knife::DeathStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("Fool_death_knife");
	Renderer_->AnimationBindEnd("Fool_death_knife", std::bind(&Fool_knife::DeathEnd, this, std::placeholders::_1));
}

void Fool_knife::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}


