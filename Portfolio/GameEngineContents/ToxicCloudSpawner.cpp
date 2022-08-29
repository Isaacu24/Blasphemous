#include "PreCompile.h"
#include "ToxicCloudSpawner.h"
#include "ToxicCloud.h"

ToxicCloudSpawner::ToxicCloudSpawner() {}

ToxicCloudSpawner::~ToxicCloudSpawner() {}

void ToxicCloudSpawner::Start() {}

void ToxicCloudSpawner::Update(float _DeltaTime)
{
    DelayTime_ += _DeltaTime;

    if (0.5f <= DelayTime_)
    {
        float XPos = Random_.RandomFloat(2000, 2800);

        DelayTime_ -= 0.5f;

        ToxicCloud* Clone = GetLevel()->CreateActor<ToxicCloud>();
        Clone->GetTransform().SetWorldPosition({XPos, -1300, static_cast<int>(ACTORORDER::BossMonster)});
        Clone->SetGround(ColMap_);
        Clone->SetDirectionX(Dir_);

        ++CloudCount_;

        if (10 == CloudCount_)
        {
            CloudCount_ = 0;
            Off();
        }
    }
}

void ToxicCloudSpawner::End() {}
