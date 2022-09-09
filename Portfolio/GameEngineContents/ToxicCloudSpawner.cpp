#include "PreCompile.h"
#include "ToxicCloudSpawner.h"
#include "ToxicCloud.h"

ToxicCloudSpawner::ToxicCloudSpawner() {}

ToxicCloudSpawner::~ToxicCloudSpawner() {}

void ToxicCloudSpawner::Start() {}

void ToxicCloudSpawner::Update(float _DeltaTime)
{
    //if (true == IsStop_)
    //{
    //    if (true == Cloud_->IsDeath())
    //    {
    //        Off();
    //        SpawnerEnd_ = true;
    //    }

    //    return;
    //}

    DelayTime_ += _DeltaTime;

    switch (SpawnerType_)
    {
        case SPAWNERTYPE::SP_LOWLEVLE:
            if (0.5f <= DelayTime_)
            {
                float XPos = Random_.RandomFloat(2000, 2800);

                DelayTime_ -= 0.5f;

                ToxicCloud* Clone = GetLevel()->CreateActor<ToxicCloud>();
                Clone->GetTransform().SetWorldPosition({XPos, -1300, FrontEffet});
                Clone->SetGround(ColMap_);

                float4 Dir = Target_->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
                Dir.Normalize();
                Dir.z = 0;
                Clone->SetDirectionX(Dir);

                ++CloudCount_;

                if (10 == CloudCount_)
                {
                    SpawnerEnd_ = true;
                    CloudCount_ = 0;
                    Off();
                }
            }
            break;

        case SPAWNERTYPE::SP_HIGHLEVLE:
            if (0.5f <= DelayTime_)
            {
                float XPos = Random_.RandomFloat(700, 1500);

                DelayTime_ -= 0.5f;

                ToxicCloud* Clone  = GetLevel()->CreateActor<ToxicCloud>();
                Clone->GetTransform().SetWorldPosition({XPos, -350, FrontEffet});
                Clone->SetGround(ColMap_);

                float4 Dir = Target_->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
                Dir.Normalize();
                Dir.z = 0;
                Clone->SetDirectionX(Dir);

                ++CloudCount_;

                if (5 == CloudCount_)
                {
                    CloudCount_ = 0;
                    SpawnerEnd_ = true;

                    Off();
                }
            }
            break;
    }
}

void ToxicCloudSpawner::End() {}
