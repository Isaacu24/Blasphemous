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
    IsFreezeEnd_ = false;

    if ("DoorEntrance" == _Info.PrevState)
    {
        IsDoorExit_ = true;
    }
}

void Penitent::FreezeUpdate(float _DeltaTime, const StateInfo& _Info) { Gravity_->SetActive(!IsGround_); }

void Penitent::FreezeEnd(const StateInfo& _Info) { IsDoorExit_ = false; }


void Penitent::IdleStart(const StateInfo& _Info)
{
    FallTime_ = 0.1f;
    MetaRenderer_->ChangeMetaAnimation("penintent_idle_anim");
}

void Penitent::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    //연속 데미지 막기
    if (0.5f < _Info.StateTime && true == IsKnockBackFall_)
    {
        IsKnockBackFall_ = false;
    }

    if (30000 < ThumbLX_ || true == GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
    {
        State_.ChangeState("Move");
    }

    else if (-30000 > ThumbLX_ || true == GameEngineInput::GetInst()->IsPressKey("PenitentLeft"))
    {
        State_.ChangeState("Move");
    }

    //사다리 내려가기 or 앉기
    else if (true == GameEngineInput::GetInst()->IsPressKey("PenitentDown") || -30000 > ThumbLY_)
    {
        State_.ChangeState("Crouch");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentSlide")
             || 254 < GameEngineInput::GetInst()->GetLeftTrigger())
    {
        State_.ChangeState("Slide");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentJump")
             || GameEngineInput::GetInst()->IsDownButton("PenitentA"))
    {
        State_.ChangeState("Jump");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentAttack")
             || GameEngineInput::GetInst()->IsDownButton("PenitentB") && false == IsReturnToPort_)
    {
        State_.ChangeState("Attack");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentParry")
             || true == GameEngineInput::GetInst()->IsDownButton("PenitentRightShoulder"))
    {
        State_.ChangeState("Parrying");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentRecovery")
             || true == GameEngineInput::GetInst()->IsDownButton("PenitentLeftShoulder"))
    {
        State_.ChangeState("Recovery");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentTelport") && true == IsReturnToPort_
             || (true == GameEngineInput::GetInst()->IsDownButton("PenitentB") && true == IsReturnToPort_))
    {
        State_.ChangeState("ReturnToPort");
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("PenitentPary") && true == IsGround_
             || 254 < GameEngineInput::GetInst()->GetRightTrigger() && true == IsGround_)
    {
        State_.ChangeState("PrayAttack");
    }

    else if (true == GameEngineInput::GetInst()->IsPressKey("PenitentL")
             || true == GameEngineInput::GetInst()->IsDownButton("PenitentX"))
    {
        State_.ChangeState("RangeAttack");
    }

    else if (true == GameEngineInput::GetInst()->IsPressKey("PenitentChrage")
             || 0.1f < GameEngineInput::GetInst()->GetButtonTime("PenitentB"))
    {
        State_.ChangeState("ChargeAttack");
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
    //연속 데미지 막기
    if (0.5f < _Info.StateTime && true == IsKnockBackFall_)
    {
        IsKnockBackFall_ = false;
    }

    if (true == GameEngineInput::GetInst()->IsPressKey("PenitentRight") || 30000 < ThumbLX_)
    {
        GetTransform().PixLocalPositiveX();
        MoveDir_ = float4::RIGHT;

        RealDirX_ = 1;

        if (false == RightObstacleCheck())
        {
            RunTime_ += _DeltaTime;

            GetTransform().SetWorldMove(MoveDir_ * Speed_ * _DeltaTime);
        }
    }

    else if (true == GameEngineInput::GetInst()->IsUpKey("PenitentRight")
             || MoveDir_.CompareInt2D(float4::RIGHT) && 30000 > ThumbLX_ && ThumbLX_ > 0)
    {
        GameEngineInput::GetInst()->SetThumbLX(0);

        if (1.f <= RunTime_)
        {
            MetaRenderer_->ChangeMetaAnimation("penintent_stop_run_anim");

            MoveEffect_->Renderer_->On();
            MoveEffect_->GetTransform().PixLocalPositiveX();
            MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()
                                                         + float4{RealDirX_ * 50.f, 0});
            MoveEffect_->Renderer_->ChangeMetaAnimation("penitent-stop-running-dust");

            SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_RUNSTOP_MARBLE.wav");
        }

        else
        {
            ChangeState("Idle");
        }

        return;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft") || -30000 > ThumbLX_)
    {
        GetTransform().PixLocalNegativeX();
        MoveDir_ = float4::LEFT;

        RealDirX_ = -1;

        if (false == LeftObstacleCheck())
        {
            RunTime_ += _DeltaTime;
            GetTransform().SetWorldMove(MoveDir_ * Speed_ * _DeltaTime);
        }
    }

    else if (GameEngineInput::GetInst()->IsUpKey("PenitentLeft")
             || MoveDir_.CompareInt2D(float4::LEFT) && -30000 < ThumbLX_ && ThumbLX_ > 0)
    {
        GameEngineInput::GetInst()->SetThumbLX(0);

        if (1.f <= RunTime_)
        {
            MetaRenderer_->ChangeMetaAnimation("penintent_stop_run_anim");

            MoveEffect_->Renderer_->On();
            MoveEffect_->GetTransform().PixLocalNegativeX();
            MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()
                                                         + float4{RealDirX_ * 50.f, 0});
            MoveEffect_->Renderer_->ChangeMetaAnimation("penitent-stop-running-dust");

            SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_RUNSTOP_MARBLE.wav");
        }

        else
        {
            ChangeState("Idle");
        }
        return;
    }

    if (GameEngineInput::GetInst()->IsDownKey("PenitentJump") || GameEngineInput::GetInst()->IsDownButton("PenitentA"))
    {
        State_.ChangeState("Jump");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentDown") || -30000 > ThumbLY_)
    {
        State_.ChangeState("Crouch");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentSlide")
             || 254 < GameEngineInput::GetInst()->GetLeftTrigger())
    {
        State_.ChangeState("Slide");
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack")
             || GameEngineInput::GetInst()->IsDownButton("PenitentB"))
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

    SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_JUMP.wav");

    MoveEffect_->Renderer_->On();
    MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
    MoveEffect_->Renderer_->ChangeMetaAnimation("penitent-jumping-dust-anim");

    LastJumpPos_ = GetTransform().GetWorldPosition();
}

void Penitent::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpForce_.y -= _DeltaTime * 100.f;

    MoveDir_ = float4::UP * 10.f;

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight") || 30000 < ThumbLX_)
    {
        GetTransform().PixLocalPositiveX();
        RealDirX_ = 1;

        MetaRenderer_->ChangeMetaAnimation("penitent_jum_forward_anim");

        if (false == RightObstacleCheck())
        {
            MoveDir_ += float4::RIGHT * 3.f;
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft") || -30000 > ThumbLX_)
    {
        GetTransform().PixLocalNegativeX();
        RealDirX_ = -1;

        MetaRenderer_->ChangeMetaAnimation("penitent_jum_forward_anim");

        if (false == LeftObstacleCheck())
        {
            MoveDir_ += float4::LEFT * 3.f;
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack")
            && GameEngineInput::GetInst()->IsPressKey("PenitentDown")
        || -30000 > ThumbLY_ && GameEngineInput::GetInst()->IsDownButton("PenitentB"))
    {
        ChangeState("VerticalAttack");
        return;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack")
        || GameEngineInput::GetInst()->IsDownButton("PenitentB"))
    {
        ChangeState("JumpAttack");
        return;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentL") || GameEngineInput::GetInst()->IsDownButton("PenitentX"))
    {
        ChangeState("JumpRangeAttack");
        return;
    }

    GetTransform().SetWorldMove(MoveDir_ * JumpForce_ * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::JumpEnd(const StateInfo& _Info) {}

void Penitent::FallStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_falling_loop_anim");

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight")
        || GameEngineInput::GetInst()->IsPressKey("PenitentLeft") || 30000 < ThumbLX_ || -30000 > ThumbLX_)
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_jum_forward_fall_anim");
    }
}

void Penitent::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpForce_.y -= _DeltaTime * 100.f;
    FallTime_ += _DeltaTime;

    MoveDir_ = GetTransform().GetUpVector() * 10.f;

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight") || 30000 < ThumbLX_)
    {
        GetTransform().PixLocalPositiveX();
        RealDirX_ = 1;

        if (false == RightObstacleCheck())
        {
            MoveDir_ += -(GetTransform().GetLeftVector() * 3.f);
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft") || -30000 > ThumbLX_)
    {
        GetTransform().PixLocalNegativeX();
        RealDirX_ = -1;

        if (false == LeftObstacleCheck())
        {
            MoveDir_ += -(GetTransform().GetLeftVector() * 3.f);
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack")
        || GameEngineInput::GetInst()->IsDownButton("PenitentB"))
    {
        ChangeState("JumpAttack");
        return;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentDown") /* || -30000 > ThumbLY_*/)
    {
        JumpForce_.y -= _DeltaTime * 50.f;
        FallTime_ += _DeltaTime / 2;
    }

    if (true == IsGround_)
    {
        ChangeState("Landing");
        return;
    }

    GetTransform().SetWorldMove(MoveDir_ * JumpForce_ * _DeltaTime);
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

    if (GameEngineInput::GetInst()->IsPressKey("PenitentUp") || 30000 < ThumbLY_)
    {
        AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_upward_attack_slash_lvl1");
    }

    MetaRenderer_->ChangeMetaAnimation("penitent_jumping_attack_noslashes");

    if (0 < RealDirX_)  //오른쪽
    {
        AttackEffect_->GetTransform().PixLocalPositiveX();
        AttackCollider_->GetTransform().SetWorldMove({RealDirX_ * 80.f, 50.f});
    }

    else if (0 > RealDirX_)  //왼쪽
    {
        AttackEffect_->GetTransform().PixLocalNegativeX();
        AttackCollider_->GetTransform().SetWorldMove({RealDirX_ * 80.f, 50.f});
    }
}

void Penitent::JumpAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    JumpForce_.y -= _DeltaTime * 80.f;

    AttackEffect_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, PlayerEffectZ});

    MoveDir_ = GetTransform().GetUpVector() * 10.f;

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight") || 30000 < ThumbLX_)
    {
        GetTransform().PixLocalPositiveX();
        RealDirX_ = 1;

        if (false == RightObstacleCheck())
        {
            MoveDir_ += -(GetTransform().GetLeftVector() * 3.f);
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft") || -30000 > ThumbLX_)
    {
        GetTransform().PixLocalNegativeX();
        RealDirX_ = -1;

        if (false == LeftObstacleCheck())
        {
            MoveDir_ += -(GetTransform().GetLeftVector() * 3.f);
        }
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentUp") || 30000 < ThumbLY_)
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

    GetTransform().SetWorldMove(MoveDir_ * JumpForce_ * _DeltaTime);
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
    SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_HIT_DAMAGE_1.wav");

    if ("LadderClimb" == _Info.PrevState)
    {
        State_.ChangeState("LadderClimb");
        return;
    }

    MetaRenderer_->ChangeMetaAnimation("Penitent_pushback_grounded");
    MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};

    HitEffect_->Renderer_->On();
    HitEffect_->Renderer_->ChangeMetaAnimation("pushback_sparks_anim");

    if (0 < RealDirX_)
    {
        HitEffect_->GetTransform().PixLocalPositiveX();
        MoveEffect_->GetTransform().PixLocalPositiveX();
        AttackEffect_->GetTransform().PixLocalPositiveX();
        GetTransform().PixLocalPositiveX();
    }

    else
    {
        HitEffect_->GetTransform().PixLocalNegativeX();
        MoveEffect_->GetTransform().PixLocalNegativeX();
        AttackEffect_->GetTransform().PixLocalNegativeX();
        GetTransform().PixLocalNegativeX();
    }

    CurStage_->SetForceX(0.f);
    CurStage_->SetForceY(5.f);
    CurStage_->SetShake(true);

    FallTime_ = 0.f;
}

void Penitent::KnockBackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (0.2f <= _Info.StateTime && 1 <= MetaRenderer_->GetColorData().PlusColor.r)
    {
        MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
    }

    if (0.f < MoveDir_.x && true == RightObstacleCheck() || 0.f > MoveDir_.x && true == LeftObstacleCheck())
    {
        return;
    }

    if (false == IsGround_)
    {
        JumpForce_ = 10.f;
        ChangeState("Fall");
        IsKnockBackFall_ = true;
        return;
    }

    HitEffect_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 75.f, PlayerEffectZ});

    GetTransform().SetWorldMove(float4{MoveDir_.x, 0} * 150.f * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::KnockBackEnd(const StateInfo& _Info)
{
    MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};

    float4 ScaleX = GetTransform().GetLocalScale();
}


void Penitent::KnockUpStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_HIT_DAMAGE_2.wav");

    if ("LadderClimb" == _Info.PrevState)
    {
        State_.ChangeState("LadderClimb");
        return;
    }

    FallTime_ = 0.f;

    IsKnockUp_ = true;
    MetaRenderer_->ChangeMetaAnimation("penitent_throwback_anim");
    MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};

    if (0 < RealDirX_)
    {
        HitEffect_->GetTransform().PixLocalPositiveX();
        MoveEffect_->GetTransform().PixLocalPositiveX();
        AttackEffect_->GetTransform().PixLocalPositiveX();
        GetTransform().PixLocalPositiveX();
    }

    else
    {
        HitEffect_->GetTransform().PixLocalNegativeX();
        MoveEffect_->GetTransform().PixLocalNegativeX();
        AttackEffect_->GetTransform().PixLocalNegativeX();
        GetTransform().PixLocalNegativeX();
    }

    CurStage_->SetShake(true);
}

void Penitent::KnockUpUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (0.2f <= _Info.StateTime && 1 <= MetaRenderer_->GetColorData().PlusColor.r)
    {
        MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
    }

    if (0.f < MoveDir_.x && true == RightObstacleCheck() || 0.f > MoveDir_.x && true == LeftObstacleCheck())
    {
        return;
    }

    if (true == IsKnockUp_)
    {
        GetTransform().SetWorldMove(float4{MoveDir_.x, 0} * 150.f * _DeltaTime);
    }

    Gravity_->SetActive(!IsGround_);
}

