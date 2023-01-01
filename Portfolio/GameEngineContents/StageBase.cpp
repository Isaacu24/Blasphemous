#include "PreCompile.h"
#include "StageBase.h"

StageBase::StageBase()
    : Stage_(nullptr)
    , ColMap_(nullptr)
    , DangleColiders_{}
    , Penitent_(nullptr)
    , BossMonster_(nullptr)
    , MonsterList_{}
    , IsLeftExit_(false)
    , IsRightExit_(false)
    , ShakeCount_(2)
    , MaxShakeCount_(2)
    , CameraZPos_(-1400.f)
    , IsChangeCameraPos_(false)
    , CameraOffset_(200.f)
    , ForceX_(10.f)
    , ForceY_(0.f)
{}

StageBase::~StageBase() {}

void StageBase::Start()
{
    StageFlow_.CreateStateMember(
        "Normally",
        std::bind(&StageBase::NormallyUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&StageBase::NormallyStart, this, std::placeholders::_1),
        std::bind(&StageBase::NormallyEnd, this, std::placeholders::_1));

    StageFlow_.CreateStateMember(
        "BossAppear",
        std::bind(&StageBase::BossAppearUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&StageBase::BossAppearStart, this, std::placeholders::_1),
        std::bind(&StageBase::BossAppearEnd, this, std::placeholders::_1));

    StageFlow_.CreateStateMember(
        "BossCombat",
        std::bind(&StageBase::BossCombatUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&StageBase::BossCombatStart, this, std::placeholders::_1),
        std::bind(&StageBase::BossCombatEnd, this, std::placeholders::_1));

    StageFlow_.CreateStateMember(
        "BossDead",
        std::bind(&StageBase::BossDeadUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&StageBase::BossDeadStart, this, std::placeholders::_1),
        std::bind(&StageBase::BossDeadEnd, this, std::placeholders::_1));

    StageFlow_.ChangeState("Normally");
}

void StageBase::Update(float _DeltaTime)
{
    StageFlow_.Update(_DeltaTime);

    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }

    if (true == GameEngineInput::GetInst()->IsPressKey("ColMapDebugKey"))
    {
        if (nullptr != ColMap_)
        {
            ColMap_->GetTransform().SetLocalPosition({0, 0, AfterParallax5Z});
        }
    }

    else
    {
        if (nullptr != ColMap_)
        {
            ColMap_->GetTransform().SetLocalPosition({0, 0, ColmapZ});
        }
    }
}

void StageBase::End() {}


void StageBase::LevelStartEvent() {}

void StageBase::LevelEndEvent()
{
    if (nullptr != LoadingActor_)
    {
        LoadingActor_->Death();
        LoadingActor_ = nullptr;
    }

    if (false == Penitent_->IsUpdate())
    {
        if (nullptr == Guilt_)
        {
            Guilt_ = CreateActor<PenitentGuilt>();
        }

        else
        {
            Guilt_->GetTransform().SetWorldPosition(Penitent_->GetLastJumpPosition());
            return;
        }

        if (true == Penitent_->GetIsPlayerDeath())
        {
            //마지막 도약 포지션을 기억한 후 해당 포지션에 길티 생성
            Guilt_->GetTransform().SetWorldPosition(
                {Penitent_->GetLastJumpPosition().x, Penitent_->GetLastJumpPosition().y, ObjectZ});
        }

        else
        {
            //도약하지 않았을 때에는 죽은 위치에 길티를 생성
            Guilt_->GetTransform().SetLocalPosition({Penitent_->GetTransform().GetWorldPosition().x,
                                                     Penitent_->GetTransform().GetWorldPosition().y,
                                                     ObjectZ});
        }
    }

    if (false == IsRightExit_ && false == IsLeftExit_)
    {
        IsLeftExit_ = true;
    }

    StageSoundPlayer_.Stop();
}


void StageBase::NormallyStart(const StateInfo& _Info) {}

void StageBase::NormallyUpdate(float _DeltaTime, const StateInfo& _Info) {}

void StageBase::NormallyEnd(const StateInfo& _Info) {}


void StageBase::BossAppearStart(const StateInfo& _Info) {}

void StageBase::BossAppearUpdate(float _DeltaTime, const StateInfo& _Info) {}

void StageBase::BossAppearEnd(const StateInfo& _Info) {}


void StageBase::BossCombatStart(const StateInfo& _Info) {}

void StageBase::BossCombatUpdate(float _DeltaTime, const StateInfo& _Info) {}

void StageBase::BossCombatEnd(const StateInfo& _Info) {}


void StageBase::BossDeadStart(const StateInfo& _Info) {}

void StageBase::BossDeadUpdate(float _DeltaTime, const StateInfo& _Info) {}

void StageBase::BossDeadEnd(const StateInfo& _Info) {}



void StageBase::CameraShaking(float _DeltaTime)
{
    if (true == IsShaking_)
    {
        ShakeTime_ += _DeltaTime;

        if (0.05f <= ShakeTime_)
        {
            ShakeTime_ = 0.f;

            if (0 == ShakeCount_ % 2)
            {
                GetMainCameraActor()->GetTransform().SetWorldMove({ForceX_, ForceY_});
                --ShakeCount_;
            }

            else
            {
                GetMainCameraActor()->GetTransform().SetWorldMove({-ForceX_, ForceY_});
                --ShakeCount_;
            }
        }

        if (0 >= ShakeCount_)
        {
            ShakeCount_ = MaxShakeCount_;

            ForceY_ = 0.f;

            IsShaking_ = false;
        }
    }
}

void StageBase::CameraShakingOneWay(float _DeltaTime)
{
    if (true == IsOneWayShaking_)
    {
        ShakeTime_ += _DeltaTime;

        if (0.05f <= ShakeTime_)
        {
            ShakeTime_ = 0.f;

            if (0 == ShakeCount_ % 2)
            {
                GetMainCameraActor()->GetTransform().SetWorldMove({ForceX_, ForceY_});
                --ShakeCount_;
            }

            else
            {
                GetMainCameraActor()->GetTransform().SetWorldMove({ForceX_, ForceY_});
                --ShakeCount_;
            }
        }

        if (0 >= ShakeCount_)
        {
            ShakeCount_ = MaxShakeCount_;

            ForceY_ = 0.f;

            IsOneWayShaking_ = false;
        }
    }
}
