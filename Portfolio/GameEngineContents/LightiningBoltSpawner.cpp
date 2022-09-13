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
    //if (true == IsStop_)
    //{
    //    if (true == Bolt_->IsDeath())
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
            {
                if (6 == StrikeCount_)
                {
                    SpawnerEnd_  = true;
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
                                Bolt->GetTransform().SetWorldPosition(
                                    {TargetPos.x - 50.f, GetTransform().GetWorldPosition().y, FrontEffetZ});
                            }

                            {
                                LightiningBolt* Bolt = GetLevel()->CreateActor<LightiningBolt>();
                                Bolt->GetTransform().SetWorldPosition(
                                    {TargetPos.x + 50.f, GetTransform().GetWorldPosition().y, FrontEffetZ});
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
                            Bolt->GetTransform().SetWorldPosition(
                                {TargetPos.x, GetTransform().GetWorldPosition().y, FrontEffetZ});

                            DelayTime_ -= 2.0f;
                            CurType_ = BOLTTYPE::Pair;

                            ++StrikeCount_;
                        }
                        break;
                }
            }
            break;

        case SPAWNERTYPE::SP_HIGHLEVLE:
            {
                if (3 == StrikeCount_)
                {
                    StrikeCount_ = 0;
                    SpawnerEnd_ = true;
                    Off();
                    return;
                }

                if (2.0f >= DelayTime_)
                {
                    return;
                }

                float4 TargetPos = Target_->GetTransform().GetWorldPosition();

                {
                    Bolt_ = GetLevel()->CreateActor<LightiningBolt>();
                    Bolt_->GetTransform().SetWorldScale({1.15f, 1.3f, 1});
                    Bolt_->GetTransform().SetWorldPosition(
                        {TargetPos.x, GetTransform().GetWorldPosition().y, FrontEffetZ});
                }

                DelayTime_ -= 2.0f;
                ++StrikeCount_;
            }
            break;
    }
}

void LightiningBoltSpawner::End() {}
