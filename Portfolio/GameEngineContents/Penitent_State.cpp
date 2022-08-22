#include "PreCompile.h"
#include "Penitent.h"
#include "PlayerUI.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"


void Penitent::FreezeStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("penitent_sheathedIdle"); }

void Penitent::FreezeUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::FreezeEnd(const StateInfo& _Info) {}

void Penitent::IdleStart(const StateInfo& _Info) 
{ 
    MetaRenderer_->ChangeMetaAnimation("penintent_idle_anim"); 
}

void Penitent::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (20000 < GameEngineInput::GetInst()->GetThumbLX() || GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        State_.ChangeState("Move");
    }

    else if (0 > GameEngineInput::GetInst()->GetThumbLX() || GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        State_.ChangeState("Move");
    }

    //사다리 내려가기 or 앉기
    else if (GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
    {
        State_.ChangeState("Crouch");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentSlide"))
    {
        State_.ChangeState("Slide");
    }

    else if (GameEngineInput::GetInst()->IsDownKey("PenitentJump"))
    {
        State_.ChangeState("Jump");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitenAttack"))
    {
        State_.ChangeState("Attack");
    }

    //내리막길
    if (false == IsGround_)
    {
        JumpForce_ = 10.f;
        State_.ChangeState("Fall");
    }

    Gravity_->SetActive(!IsGround_);
}

void Penitent::IdleEnd(const StateInfo& _Info) 
{ 
}

void Penitent::MoveStart(const StateInfo& _Info) 
{ 
    MetaRenderer_->ChangeMetaAnimation("penintent_start_run_anim"); 
}

void Penitent::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();
        Dir_ = GetTransform().GetRightVector();

        RealXDir_ = 1;

        if (false == RightObstacleCheck())
        {
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
        }
    }

    else if (GameEngineInput::GetInst()->IsUpKey("PenitentRight"))
    {
        MetaRenderer_->ChangeMetaAnimation("penintent_stop_run_anim");
        return;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();
        Dir_ = -(GetTransform().GetLeftVector());

        RealXDir_ = -1;

        if (false == LeftObstacleCheck())
        {
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
        }
    }

    else if (GameEngineInput::GetInst()->IsUpKey("PenitentLeft"))
    {
        MetaRenderer_->ChangeMetaAnimation("penintent_stop_run_anim");
        return;
    }

    if (GameEngineInput::GetInst()->IsDownKey("PenitentJump"))
    {
        State_.ChangeState("Jump");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
    {
        State_.ChangeState("Crouch");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentSlide"))
    {
        State_.ChangeState("Slide");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitenAttack"))
    {
        State_.ChangeState("Attack");
    }

    //내리막길
    if (false == IsGround_)
    {
        JumpForce_ = 10.f;
        State_.ChangeState("Fall");
    }

    Gravity_->SetActive(!IsGround_);
}

void Penitent::MoveEnd(const StateInfo& _Info) {}


void Penitent::JumpStart(const StateInfo& _Info)
{
    JumpForce_ = 100.f;
    MetaRenderer_->ChangeMetaAnimation("penitent_jump_anim");
}

void Penitent::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpForce_.y -= _DeltaTime * 100.f;

    Dir_ = GetTransform().GetUpVector() * 10.f;

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();
        Dir_ += GetTransform().GetRightVector() * 3.f;

        RealXDir_ = 1;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();
        Dir_ += -(GetTransform().GetLeftVector() * 3.f);

        RealXDir_ = -1;
    }

    GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::JumpEnd(const StateInfo& _Info) {}

void Penitent::FallStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("penitent_falling_loop_anim"); }

void Penitent::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpForce_.y -= _DeltaTime * 100.f;
    FallTime_ += _DeltaTime;

    Dir_ = GetTransform().GetUpVector() * 10.f;

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();
        Dir_ += GetTransform().GetRightVector() * 3.f;

        RealXDir_ = 1;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();
        Dir_ += -(GetTransform().GetLeftVector() * 3.f);

        RealXDir_ = -1;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
    {
        JumpForce_.y -= _DeltaTime * 100.f;
    }

    if (true == IsGround_)
    {
        ChangeState("Landing");
        return;
    }

    GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::FallEnd(const StateInfo& _Info) { JumpForce_ = 100.f; }

void Penitent::LandingStart(const StateInfo& _Info)
{
    if (1.0f <= FallTime_)
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_hardlanding_rocks_anim");
    }

    else
    {
        MetaRenderer_->ChangeMetaAnimation("penintent_standing_up");

        //모션 캔슬
        if (GameEngineInput::GetInst()->IsPressKey("PenitentRight")
            || GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
        {
            ChangeState("Move");
        }
    }
}

void Penitent::LandingUpdate(float _DeltaTime, const StateInfo& _Info) { Gravity_->SetActive(!IsGround_); }

void Penitent::LandingEnd(const StateInfo& _Info) { FallTime_ = 0.f; }


void Penitent::CrouchStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_crouch_anim");

    BodyCollider_->GetTransform().SetWorldScale({ColScale_.y, ColScale_.x});
    BodyCollider_->GetTransform().SetWorldMove({0, -50});
}

void Penitent::CrouchUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsUpKey("PenitentDown"))
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_crouch_up_anim");
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();
    }
}

void Penitent::CrouchEnd(const StateInfo& _Info)
{
    BodyCollider_->GetTransform().SetWorldScale(ColScale_);
    BodyCollider_->GetTransform().SetWorldMove({0, 50});
}

