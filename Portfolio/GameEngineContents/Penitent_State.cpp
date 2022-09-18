#include "PreCompile.h"
#include "Penitent.h"
#include "PlayerUI.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"
#include "MoveEffect.h"
#include "HitEffect.h"
#include "AttackEffect.h"
#include "StageBase.h"

void Penitent::FreezeStart(const StateInfo& _Info) 
{ 
    MetaRenderer_->ChangeMetaAnimation("penitent_sheathedIdle_Start"); 
}

void Penitent::FreezeUpdate(float _DeltaTime, const StateInfo& _Info) 
{
    Gravity_->SetActive(!IsGround_); 
}

void Penitent::FreezeEnd(const StateInfo& _Info) {}


void Penitent::IdleStart(const StateInfo& _Info)
{
    FallTime_ = 0.1f;
    MetaRenderer_->ChangeMetaAnimation("penintent_idle_anim");
}

void Penitent::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (20000 < GameEngineInput::GetInst()->GetThumbLX()
        || true == GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        State_.ChangeState("Move");
    }

    else if (0 > GameEngineInput::GetInst()->GetThumbLX()
             || true == GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        State_.ChangeState("Move");
    }

    //사다리 내려가기 or 앉기
    else if (true == GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
    {
        State_.ChangeState("Crouch");
    }

    else if (true == GameEngineInput::GetInst()->IsPressKey("PenitentSlide"))
    {
        State_.ChangeState("Slide");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentJump"))
    {
        State_.ChangeState("Jump");
    }

    else if (true == GameEngineInput::GetInst()->IsPressKey("PenitentAttack"))
    {
        State_.ChangeState("Attack");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentParry"))
    {
        State_.ChangeState("Parrying");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentRecovery"))
    {
        State_.ChangeState("Recovery");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentTelport") && true == IsReturnToPort_)
    {
        State_.ChangeState("ReturnToPort");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentPary") && true == IsGround_)
    {
        State_.ChangeState("PrayAttack");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentL"))
    {
        State_.ChangeState("RangeAttack");
    }

    //내리막길
    if (false == IsGround_)
    {
        if (false == FallCollisionCheck())
        {
            JumpForce_ = 10.f;
            State_.ChangeState("Fall");
        }
    }

    Gravity_->SetActive(!IsGround_);
}

void Penitent::IdleEnd(const StateInfo& _Info) {}

void Penitent::MoveStart(const StateInfo& _Info)
{
    RunTime_ = 0.f;
    MetaRenderer_->ChangeMetaAnimation("penintent_start_run_anim");
}


void Penitent::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
    SHORT ThumbLX = GameEngineInput::GetInst()->GetThumbLX();

    if (true == GameEngineInput::GetInst()->IsPressKey("PenitentRight") || 30000 < ThumbLX)
    {
        GetTransform().PixLocalPositiveX();
        Dir_ = GetTransform().GetRightVector();

        RealXDir_ = 1;

        if (false == RightObstacleCheck())
        {
            RunTime_ += _DeltaTime;

            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
        }
    }

    else if (true == GameEngineInput::GetInst()->IsUpKey("PenitentRight") || -1000 >= ThumbLX)
    {
        if (1.f <= RunTime_)
        {
            MetaRenderer_->ChangeMetaAnimation("penintent_stop_run_anim");

            MoveEffect_->Renderer_->On();
            MoveEffect_->GetTransform().PixLocalPositiveX();
            MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()
                                                         + float4{RealXDir_ * 50.f, 0});
            MoveEffect_->Renderer_->ChangeMetaAnimation("penitent-stop-running-dust");
        }

        else
        {
            ChangeState("Idle");
        }

        return;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft") || -30000 > ThumbLX)
    {
        GetTransform().PixLocalNegativeX();
        Dir_ = -(GetTransform().GetLeftVector());

        RealXDir_ = -1;

        if (false == LeftObstacleCheck())
        {
            RunTime_ += _DeltaTime;
            GetTransform().SetWorldMove(Dir_ * Speed_ * _DeltaTime);
        }
    }

    else if (GameEngineInput::GetInst()->IsUpKey("PenitentLeft") || 1000 <= ThumbLX)
    {
        if (1.f <= RunTime_)
        {
            MetaRenderer_->ChangeMetaAnimation("penintent_stop_run_anim");

            MoveEffect_->Renderer_->On();
            MoveEffect_->GetTransform().PixLocalNegativeX();
            MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()
                                                         + float4{RealXDir_ * 50.f, 0});
            MoveEffect_->Renderer_->ChangeMetaAnimation("penitent-stop-running-dust");
        }

        else
        {
            ChangeState("Idle");
        }
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

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack"))
    {
        State_.ChangeState("Attack");
    }

    //내리막길
    if (false == IsGround_)
    {
        if (false == FallCollisionCheck())
        {
            JumpForce_ = 10.f;
            State_.ChangeState("Fall");
        }
    }

    Gravity_->SetActive(!IsGround_);
}

void Penitent::MoveEnd(const StateInfo& _Info) {}


void Penitent::JumpStart(const StateInfo& _Info)
{
    JumpForce_ = 100.f;
    MetaRenderer_->ChangeMetaAnimation("penitent_jump_anim");

    MoveEffect_->Renderer_->On();
    MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
    MoveEffect_->Renderer_->ChangeMetaAnimation("penitent-jumping-dust-anim");

    LastJumpPos_ = GetTransform().GetWorldPosition();
}

void Penitent::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpForce_.y -= _DeltaTime * 100.f;

    Dir_ = GetTransform().GetUpVector() * 10.f;

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();
        RealXDir_ = 1;

        MetaRenderer_->ChangeMetaAnimation("penitent_jum_forward_anim");

        if (false == RightObstacleCheck())
        {
            Dir_ += GetTransform().GetRightVector() * 3.f;
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();
        RealXDir_ = -1;

        MetaRenderer_->ChangeMetaAnimation("penitent_jum_forward_anim");

        if (false == LeftObstacleCheck())
        {
            Dir_ += -(GetTransform().GetLeftVector() * 3.f);
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack")
        && GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
    {
        ChangeState("VerticalAttack");
        return;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack"))
    {
        ChangeState("JumpAttack");
        return;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentL"))
    {
        ChangeState("JumpRangeAttack");
        return;
    }

    GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::JumpEnd(const StateInfo& _Info) {}

void Penitent::FallStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_falling_loop_anim");

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight")
        || GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_jum_forward_fall_anim");
    }
}

void Penitent::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpForce_.y -= _DeltaTime * 100.f;
    FallTime_ += _DeltaTime;

    Dir_ = GetTransform().GetUpVector() * 10.f;

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();
        RealXDir_ = 1;

        if (false == RightObstacleCheck())
        {
            Dir_ += -(GetTransform().GetLeftVector() * 3.f);
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();
        RealXDir_ = -1;

        if (false == LeftObstacleCheck())
        {
            Dir_ += -(GetTransform().GetLeftVector() * 3.f);
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack"))
    {
        ChangeState("JumpAttack");
        return;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
    {
        JumpForce_.y -= _DeltaTime * 100.f;
        FallTime_ += _DeltaTime / 2;
    }

    if (true == IsGround_)
    {
        ChangeState("Landing");
        return;
    }

    GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::FallEnd(const StateInfo& _Info) {}


void Penitent::JumpAttackStart(const StateInfo& _Info)
{
    //일단 인정하지도 증가하지도 않음.
    FallTime_ = 0.f;

    AttackEffect_->Renderer_->On();
    AttackEffect_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, PlayerEffectZ});

    AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_jumping_attack_slasheslvl2");

    if (GameEngineInput::GetInst()->IsPressKey("PenitentUp"))
    {
        AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_upward_attack_slash_lvl1");
    }

    MetaRenderer_->ChangeMetaAnimation("penitent_jumping_attack_noslashes");

    if (0 < RealXDir_)  //오른쪽
    {
        AttackEffect_->GetTransform().PixLocalPositiveX();
        AttackCollider_->GetTransform().SetWorldMove({RealXDir_ * 80.f, 50.f});
    }

    else if (0 > RealXDir_)  //왼쪽
    {
        AttackEffect_->GetTransform().PixLocalNegativeX();
        AttackCollider_->GetTransform().SetWorldMove({RealXDir_ * 80.f, 50.f});
    }
}

void Penitent::JumpAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpForce_.y -= _DeltaTime * 80.f;

    AttackEffect_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, PlayerEffectZ});

    Dir_ = GetTransform().GetUpVector() * 10.f;

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        GetTransform().PixLocalPositiveX();
        RealXDir_ = 1;

        if (false == RightObstacleCheck())
        {
            Dir_ += -(GetTransform().GetLeftVector() * 3.f);
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        GetTransform().PixLocalNegativeX();
        RealXDir_ = -1;

        if (false == LeftObstacleCheck())
        {
            Dir_ += -(GetTransform().GetLeftVector() * 3.f);
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentUp"))
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_upward_attack_jump");

        AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
        AttackCollider_->GetTransform().SetWorldMove({0.f, 150.f});
    }

    if (true == IsGround_)
    {
        ChangeState("Landing");
        return;
    }

    GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::JumpAttackEnd(const StateInfo& _Info)
{
    AttackCollider_->Off();
    AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});

    AttackEffect_->Renderer_->Off();
}

void Penitent::KnockBackStart(const StateInfo& _Info)
{
    if ("LadderClimb" == _Info.PrevState)
    {
        State_.ChangeState("LadderClimb");
        return;
    }

    FallTime_ = 0.f;
    MetaRenderer_->ChangeMetaAnimation("Penitent_pushback_grounded");
    MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};

    HitEffect_->Renderer_->On();
    HitEffect_->Renderer_->ChangeMetaAnimation("pushback_sparks_anim");

    if (0 > KnockBackXDir_)
    {
        HitEffect_->GetTransform().PixLocalPositiveX();
        MoveEffect_->GetTransform().PixLocalPositiveX();
        GetTransform().PixLocalPositiveX();
    }

    else
    {
        HitEffect_->GetTransform().PixLocalNegativeX();
        MoveEffect_->GetTransform().PixLocalNegativeX();
        GetTransform().PixLocalNegativeX();
    }

    CurStage_->SetForceY(5.f);
    CurStage_->SetShake(true);
}

void Penitent::KnockBackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == RightObstacleCheck() || true == LeftObstacleCheck())
    {
        return;
    }

    // if (false == IsGround_)
    //{
    //     ChangeState("Fall");
    // }

    if (0.2f <= _Info.StateTime && 1 <= MetaRenderer_->GetColorData().PlusColor.r)
    {
        MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
    }

    HitEffect_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 75.f, PlayerEffectZ});

    GetTransform().SetWorldMove(float4{KnockBackXDir_, 0} * 150.f * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::KnockBackEnd(const StateInfo& _Info) {}


void Penitent::KnockUpStart(const StateInfo& _Info)
{
    if ("LadderClimb" == _Info.PrevState)
    {
        State_.ChangeState("LadderClimb");
        return;
    }

    FallTime_ = 0.f;

    MetaRenderer_->ChangeMetaAnimation("penitent_throwback_anim");
    MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};

    if (0 > KnockBackXDir_)
    {
        GetTransform().PixLocalPositiveX();
    }

    else
    {
        GetTransform().PixLocalNegativeX();
    }

    CurStage_->SetShake(true);
}

void Penitent::KnockUpUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == RightObstacleCheck() || true == LeftObstacleCheck())
    {
        return;
    }

    if (0.2f <= _Info.StateTime && 1 <= MetaRenderer_->GetColorData().PlusColor.r)
    {
        MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
    }

    GetTransform().SetWorldMove(float4{KnockBackXDir_, 0} * 150.f * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::KnockUpEnd(const StateInfo& _Info) {}


void Penitent::LandingStart(const StateInfo& _Info)
{
    if ("VerticalAttack" == _Info.PrevState)
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_verticalattack_landing");

        float4 PlayerPos = GetTransform().GetWorldPosition();

        AttackEffect_->GetTransform().SetWorldPosition({PlayerPos.x, PlayerPos.y, PlayerEffectZ});

        AttackEffect_->Renderer_->On();
        AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_verticalattack_landing_effects_anim");
        AttackEffect_->Renderer_->CurAnimationReset();
        return;
    }

    if (0.9f <= FallTime_)
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_hardlanding_rocks_anim");
    }

    else
    {
        MetaRenderer_->ChangeMetaAnimation("penintent_standing_up");

        MoveEffect_->Renderer_->On();
        MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
        MoveEffect_->Renderer_->ChangeMetaAnimation("penitent-landing-dust-anim");

        //모션 캔슬
        if (GameEngineInput::GetInst()->IsPressKey("PenitentRight")
            || GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
        {
            ChangeState("Move");
        }

        else if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack"))
        {
            ChangeState("Attack");
        }

        else if (GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
        {
            ChangeState("Crouch");
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

    Gravity_->SetActive(!IsGround_);
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

    MoveEffect_->Renderer_->On();

    if (1 == RealXDir_)
    {
        MoveEffect_->GetTransform().PixLocalPositiveX();
    }

    else if (-1 == RealXDir_)
    {
        MoveEffect_->GetTransform().PixLocalNegativeX();
    }

    MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{RealXDir_ * 50.f, 0});
    MoveEffect_->Renderer_->ChangeMetaAnimation("penitent_start_dodge_dust_anim");

    SlideSpectrum_->SetIsMetaDraw(true);
}

void Penitent::SlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack"))
    {
        State_.ChangeState("SlideAttack");
        return;
    }

    if (true == RightObstacleCheck() || true == LeftObstacleCheck())
    {
        return;
    }

    SlideForce_ -= _DeltaTime * 350.f;
    GetTransform().SetWorldMove(Dir_ * SlideForce_ * _DeltaTime);

    Gravity_->SetActive(!IsGround_);

    //내리막길
    if (false == IsGround_)
    {
        if (false == FallCollisionCheck())
        {
            MoveEffect_->Renderer_->Off();

            JumpForce_ = 10.f;
            State_.ChangeState("Fall");
        }
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

    //누적된 추락 시간 초기화
    FallTime_ = 0.f;
}

void Penitent::DangleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsDownKey("PenitentUp"))
    {
        IsDangle_     = true;
        IsClimbLedge_ = true;

        MetaRenderer_->ChangeMetaAnimation("penitent_climbledge_reviewed");

        GetTransform().SetWorldMove({RealXDir_ * 20.f, 100.f});
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
        float4 EndPos   = GetTransform().GetWorldPosition() + float4{RealXDir_ * 50.f, 50.f};

        GetTransform().SetWorldPosition(float4::LerpLimit(StartPos, EndPos, _DeltaTime * 1.5f));
    }
}

