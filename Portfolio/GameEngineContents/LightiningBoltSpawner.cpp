#include "PreCompile.h"
#include "LightiningBoltSpawner.h"
#include "LightiningBolt.h"

LightiningBoltSpawner::LightiningBoltSpawner()
    : CurType_(BOLTTYPE::Alone)
    , StrikeCount_(0)
    , IsStrike_(false)
    , LimitTime_(0.1f)
{}

LightiningBoltSpawner::~LightiningBoltSpawner() {}

void LightiningBoltSpawner::Start() {}

void LightiningBoltSpawner::Update(float _DeltaTime)
{
    // if (true == IsStop_)
    //{
    //     if (true == Bolt_->IsDeath())
    //     {
    //         Off();
    //         SpawnerEnd_ = true;
    //     }
    //     return;
    // }

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
                if (10 == StrikeCount_)
                {
                    StrikeCount_ = 0;
                    SpawnerEnd_  = true;
                    Off();
                    return;
                }

                if (LimitTime_ >= DelayTime_)
                {
                    return;
                }

                if (4 >= StrikeCount_)
                {
                    {
                        Bolt_ = GetLevel()->CreateActor<LightiningBolt>();
                        Bolt_->GetTransform().SetWorldScale({1.15f, 1.3f, 1});
                        Bolt_->GetTransform().SetWorldPosition(
                            {650 + (StrikeCount_ * 110.f), GetTransform().GetWorldPosition().y, FrontEffetZ});
                    }

                    DelayTime_ -= LimitTime_;
                    ++StrikeCount_;

                    if (5 == StrikeCount_)
                    {
                        LimitTime_ = 1.0f;
                        DelayTime_ = 0.f;
                    }
                }

                else if (5 <= StrikeCount_)
                {
                    {
                        Bolt_ = GetLevel()->CreateActor<LightiningBolt>();
                        Bolt_->GetTransform().SetWorldScale({1.15f, 1.3f, 1});
                        Bolt_->GetTransform().SetWorldPosition(
                            {2400 + (StrikeCount_ * -110.f), GetTransform().GetWorldPosition().y, FrontEffetZ});
                        Bolt_->GetTransform().PixWorldNegativeX();
                    }

                    DelayTime_ -= LimitTime_;
                    ++StrikeCount_;

                    if (6 == StrikeCount_)
                    {
                        LimitTime_ = 0.1f;
                        DelayTime_ = 0.f;
                    }
                }
            }
            break;
    }
}

void LightiningBoltSpawner::End() {}