void Penitent::KnockUpEnd(const StateInfo& _Info)
{
    MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
}


void Penitent::LandingStart(const StateInfo& _Info)
{
    if (0.9f <= FallTime_)
    {
        //카메라 쉐이킹
        CurStage_->SetForceX(0.f);
        CurStage_->SetForceY(15.f);
        CurStage_->SetShake(true);

        BodyCollider_->Off();

        AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
        AttackCollider_->On();

        MetaRenderer_->ChangeMetaAnimation("penitent_hardlanding_rocks_anim");

        SoundPlayer_ = GameEngineSound::SoundPlayControl("HARD_LANDING.wav");
    }

    else
    {
        SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_JUMP_FALL_STONE.wav");

        MetaRenderer_->ChangeMetaAnimation("penintent_standing_up");

        MoveEffect_->Renderer_->On();
        MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
        MoveEffect_->Renderer_->ChangeMetaAnimation("penitent-landing-dust-anim");

        //모션 캔슬
        if (GameEngineInput::GetInst()->IsPressKey("PenitentRight")
            || GameEngineInput::GetInst()->IsPressKey("PenitentLeft") || 30000 < ThumbLX_ || -30000 > ThumbLX_)
        {
            ChangeState("Move");

            SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_LANDING_RUNNING.wav");
        }

        else if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack")
                 || GameEngineInput::GetInst()->IsDownButton("PenitentB"))
        {
            ChangeState("Attack");
        }

        else if (GameEngineInput::GetInst()->IsPressKey("PenitentDown") || -30000 > ThumbLY_)
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

    if ("CrouchAttack" == _Info.PrevState)
    {
        MetaRenderer_->CurAnimationSetStartPivotFrame(6);
    }

    BodyCollider_->GetTransform().SetWorldScale({ColScale_.y, ColScale_.x});
    BodyCollider_->GetTransform().SetWorldMove({0, -50});
}