void Penitent::DangleEnd(const StateInfo& _Info) { IsClimbLedge_ = false; }

void Penitent::LadderClimbStart(const StateInfo& _Info)
{
    //한 프레임 false 상태로 만들고 다음 상태일 때 체크
    IsGround_ = false;
    Gravity_->SetActive(false);

    MetaRenderer_->ChangeMetaAnimation("penintent_ladder_climb_loop_anim");
}

void Penitent::LadderClimbUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (false == IsLadder_)
    {
        if (GameEngineInput::GetInst()->IsPressKey("PenitentUp"))
        {
            CilmbY_ = 30.f;

            if (true == MetaRenderer_->IsCurAnimationPause())
            {
                MetaRenderer_->CurAnimationPauseSwitch();
            }

            MetaRenderer_->ChangeMetaAnimation("penintent_ladder_climb_loop_anim");
            GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
        }

        if (GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
        {
            CilmbY_ = -50;

            if (true == MetaRenderer_->IsCurAnimationPause())
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

        if (GameEngineInput::GetInst()->IsDownKey("PenitentJump")
                && GameEngineInput::GetInst()->IsPressKey("PenitentLeft")
            || GameEngineInput::GetInst()->IsDownKey("PenitentJump")
                   && GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
        {
            State_.ChangeState("Jump");
            return;
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

void Penitent::LadderClimbEnd(const StateInfo& _Info) 
{
    IsLadder_ = false; 
}


void Penitent::AttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_three_hits_attack_combo_no_slashes");
    AttackCollider_->GetTransform().SetWorldMove({RealXDir_ * 80.f, 50.f});

    if (1 == RealXDir_)
    {
        AttackEffect_->GetTransform().PixLocalPositiveX();
    }

    else if (-1 == RealXDir_)
    {
        AttackEffect_->GetTransform().PixLocalNegativeX();
    }
}

void Penitent::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsDownKey("PenitentAttack"))
    {
        ++AttackStack_;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentUp"))
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_upward_attack_clamped_anim");

        AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
        AttackCollider_->GetTransform().SetWorldMove({0.f, 150.f});
    }

    Gravity_->SetActive(!IsGround_);
}

void Penitent::AttackEnd(const StateInfo& _Info)
{
    AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
    AttackCollider_->Off();

    AttackStack_ = 0;
}


void Penitent::SlideAttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_dodge_attack_LVL3");
    AttackCollider_->GetTransform().SetWorldMove({RealXDir_ * 80.f, 50.f});
    AttackCollider_->ChangeOrder(COLLISIONORDER::PlayerSkill);
    BodyCollider_->Off();

    SlideAttackSpectrum_->SetIsMetaDraw(true);
}

void Penitent::SlideAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == RightObstacleCheck() || true == LeftObstacleCheck())
    {
        return;
    }

    GetTransform().SetWorldMove({RealXDir_ * 350.f * _DeltaTime, 0.f});
    Gravity_->SetActive(!IsGround_);
}

