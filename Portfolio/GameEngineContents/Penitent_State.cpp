#include "PreCompile.h"
#include "Penitent.h"
#include "PlayerUI.h"
#include "AttackCorpseEffecter.h"


void Penitent::IdleStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("penintent_idle_anim");
}

void Penitent::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (20000 < GameEngineInput::GetInst()->GetThumbLX()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
	{
		Renderer_->GetTransform().PixLocalPositiveX();

		if (false == RightObstacleCheck())
		{
			Dir_ = GetTransform().GetRightVector();
			GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
		}
	}

	if (0 > GameEngineInput::GetInst()->GetThumbLX()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
	{
		Renderer_->GetTransform().PixLocalNegativeX();

		if (false == LeftObstacleCheck())
		{
			Dir_ = GetTransform().GetLeftVector();
			GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
		}
	}

	if (GameEngineInput::GetInst()->IsDownKey("PenitentJump")
		&& false == IsJump_ && true == IsGround_
		|| GameEngineInput::GetInst()->IsDownButton("PenitentA")
		&& false == IsJump_ && true == IsGround_)
	{
		State_.ChangeState("Jump");
		PlayerUI_->SetTear(Tear_ += 123);
	}

	if (GameEngineInput::GetInst()->IsDownKey("PenitentRecovery")
		|| GameEngineInput::GetInst()->IsDownButton("PenitentLeftShoulder"))
	{
		State_.ChangeState("Recovery");
	}

	if (GameEngineInput::GetInst()->IsDownKey("PenitentSlide")
		&& true == IsGround_ && false == IsLadder_)
	{
		State_.ChangeState("Slide");
	}

	Gravity_->SetActive(!IsGround_);
}

void Penitent::FreezeStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation("penintent_idle_anim");
}

void Penitent::FreezeUpdate(float _DeltaTime, const StateInfo& _Info)
{
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
		State_.ChangeState("Idle");
	}
}



void Penitent::JumpStart(const StateInfo& _Info)
{
	IsJump_ = true;
}


void Penitent::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	JumpTime_ += _DeltaTime;

	Dir_ = GetTransform().GetUpVector() * 2;

	if (20000 < GameEngineInput::GetInst()->GetThumbLX()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
	{
		Renderer_->GetTransform().PixLocalPositiveX();

		if (false == RightObstacleCheck())
		{
			Dir_ += GetTransform().GetRightVector();
		}
	}

	if (0 > GameEngineInput::GetInst()->GetThumbLX()
		|| GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
	{
		Renderer_->GetTransform().PixLocalNegativeX();

		if (false == LeftObstacleCheck())
		{
			Dir_ += GetTransform().GetLeftVector();
		}
	}

	GetTransform().SetWorldMove(Dir_ * 350.f * _DeltaTime);

	if (0.5f <= JumpTime_)
	{
		JumpTime_ -= 0.5f;
		State_.ChangeState("Idle");
	}

	Gravity_->SetActive(!IsGround_);
}

void Penitent::SlideStart(const StateInfo& _Info)
{
	IsSlide_ = true;
	Collider_->GetTransform().SetWorldScale({ 200.f, 100.f });
	Collider_->GetTransform().SetWorldMove({0.f, -100.f});
}

void Penitent::SlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SlideTime_ += _DeltaTime;
	GetTransform().SetWorldMove(Dir_ * 500 * _DeltaTime);

	if (true == RightObstacleCheck()
		|| true == LeftObstacleCheck())
	{
		IsSlide_ = false;
		State_.ChangeState("Idle");
	}

	if (0.5f <= SlideTime_)
	{
		IsSlide_ = false;
		SlideTime_ = 0.f;
		State_.ChangeState("Idle");
	}

	Gravity_->SetActive(!IsGround_);
}

void Penitent::SlideEnd(const StateInfo& _Info)
{
	Collider_->GetTransform().SetWorldScale({ 100.f, 200.f});
	Collider_->GetTransform().SetWorldMove({ 0.f, 100.f });
}

void Penitent::RecoveryStart(const StateInfo& _Info)
{
	int Size = static_cast<int>(Flasks_.size() - 1);

	if (0 >= Size)
	{
		State_.ChangeState("Idle");
		return;
	}

	for (int i = Size; i >= 0; --i)
	{
		if (true == Flasks_[i])
		{
			PlusHP(10);

			Flasks_[i] = false;
			PlayerUI_->UseFlask(i);
			State_.ChangeState("Idle");
			return;
		}
	}

	State_.ChangeState("Idle");
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