void Penitent::CrouchUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsFreeKey("PenitentDown"))
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_crouch_up_anim");
    }

    if (GameEngineInput::GetInst()->IsUpKey("PenitentDown") || 0 < ThumbLY_)
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_crouch_up_anim");
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentRight") || 30000 < ThumbLX_)
    {
        RealDirX_ = 1;
        GetTransform().PixLocalPositiveX();
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentLeft") || -30000 > ThumbLX_)
    {
        RealDirX_ = -1;
        GetTransform().PixLocalNegativeX();
    }

    if (GameEngineInput::GetInst()->IsDownKey("PenitentAttack"))
    {
        ChangeState("CrouchAttack");
    }

    if (false == IsGround_)
    {
        ChangeState("Fall");
    }

    Gravity_->SetActive(!IsGround_);
}

void Penitent::CrouchEnd(const StateInfo& _Info)
{
    BodyCollider_->GetTransform().SetWorldScale(ColScale_);
    BodyCollider_->GetTransform().SetWorldMove({0, 50});
}


void Penitent::CrouchAttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_crouchslash_noslashes_anim");
    AttackEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());

    if (1 == RealDirX_)
    {
        AttackEffect_->GetTransform().PixLocalPositiveX();
    }

    else if (-1 == RealDirX_)
    {
        AttackEffect_->GetTransform().PixLocalNegativeX();
    }
}

