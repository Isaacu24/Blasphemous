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
                float4 TargetPos = Target_->GetTransform().GetWorldPosition();

                {
                    LightiningBolt* Bolt = GetLevel()->CreateActor<LightiningBolt>();
                    Bolt->GetTransform().SetWorldPosition({TargetPos.x - 50.f, GetTransform().GetWorldPosition().y});
                }

                {
                    LightiningBolt* Bolt = GetLevel()->CreateActor<LightiningBolt>();
                    Bolt->GetTransform().SetWorldPosition({TargetPos.x + 50.f, GetTransform().GetWorldPosition().y});
                }

                DelayTime_ -= 2.0f;
                CurType_ = BOLTTYPE::Alone;

                ++StrikeCount_;
            }
            break;
        case BOLTTYPE::Alone:
            {
                float4 TargetPos = Target_->GetTransform().GetWorldPosition();

                LightiningBolt* Bolt = GetLevel()->CreateActor<LightiningBolt>();
                Bolt->GetTransform().SetWorldPosition({TargetPos.x, GetTransform().GetWorldPosition().y});

                DelayTime_ -= 2.0f;
                CurType_ = BOLTTYPE::Pair;

                ++StrikeCount_;
            }
            break;
    }
}

void LightiningBoltSpawner::End() {}