void Penitent::SlideAttackEnd(const StateInfo& _Info)
{
    AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
    AttackCollider_->Off();
    AttackCollider_->ChangeOrder(COLLISIONORDER::PlayerAttack);
    BodyCollider_->On();
}


void Penitent::VerticalAttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_verticalattack_start_anim");
    FallTime_ = 0;

    ReadySkill_ = false;
    Gravity_->SetActive(false);

    AttackCollider_->On();
    AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
    BodyCollider_->Off();
}

void Penitent::VerticalAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (false == ReadySkill_)
    {
        return;
    }

    JumpForce_.y -= _DeltaTime * 150.f;

    Dir_ = GetTransform().GetUpVector() * 10.f;

    if (true == IsGround_)
    {
        ChangeState("Landing");
        return;
    }

    GetTransform().SetWorldMove(Dir_ * JumpForce_ * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::VerticalAttackEnd(const StateInfo& _Info) { AttackCollider_->Off(); }


void Penitent::PrayAttackStart(const StateInfo& _Info)
{
    BodyCollider_->Off();
    MetaRenderer_->ChangeMetaAnimation("penitent_aura_anim");
}

void Penitent::PrayAttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::PrayAttackEnd(const StateInfo& _Info)
{
    BodyCollider_->On();

    //보스 킬 이벤트
    if (MetaRenderer_->GetColorData().MulColor.CompareInt4D(float4::ZERO))
    {
        return;
    }

    MetaRenderer_->GetColorData().MulColor = float4{1.0f, 1.0f, 1.0f, 1.0f};
}


void Penitent::RangeAttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_rangeAttack_shoot_anim");
}