void Penitent::CrouchAttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::CrouchAttackEnd(const StateInfo& _Info) {}


void Penitent::SlideStart(const StateInfo& _Info)
{
    SlideForce_ = 500.f;
    MetaRenderer_->ChangeMetaAnimation("penitent_dodge_anim");
    MoveEffect_->Renderer_->On();

    SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_DASH.wav");

    if (1 == RealDirX_)
    {
        MoveDir_ = float4::RIGHT;
        MoveEffect_->GetTransform().PixLocalPositiveX();
    }

    else if (-1 == RealDirX_)
    {
        MoveDir_ = float4::LEFT;
        MoveEffect_->GetTransform().PixLocalNegativeX();
    }

    BodyCollider_->GetTransform().SetWorldScale({ColScale_.y, ColScale_.x});
    BodyCollider_->GetTransform().SetWorldMove({0, -50});

    MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{RealDirX_ * 50.f, 0});
    MoveEffect_->Renderer_->ChangeMetaAnimation("penitent_start_dodge_dust_anim");

    SlideSpectrum_->SetIsMetaDraw(true);
}

void Penitent::SlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsPressKey("PenitentAttack")
        || GameEngineInput::GetInst()->IsDownButton("PenitentB"))
    {
        State_.ChangeState("SlideAttack");
        return;
    }

    if (true == RightObstacleCheck() || true == LeftObstacleCheck())
    {
        return;
    }

    SlideForce_ -= _DeltaTime * 350.f;
    GetTransform().SetWorldMove(float4{RealDirX_, 0} * SlideForce_ * _DeltaTime);

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
    SoundPlayer_ = GameEngineSound::SoundPlayControl("Penitent_EdgeClimb.wav");

    Gravity_->SetActive(false);
    MetaRenderer_->ChangeMetaAnimation("penitent_hangonledge_anim");

    //누적된 추락 시간 초기화
    FallTime_ = 0.f;
}

