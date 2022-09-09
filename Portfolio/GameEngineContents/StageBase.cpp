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
    , CameraZPos_(-1400.f)
    , IsChangeCameraPos_(false)
    , CameraOffset_(200.f)
{}

StageBase::~StageBase() {}


void StageBase::CameraShaking(float _DeltaTime)
{
    ShakeTime_ += _DeltaTime;

    if (0.05f <= ShakeTime_)
    {
        ShakeTime_ = 0.f;

        if (0 == ShakeCount_ % 2)
        {
            GetMainCameraActor()->GetTransform().SetWorldMove({10, 0});
            --ShakeCount_;
        }

        else
        {
            GetMainCameraActor()->GetTransform().SetWorldMove({-10, 0});
            --ShakeCount_;
        }
    }

    if (0 >= ShakeCount_)
    {
        ShakeCount_ = 30;
    }
}

void StageBase::Start() {}

void StageBase::Update(float _DeltaTime) {}

void StageBase::End() {}