void Penitent::RangeAttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::RangeAttackEnd(const StateInfo& _Info) { FallTime_ = 0.f; }


void Penitent::JumpRangeAttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_rangeAttack_symbol_midair_anim");

    Gravity_->SetActive(false);
}

void Penitent::JumpRangeAttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::JumpRangeAttackEnd(const StateInfo& _Info) {}


void Penitent::ExecutionStart(const StateInfo& _Info)
{
    BodyCollider_->Off();

    switch (ExecutionType_)
    {
        case EXECUTIONTYPE::None:
            break;
        case EXECUTIONTYPE::Crosscrawler:
            MetaRenderer_->ChangeMetaAnimation("crosscrawler_execution");
            break;
        case EXECUTIONTYPE::ShieldMaiden:
            MetaRenderer_->ChangeMetaAnimation("shieldMaiden_execution");
            break;
        default:
            break;
    }
}

void Penitent::ExecutionUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::ExecutionEnd(const StateInfo& _Info)
{
    switch (ExecutionType_)
    {
        case EXECUTIONTYPE::None:
            break;
        case EXECUTIONTYPE::Crosscrawler:
            if (0 > RealXDir_)
            {
                GetTransform().SetWorldMove({30.f, 0});
            }

            else
            {
                GetTransform().SetWorldMove({-30.f, 0});
            }
            break;

        case EXECUTIONTYPE::ShieldMaiden:
            if (0 > RealXDir_)
            {
                GetTransform().SetWorldMove({70.f, 0});
            }

            else
            {
                GetTransform().SetWorldMove({-70.f, 0});
            }
            break;
        default:
            break;
    }

    BodyCollider_->On();
}


