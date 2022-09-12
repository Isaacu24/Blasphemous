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
    , CameraZPos_(-1400.f)
    , IsChangeCameraPos_(false)
    , CameraOffset_(200.f)
{}

StageBase::~StageBase() {}


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
                GetMainCameraActor()->GetTransform().SetWorldMove({5, 0});
                --ShakeCount_;
            }

            else
            {
                GetMainCameraActor()->GetTransform().SetWorldMove({-5, 0});
                --ShakeCount_;
            }
        }

        if (0 >= ShakeCount_)
        {
            ShakeCount_ = 2;
            IsShaking_  = false;
        }
    }
}


void StageBase::Start() {}

void StageBase::Update(float _DeltaTime) {}

void StageBase::End() {}