void Penitent::DangleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsDownKey("PenitentUp") || 30000 < ThumbLY_ && false == IsClimbLedge_)
    {
        IsDangle_     = true;
        IsClimbLedge_ = true;

        MetaRenderer_->ChangeMetaAnimation("penitent_climbledge_reviewed");

        GetTransform().SetWorldMove({RealDirX_ * 20.f, 100.f});
    }

    else if (GameEngineInput::GetInst()->IsPressKey("PenitentDown") || -30000 > ThumbLY_)
    {
        State_.ChangeState("Fall");
        IsDangle_  = true;
        JumpForce_ = 10.f;
    }

    if (true == IsClimbLedge_)
    {
        float4 StartPos = GetTransform().GetWorldPosition();
        float4 EndPos   = GetTransform().GetWorldPosition() + float4{RealDirX_ * 50.f, 50.f};

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

        if (GameEngineInput::GetInst()->IsPressKey("PenitentDown") || -30000 > ThumbLY_)
        {
            CilmbY_ = -50;

            if (true == MetaRenderer_->IsCurAnimationPause())
            {
                MetaRenderer_->CurAnimationPauseSwitch();
            }

            MetaRenderer_->ChangeMetaAnimation("penintent_ladder_climb_loop_anim");
            GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
        }

        if (GameEngineInput::GetInst()->IsPressKey("PenitentDown")
                && GameEngineInput::GetInst()->IsPressKey("PenitentSlide")
            || -30000 > ThumbLY_)
        {
            ChangeState("LadderSlide");
        }

        if (GameEngineInput::GetInst()->IsUpKey("PenitentUp") || GameEngineInput::GetInst()->IsUpKey("PenitentDown")
            || 5000.f > GameEngineInput::GetInst()->GetMagnitudeLY() && PacketNumber_)
        {
            //애니메이션 멈춤
            if (false == MetaRenderer_->IsCurAnimationPause())
            {
                MetaRenderer_->CurAnimationPauseSwitch();
                SoundPlayer_.Stop();
            }
        }

        if (GameEngineInput::GetInst()->IsDownKey("PenitentJump")
                && GameEngineInput::GetInst()->IsPressKey("PenitentLeft")
            || GameEngineInput::GetInst()->IsDownKey("PenitentJump")
                   && GameEngineInput::GetInst()->IsPressKey("PenitentRight"))
        {
            State_.ChangeState("Jump");
            return;
        }

        if (GameEngineInput::GetInst()->IsDownButton("PenitentA") && 30000 < ThumbLX_
            || GameEngineInput::GetInst()->IsDownButton("PenitentA") && -30000 > ThumbLX_)
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

void Penitent::LadderClimbEnd(const StateInfo& _Info) { IsLadder_ = false; }


void Penitent::LadderSlideStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_ladder_sliding");

    Speed_ *= 1.5f;
}