void Penitent::SlideStart(const StateInfo& _Info)
{
    SlideForce_ = 500.f;
    MetaRenderer_->ChangeMetaAnimation("penitent_dodge_anim");

    BodyCollider_->GetTransform().SetWorldScale({ColScale_.y, ColScale_.x});
    BodyCollider_->GetTransform().SetWorldMove({0, -50});
}

void Penitent::SlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == RightObstacleCheck() || true == LeftObstacleCheck())
    {
        return;
    }

    SlideForce_ -= _DeltaTime * 350.f;
    GetTransform().SetWorldMove(Dir_ * SlideForce_ * _DeltaTime);

    Gravity_->SetActive(!IsGround_);

    //내리막길 문제있음
    if (false == IsGround_)
    {
        JumpForce_ = 10.f;
        State_.ChangeState("Fall");
    }
}

void Penitent::SlideEnd(const StateInfo& _Info)
{
    BodyCollider_->GetTransform().SetWorldScale(ColScale_);
    BodyCollider_->GetTransform().SetWorldMove({0, 50});
}

void Penitent::DangleStart(const StateInfo& _Info)
{
    Gravity_->SetActive(false);
    MetaRenderer_->ChangeMetaAnimation("penitent_hangonledge_anim");
}


void Penitent::DangleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsPressKey("PenitentUp"))
    {
        IsDangle_     = true;
        IsClimbLedge_ = true;
        MetaRenderer_->ChangeMetaAnimation("penitent_climbledge_reviewed");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
    {
        State_.ChangeState("Fall");
        IsDangle_  = true;
        JumpForce_ = 10.f;
    }

    if (true == IsClimbLedge_)
    {
        float4 StartPos = GetTransform().GetWorldPosition();
        float4 EndPos   = GetTransform().GetWorldPosition() + float4{RealXDir_ * 100.f, 300.f};

        GetTransform().SetWorldPosition(float4::Lerp(StartPos, EndPos, _DeltaTime));
    }
}

void Penitent::DangleEnd(const StateInfo& _Info) { IsClimbLedge_ = false; }

void Penitent::LadderClimbStart(const StateInfo& _Info)
{
    //한 프레임 false 상태로 만들고 다음 상태일 때 체크
    IsGround_ = false;

    //위아래 분기 나누어야 함@
    MetaRenderer_->ChangeMetaAnimation("penintent_ladder_climb_loop_anim");
}

void Penitent::LadderClimbUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (false == IsLadder_)
    {
        if (GameEngineInput::GetInst()->IsPressKey("PenitentUp"))
        {
            CilmbY_ = 30.f;

            if (true == MetaRenderer_->GetPause())
            {
                MetaRenderer_->CurAnimationPauseSwitch();
            }

            MetaRenderer_->ChangeMetaAnimation("penintent_ladder_climb_loop_anim");
            GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
        }

        if (GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
        {
            CilmbY_ = -50;


            if (true == MetaRenderer_->GetPause())
            {
                MetaRenderer_->CurAnimationPauseSwitch();
            }


            MetaRenderer_->ChangeMetaAnimation("penintent_ladder_climb_loop_anim");
            GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
        }

        else if (GameEngineInput::GetInst()->IsUpKey("PenitentUp")
                 || GameEngineInput::GetInst()->IsUpKey("PenitentDown"))
        {
            //애니메이션 멈춤
            MetaRenderer_->CurAnimationPauseSwitch();
        }
    }

    if (true == IsGround_)
    {
        if (0 > CilmbY_)  //아래 사다리
        {
            IsLadder_ = true;
            Gravity_->SetActive(true);
            MetaRenderer_->ChangeMetaAnimation("penintent_ladder_up_from_ground");
        }

        else if (0 < CilmbY_)  //위 사다리
        {
            IsLadder_ = true;

            GetTransform().SetWorldUpMove(500.f, _DeltaTime);
            MetaRenderer_->ChangeMetaAnimation("penitent_ladder_down_from_ground_anim");
        }
    }
}

void Penitent::LadderClimbEnd(const StateInfo& _Info) { IsLadder_ = false; }

void Penitent::AttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_attack_combo_1");
    AttackCollider_->On();

    if (0 < RealXDir_)  //오른쪽
    {
        AttackCollider_->GetTransform().SetWorldMove({RealXDir_ * 80.f, 50.f});
    }

    else if (0 > RealXDir_)  //왼쪽
    {
        AttackCollider_->GetTransform().SetWorldMove({RealXDir_ * 80.f, 50.f});
    }
}

void Penitent::AttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::AttackEnd(const StateInfo& _Info)
{
    AttackCollider_->Off();
    AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
}

void Penitent::KnockBackStart(const StateInfo& _Info)
{
    if ("LadderClimb" == _Info.PrevState)
    {
        State_.ChangeState("LadderClimb");
        return;
    }

    //착지 시에 피격 당할 경우 추락 시간은 0
    FallTime_ = 0.f;

    MetaRenderer_->ChangeMetaAnimation("Penitent_pushback_grounded");
}

void Penitent::KnockBackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == RightObstacleCheck() || true == LeftObstacleCheck())
    {
        return;
    }

    GetTransform().SetWorldMove(float4{RealXDir_, 0} * 150.f * _DeltaTime);
}

void Penitent::KnockBackEnd(const StateInfo& _Info) {}
