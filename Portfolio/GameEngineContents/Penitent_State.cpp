#include "PreCompile.h"
#include "Penitent.h"
#include "PlayerUI.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"


void Penitent::FreezeStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("penitent_sheathedIdle"); }

void Penitent::FreezeUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::FreezeEnd(const StateInfo& _Info) {}

void Penitent::IdleStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("penintent_idle_anim"); }

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

void Penitent::IdleEnd(const StateInfo& _Info) {}

void Penitent::MoveStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("penintent_start_run_anim"); }

void Penitent::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();
        Dir_ = GetTransform().GetRightVector();

        AttackDir_ = 1;

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

        AttackDir_ = -1;

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

        AttackDir_ = 1;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();
        Dir_ += -(GetTransform().GetLeftVector() * 3.f);

        AttackDir_ = -1;
    }

    GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::JumpEnd(const StateInfo& _Info) {}

void Penitent::FallStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("penitent_falling_loop_anim"); }

void Penitent::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpForce_.y -= _DeltaTime * 100.f;

    Dir_ = GetTransform().GetUpVector() * 10.f;

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();
        Dir_ += GetTransform().GetRightVector() * 3.f;

        AttackDir_ = 1;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();
        Dir_ += -(GetTransform().GetLeftVector() * 3.f);

        AttackDir_ = -1;
    }

    if (true == IsGround_)
    {
        State_.ChangeState("Idle");
        return;
    }

    GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::FallEnd(const StateInfo& _Info) { JumpForce_ = 100.f; }

void Penitent::CrouchStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_crouch_anim");

    Collider_->GetTransform().SetWorldScale({ColScale_.y, ColScale_.x});
    Collider_->GetTransform().SetWorldMove({0, -50});
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
    Collider_->GetTransform().SetWorldScale(ColScale_);
    Collider_->GetTransform().SetWorldMove({0, 50});
}

void Penitent::SlideStart(const StateInfo& _Info)
{
    SlideForce_ = 500.f;
    MetaRenderer_->ChangeMetaAnimation("penitent_dodge_anim");

    Collider_->GetTransform().SetWorldScale({ColScale_.y, ColScale_.x});
    Collider_->GetTransform().SetWorldMove({0, -50});
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
    Collider_->GetTransform().SetWorldScale(ColScale_);
    Collider_->GetTransform().SetWorldMove({0, 50});
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
        GetTransform().SetWorldMove((Dir_ * float4::UP) * 100.f * _DeltaTime);
        IsDangle_ = true;
        MetaRenderer_->ChangeMetaAnimation("penitent_climbledge_reviewed");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
    {
        State_.ChangeState("Fall");
        IsDangle_  = true;
        JumpForce_ = 10.f;
    }
}

void Penitent::DangleEnd(const StateInfo& _Info) {}

void Penitent::LadderClimbStart(const StateInfo& _Info)
{
    //한 프레임 false 상태로 만들고 다음 상태일 때 체크
    IsGround_ = false;
    MetaRenderer_->ChangeMetaAnimation("penintent_ladder_climb_loop_anim");
}

void Penitent::LadderClimbUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (false == IsLadder_)
    {
        if (GameEngineInput::GetInst()->IsPressKey("PenitentUp"))
        {
            CilmbY_ = 30.f;

            MetaRenderer_->ChangeMetaAnimation("penintent_ladder_climb_loop_anim");
            GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
        }

        else if (GameEngineInput::GetInst()->IsUpKey("PenitentUp"))
        {
            //애니메이션 멈춤
        }

        if (GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
        {
            CilmbY_ = -50;

            MetaRenderer_->ChangeMetaAnimation("penintent_ladder_climb_loop_anim");
            GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
        }

        else if (GameEngineInput::GetInst()->IsUpKey("PenitentDown"))
        {
            //애니메이션 멈춤
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

    if (0 < AttackDir_) //오른쪽
    {
        AttackCollider_->GetTransform().SetWorldMove({AttackDir_ * 80.f, 50.f});
    }

    else if (0 > AttackDir_) //왼쪽
    {
        AttackCollider_->GetTransform().SetWorldMove({AttackDir_ * 80.f, 50.f});
    }
}

void Penitent::AttackUpdate(float _DeltaTime, const StateInfo& _Info) 
{

}

void Penitent::AttackEnd(const StateInfo& _Info)
{
    AttackCollider_->Off();
    AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
}