#include "PreCompile.h"
#include "Penitent.h"
#include "PlayerUI.h"
#include "AttackCorpseEffecter.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

void Penitent::IdleStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("penintent_idle_anim 1"); }

void Penitent::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (20000 < GameEngineInput::GetInst()->GetThumbLX() || GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();

        if (false == RightObstacleCheck())
        {
            MetaRenderer_->ChangeMetaAnimation("penitent_running_anim");

            Dir_ = GetTransform().GetRightVector();
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
        }
    }

    if (0 > GameEngineInput::GetInst()->GetThumbLX() || GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();

        if (false == LeftObstacleCheck())
        {
            MetaRenderer_->ChangeMetaAnimation("penitent_running_anim");

            Dir_ = -(GetTransform().GetLeftVector());
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
        }
    }

    if (GameEngineInput::GetInst()->IsDownKey("PenitentJump") && false == IsJump_ && true == IsGround_
        || GameEngineInput::GetInst()->IsDownButton("PenitentA") && false == IsJump_ && true == IsGround_)
    {
        State_.ChangeState("Jump");
        PlayerUI_->SetTear(Tear_ += 123);
    }

    if (GameEngineInput::GetInst()->IsDownKey("PenitentRecovery")
        || GameEngineInput::GetInst()->IsDownButton("PenitentLeftShoulder"))
    {
        State_.ChangeState("Recovery");
    }

    if (GameEngineInput::GetInst()->IsDownKey("PenitentSlide") && true == IsGround_)
    {
        State_.ChangeState("Slide");
    }

    if (GameEngineInput::GetInst()->IsDownKey("PenitentDown"))
    {
        ChangeState("Crouch");
    }

    Gravity_->SetActive(!IsGround_);
}

void Penitent::CrouchStart(const StateInfo& _Info)
{
    Collider_->GetTransform().SetWorldScale({ColScale_.y, ColScale_.x});
    Collider_->GetTransform().SetWorldMove({0, -50});
}

void Penitent::CrouchUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == GameEngineInput::GetInst()->IsUpKey("PenitentDown"))
    {
        ChangeState("Idle");
    }
}

void Penitent::CrouchEnd(const StateInfo& _Info)
{
    Collider_->GetTransform().SetWorldScale(ColScale_);
    Collider_->GetTransform().SetWorldMove({0, 50});
}

void Penitent::DangleStart(const StateInfo& _Info) {}

void Penitent::DangleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    Gravity_->SetActive(false);

    if (true == GameEngineInput::GetInst()->IsDownKey("PenitentDown"))
    {
        ChangeState("Idle");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentUp"))
    {

    }
}

void Penitent::DangleEnd(const StateInfo& _Info) {}

void Penitent::FreezeStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("penintent_idle_anim 1"); }

void Penitent::FreezeUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::LadderClimbStart(const StateInfo& _Info) { IsGround_ = false; }

void Penitent::LadderClimbUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (20000 < GameEngineInput::GetInst()->GetThumbLY() || GameEngineInput::GetInst()->IsPressKey("PenitentUp"))
    {
        CilmbY_ = 30;
        GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
    }

    if (0 > GameEngineInput::GetInst()->GetThumbLY() || GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
    {
        CilmbY_ = -10;
        GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
    }


    if (true == IsGround_)
    {
        State_.ChangeState("Idle");
    }
}


void Penitent::JumpStart(const StateInfo& _Info)
{
    IsJump_ = true;

    MetaRenderer_->ChangeMetaAnimation("penitent_jump_anim");
}


void Penitent::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpTime_ += _DeltaTime;

    Dir_ = GetTransform().GetUpVector() * 2;

    if (20000 < GameEngineInput::GetInst()->GetThumbLX() || GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();

        if (false == RightObstacleCheck())
        {
            Dir_ += GetTransform().GetRightVector();
        }
    }

    if (0 > GameEngineInput::GetInst()->GetThumbLX() || GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();

        if (false == LeftObstacleCheck())
        {
            Dir_ -= GetTransform().GetLeftVector();
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
    Collider_->GetTransform().SetWorldScale({ColScale_.y, ColScale_.x});
    Collider_->GetTransform().SetWorldMove({0, -50});

    MetaRenderer_->ChangeMetaAnimation("penitent_dodge_anim");
}

void Penitent::SlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == RightObstacleCheck() || true == LeftObstacleCheck())
    {
        return;
    }
    
    SlideTime_ += _DeltaTime;
    GetTransform().SetWorldMove(Dir_ * 500 * _DeltaTime);

    Gravity_->SetActive(!IsGround_);
}

void Penitent::SlideEnd(const StateInfo& _Info)
{
    Collider_->GetTransform().SetWorldScale(ColScale_);
    Collider_->GetTransform().SetWorldMove({0, 50});
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

void Penitent::RecoveryUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::DeathStart(const StateInfo& _Info) {}

void Penitent::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}