void Penitent::LadderSlideUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsUpKey("PenitentSlide"))
    {
        ChangeState("LadderClimb");
    }

    GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);

    if (true == IsGround_)
    {
        if (0 > CilmbY_)  //아래 사다리
        {
            IsLadder_ = true;
            Gravity_->SetActive(true);
            MetaRenderer_->ChangeMetaAnimation("penintent_ladder_up_from_ground");
        }
    }
}

void Penitent::LadderSlideEnd(const StateInfo& _Info)
{
    IsLadder_ = false;
    Speed_    = 250.f;
}


void Penitent::AttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_three_hits_attack_combo_no_slashes");

    AttackCollider_->GetTransform().SetLocalPosition({0, 0, 0});
    AttackCollider_->GetTransform().SetWorldMove({RealDirX_ * 80.f, 50.f});

    if (1 == RealDirX_)
    {
        AttackEffect_->GetTransform().PixLocalPositiveX();
    }

    else if (-1 == RealDirX_)
    {
        AttackEffect_->GetTransform().PixLocalNegativeX();
    }
}

void Penitent::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (GameEngineInput::GetInst()->IsDownKey("PenitentAttack")
        || GameEngineInput::GetInst()->IsDownButton("PenitentB"))
    {
        ++AttackStack_;
    }

    if (GameEngineInput::GetInst()->IsPressKey("PenitentUp") || 30000 < ThumbLY_)
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

    AttackCollider_->GetTransform().SetLocalPosition({0, 0, 0});
    AttackCollider_->GetTransform().SetWorldMove({RealDirX_ * 80.f, 50.f});
    // AttackCollider_->ChangeOrder(COLLISIONORDER::PlayerSkill);

    SlideAttackSpectrum_->SetIsMetaDraw(true);
}

void Penitent::SlideAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == RightObstacleCheck() || true == LeftObstacleCheck())
    {
        return;
    }

    //내리막길
    if (false == IsGround_)
    {
        if (false == FallCollisionCheck())
        {
            MoveEffect_->Renderer_->Off();

            JumpForce_ = 10.f;
            State_.ChangeState("Fall");
            return;
        }
    }

    GetTransform().SetWorldMove({RealDirX_ * 350.f * _DeltaTime, 0.f});
    Gravity_->SetActive(!IsGround_);
}

void Penitent::SlideAttackEnd(const StateInfo& _Info)
{
    AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
    AttackCollider_->Off();
    // AttackCollider_->ChangeOrder(COLLISIONORDER::PlayerAttack);
}


void Penitent::VerticalAttackStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("VERTICAL_ATTACK_START.wav");

    MetaRenderer_->ChangeMetaAnimation("penitent_verticalattack_start_anim");
    FallTime_ = 0;

    ReadySkill_ = false;
    Gravity_->SetActive(false);
}