void Penitent::ParryingStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("penitent_parry_failed"); }

void Penitent::ParryingUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == IsParrySuccess_)
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_parry_success_animv3");
        ParryOn_ = false;
    }
}

void Penitent::ParryingEnd(const StateInfo& _Info) { IsParrySuccess_ = false; }


void Penitent::ParryingAttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_parry_counter_v2_anim");
}

void Penitent::ParryingAttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::ParryingAttackEnd(const StateInfo& _Info) {}


void Penitent::RecoveryStart(const StateInfo& _Info)
{
    int Size = static_cast<int>(Flasks_.size() - 1);

    for (int i = Size; i >= 0; --i)
    {
        if (true == Flasks_[i])
        {
            PlusHP(30);

            Flasks_[i] = false;
            PlayerUI_->UseFlask(i);

            MetaRenderer_->ChangeMetaAnimation("penitent_healthpotion_consuming_anim");

            AttackEffect_->Renderer_->On();

            if (1 == RealXDir_)
            {
                AttackEffect_->GetTransform().PixLocalPositiveX();
            }

            else if (-1 == RealXDir_)
            {
                AttackEffect_->GetTransform().PixLocalNegativeX();
            }

            AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_healthpotion_consuming_aura_anim");
            AttackEffect_->GetTransform().SetWorldPosition(
                {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, PlayerEffectZ});
            return;
        }
    }

    State_.ChangeState("Idle");
}

