#include "PreCompile.h"
#include "MagicMissileSpawner.h"
#include "MagicMissile.h"
#include "MultipleMagicMissile.h"

MagicMissileSpawner::MagicMissileSpawner()
    : MissileCount_(1)
{}

MagicMissileSpawner::~MagicMissileSpawner() {}

void MagicMissileSpawner::Start() {}

void MagicMissileSpawner::Update(float _DeltaTime)
{
    DelayTime_ += _DeltaTime;

    switch (SpawnerType_)
    {
        case SPAWNERTYPE::SP_LOWLEVLE:
            {
                if (1.0f >= DelayTime_)
                {
                    return;
                }

                if (8 == MissileCount_)
                {
                    Off();
                    SpawnerEnd_ = true;
                    MissileCount_ = 0;
                    return;
                }

                if (0 == MissileCount_ % 2)  //Â¦¼ö(À§)
                {
                    MagicMissile* Missile = GetLevel()->CreateActor<MagicMissile>();
                    Missile->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{0, 50});
                    Missile->SetDirection(Dir_);

                    DelayTime_ = 0.f;
                    ++MissileCount_;
                }

                else  //È¦¼ö(¾Æ·¡)
                {
                    MagicMissile* Missile = GetLevel()->CreateActor<MagicMissile>();
                    Missile->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{0, -50});
                    Missile->SetDirection(Dir_);

                    DelayTime_ = 0.f;
                    ++MissileCount_;
                }
            }
            break;

        case SPAWNERTYPE::SP_HIGHLEVLE:
            {
                if (true == IsCreate_)
                {
                    Off();
                    SpawnerEnd_ = true;
                    IsCreate_   = false;
                    return;
                }

                IsCreate_ = true;

                MultipleMagicMissile* Clone = GetLevel()->CreateActor<MultipleMagicMissile>();
                Clone->GetTransform().SetWorldScale({2, 2, 1}); 
                Clone->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{-350, 0});

                MultipleMagicMissile* Clone1 = GetLevel()->CreateActor<MultipleMagicMissile>();
                Clone1->GetTransform().SetWorldScale({2, 2, 1}); 
                Clone1->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{350, 0});
            }


            break;
    }
}

void MagicMissileSpawner::End() {}