void Penitent::VerticalAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (false == ReadySkill_)
    {
        return;
    }

    JumpForce_.y -= _DeltaTime * 150.f;

    MoveDir_ = GetTransform().GetUpVector() * 10.f;

    if (true == IsGround_)
    {
        ChangeState("VerticalAttackLanding");
        return;
    }

    GetTransform().SetWorldMove(MoveDir_ * JumpForce_ * _DeltaTime);
    Gravity_->SetActive(!IsGround_);
}

void Penitent::VerticalAttackEnd(const StateInfo& _Info) {}


void Penitent::VerticalAttackLandingStart(const StateInfo& _Info)
{
    AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
    AttackCollider_->On();

    MetaRenderer_->ChangeMetaAnimation("penitent_verticalattack_landing");

    float4 PlayerPos = GetTransform().GetWorldPosition();

    AttackEffect_->GetTransform().SetWorldPosition({PlayerPos.x, PlayerPos.y, PlayerEffectZ});

    AttackEffect_->Renderer_->On();
    AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_verticalattack_landing_effects_anim");
}

void Penitent::VerticalAttackLandingUpdate(float _DeltaTime, const StateInfo& _Info)
{
    Gravity_->SetActive(!IsGround_);
}

void Penitent::VerticalAttackLandingEnd(const StateInfo& _Info)
{
    AttackCollider_->GetTransform().SetLocalPosition({0.f, 0.f});
    AttackCollider_->Off();
}


void Penitent::PrayAttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_aura_anim");
    SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_ACTIVATE_PRAYER.wav");
}

void Penitent::PrayAttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::PrayAttackEnd(const StateInfo& _Info)
{
    //보스 킬 이벤트
    if (MetaRenderer_->GetColorData().MulColor.CompareInt4D(float4::ZERO))
    {
        return;
    }

    MetaRenderer_->GetColorData().MulColor = float4{1.0f, 1.0f, 1.0f, 1.0f};

    AttackCollider_->GetTransform().SetWorldMove({-RealDirX_ * 20.f, -400.f});
    AttackCollider_->GetTransform().SetLocalScale({75.f, 75.f});
    AttackCollider_->Off();
}


void Penitent::RangeAttackStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("RANGE_ATTACK.wav");

    MetaRenderer_->ChangeMetaAnimation("penitent_rangeAttack_shoot_anim");
}

void Penitent::RangeAttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::RangeAttackEnd(const StateInfo& _Info) {}


void Penitent::JumpRangeAttackStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("RANGE_ATTACK.wav");

    MetaRenderer_->ChangeMetaAnimation("penitent_rangeAttack_symbol_midair_anim");

    JumpForce_ = 10.f;
    Gravity_->SetActive(false);
}

void Penitent::JumpRangeAttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::JumpRangeAttackEnd(const StateInfo& _Info) { FallTime_ = 0.f; }


void Penitent::ExecutionStart(const StateInfo& _Info)
{
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
            if (0 > RealDirX_)
            {
                GetTransform().SetWorldMove({30.f, 0});
            }

            else
            {
                GetTransform().SetWorldMove({-30.f, 0});
            }
            break;

        case EXECUTIONTYPE::ShieldMaiden:
            if (0 > RealDirX_)
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
}


void Penitent::ParryingStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_START_PARRY.wav");

    MetaRenderer_->ChangeMetaAnimation("penitent_parry_failed");
}

void Penitent::ParryingUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == IsParrySuccess_)
    {
        IsParrySuccess_ = false;

        SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_GUARD.wav");

        MetaRenderer_->ChangeMetaAnimation("penitent_parry_success_animv3");
        ParryOn_ = false;
    }
}

void Penitent::ParryingEnd(const StateInfo& _Info) {}


void Penitent::ParryingAttackStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_PARRY_HIT.wav");

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

            if (1 == RealDirX_)
            {
                AttackEffect_->GetTransform().PixLocalPositiveX();
            }

            else if (-1 == RealDirX_)
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

void Penitent::RecoveryEnd(const StateInfo& _Info) { AttackEffect_->Renderer_->Off(); }


