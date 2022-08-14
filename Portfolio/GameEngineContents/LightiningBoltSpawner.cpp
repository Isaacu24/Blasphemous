#include "PreCompile.h"
#include "LightiningBoltSpawner.h"
#include "LightiningBolt.h"

LightiningBoltSpawner::LightiningBoltSpawner()
    : CurType_(BOLTTYPE::Alone)
    , IsStrike_(false)
{}

LightiningBoltSpawner::~LightiningBoltSpawner() {}

void LightiningBoltSpawner::Start() {}

void LightiningBoltSpawner::Update(float _DeltaTime)
{
    DelayTime_ += _DeltaTime;

    if (6 == StrikeCount_)
    {
        StrikeCount_ = 0;
        Off();
        return;
    }

    if (2.0f >= DelayTime_)
    {
        return;
    }

    switch (CurType_)
    {
        case BOLTTYPE::Pair:
            {
                {
                    LightiningBolt* Bolt = GetLevel()->CreateActor<LightiningBolt>();
                    Bolt->GetTransform().SetWorldPosition(Target_->GetTransform().GetWorldPosition() + float4{50, 310});
                }

                {
                    LightiningBolt* Bolt = GetLevel()->CreateActor<LightiningBolt>();
                    Bolt->GetTransform().SetWorldPosition(Target_->GetTransform().GetWorldPosition()
                                                          + float4{-50, 310});
                }
               
                DelayTime_ -= 2.0f;
                CurType_ = BOLTTYPE::Alone;

                ++StrikeCount_;
            }
            break;
        case BOLTTYPE::Alone:
            {
                LightiningBolt* Bolt = GetLevel()->CreateActor<LightiningBolt>();
                Bolt->GetTransform().SetWorldPosition(Target_->GetTransform().GetWorldPosition() + float4{0, 310});

                DelayTime_ -= 2.0f;
                CurType_ = BOLTTYPE::Pair;

                ++StrikeCount_;
            }
            break;
        default:
            break;
    }
}

void LightiningBoltSpawner::End() {}