void Penitent::RecoveryUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::RecoveryEnd(const StateInfo& _Info) {}


void Penitent::ReturnToPortStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("RegresoAPuerto-Prayer");

    // AttackEffect_->Renderer_->On();
    // AttackEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
    // AttackEffect_->Renderer_->ChangeMetaAnimation("guardian_lady_protect_and_vanish");
}

void Penitent::ReturnToPortUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::ReturnToPortEnd(const StateInfo& _Info) {}


void Penitent::RespawnStart(const StateInfo& _Info)
{
    //일단 무조건 오른쪽을 본다.
    GetTransform().PixLocalPositiveX();

    if ("" != LastSaveLevel_)
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_respawning_anim");

        AttackEffect_->Renderer_->On();
        AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_respawning_anim_querubs");
    }

    BodyCollider_->Off();
}

void Penitent::RespawnUpdate(float _DeltaTime, const StateInfo& _Info)
{
    AttackEffect_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, PlayerEffectZ});

    Gravity_->SetActive(!IsGround_);
}

void Penitent::RespawnEnd(const StateInfo& _Info) { BodyCollider_->Off(); }


void Penitent::PrayStart(const StateInfo& _Info) {}

void Penitent::PrayUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::PrayEnd(const StateInfo& _Info) {}


void Penitent::RestPrayStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_priedieu_kneeling_anim");
}

void Penitent::RestPrayUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::RestPrayEnd(const StateInfo& _Info)
{
    SetHP(100);
    SetMP(100);

    int Size = static_cast<int>(Flasks_.size() - 1);

    for (int i = Size; i >= 0; --i)
    {
        Flasks_[i] = true;
        PlayerUI_->FillFlask(i);
    }
}


void Penitent::DoorEntranceStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_crossing_opendoor_out_anim");
}

void Penitent::DoorEntranceUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::DoorEntranceEnd(const StateInfo& _Info)
{
    GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, BeforeParallax5Z});

    GEngine::ChangeLevel(OutDoorLevel_);
}


void Penitent::DeathStart(const StateInfo& _Info)
{
    IsPlayerDeath_ = true;

    MetaRenderer_->ChangeMetaAnimation("death_anim_blood");

    if (true == LastSaveLevel_.empty())
    {
        PlayerUI_->SetRespawnLevelName("Stage01");
    }

    else
    {
        PlayerUI_->SetRespawnLevelName(LastSaveLevel_);
    }

    MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
}

void Penitent::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::DeathEnd(const StateInfo& _Info) { SetHP(100.f); }