void Penitent::ReturnToPortStart(const StateInfo& _Info)
{
    IsReturnToPort_ = false;
    MetaRenderer_->ChangeMetaAnimation("RegresoAPuerto-Prayer");

    // AttackEffect_->Renderer_->On();
    // AttackEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
    // AttackEffect_->Renderer_->ChangeMetaAnimation("guardian_lady_protect_and_vanish");
}

void Penitent::ReturnToPortUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::ReturnToPortEnd(const StateInfo& _Info) {}


void Penitent::RespawnStart(const StateInfo& _Info)
{
    BodyCollider_->Off();

    SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_RESPAWN.wav");

    //일단 무조건 오른쪽을 본다.
    GetTransform().PixLocalPositiveX();

    if ("" != LastSaveLevel_)
    {
        MetaRenderer_->ChangeMetaAnimation("penitent_respawning_anim");

        AttackEffect_->Renderer_->On();
        AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_respawning_anim_querubs");
    }
}

void Penitent::RespawnUpdate(float _DeltaTime, const StateInfo& _Info)
{
    AttackEffect_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, PlayerEffectZ});

    Gravity_->SetActive(!IsGround_);
}

void Penitent::RespawnEnd(const StateInfo& _Info) { BodyCollider_->On(); }


// void Penitent::PrayStart(const StateInfo& _Info)
//{
//     MetaRenderer_->ChangeMetaAnimation("penitent_kneeled");
//     PlayerUI_->IsPrayEnd_ = false;
// }
//
// void Penitent::PrayUpdate(float _DeltaTime, const StateInfo& _Info)
//{
//     if (true == PlayerUI_->IsPrayEnd_)
//     {
//         MetaRenderer_->ChangeMetaAnimation("penitent_priedieu_stand_up_anim");
//     }
// }
//
// void Penitent::PrayEnd(const StateInfo& _Info) {}


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
    BodyCollider_->Off();
    MetaRenderer_->ChangeMetaAnimation("penitent_crossing_opendoor_out_anim");
}

void Penitent::DoorEntranceUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::DoorEntranceEnd(const StateInfo& _Info)
{
    GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, BeforeParallax5Z});

    GEngine::ChangeLevel(OutDoorLevel_);
}


void Penitent::DoorExitStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_crossing_teleportVortex_in");

    GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, PlayerZ});
}

void Penitent::DoorExitUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::DoorExitEnd(const StateInfo& _Info) { BodyCollider_->On(); }


void Penitent::ChargeAttackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_charged_attack_v2_anim");
}

void Penitent::ChargeAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == IsCharging_ && true == GameEngineInput::GetInst()->IsUpKey("PenitentChrage"))
    {
        ChangeState("Idle");
    }
}

void Penitent::ChargeAttackEnd(const StateInfo& _Info) { AttackCollider_->Off(); }


void Penitent::CollectSoulStart(const StateInfo& _Info)
{
    AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_pickUpGuiltFx");
    AttackEffect_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, PlayerEffectZ});
}

void Penitent::CollectSoulUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (false == AttackEffect_->Renderer_->IsUpdate())
    {
        ChangeState("Idle");
    }

    AttackEffect_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, PlayerEffectZ});
}

void Penitent::CollectSoulEnd(const StateInfo& _Info) { AttackEffect_->Renderer_->Off(); }


void Penitent::DeathStart(const StateInfo& _Info)
{
    IsPlayerDeath_ = true;

    MetaRenderer_->ChangeMetaAnimation("death_anim_blood");

    SoundPlayer_ = GameEngineSound::SoundPlayControl("PENITENT_DEATH_DEFAULT.wav");

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

void Penitent::DeathUpdate(float _DeltaTime, const StateInfo& _Info) { Gravity_->SetActive(!IsGround_); }

void Penitent::DeathEnd(const StateInfo& _Info) { SetHP(100); }


void Penitent::RisingStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_risingFromFallen_anim");
    MetaRenderer_->SetCurAnimationPause(true);
}

void Penitent::RisingUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == IsRising_)
    {
        IsRising_ = false;
        MetaRenderer_->SetCurAnimationPause(false);
    }

    Gravity_->SetActive(!IsGround_);
}

void Penitent::RisingEnd(const StateInfo& _Info) {}
