#include "PreCompile.h"
#include "MagicMissileSpawner.h"
#include "MagicMissile.h"
#include "MultipleMagicMissile.h"

MagicMissileSpawner::MagicMissileSpawner()
    : MissileCount_(0)
    , NestingCount_(0)
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
                if (0.75f >= DelayTime_)
                {
                    return;
                }

                if (4 == NestingCount_)
                {
                    Off();
                    SpawnerEnd_   = true;
                    NestingCount_ = 0;
                    return;
                }

                if (0 == MissileCount_)  //Â¦¼ö(À§)
                {
                    MagicMissile* Missile = GetLevel()->CreateActor<MagicMissile>();
                    Missile->GetTransform().SetWorldPosition({GetTransform().GetWorldPosition().x,
                                                              GetTransform().GetWorldPosition().y + 60.f,
                                                              BossMonsterEffectZ});
                    Missile->SetStartPosition(Missile->GetTransform().GetWorldPosition());
                    Missile->SetDirection(Dir_);
                    Missile->SetGround(ColMap_);

                    DelayTime_ = 0.f;
                    ++MissileCount_;
                }

                else if (1 == MissileCount_)
                {
                    MagicMissile* Missile = GetLevel()->CreateActor<MagicMissile>();
                    Missile->GetTransform().SetWorldPosition({GetTransform().GetWorldPosition().x - 10.f,
                                                              GetTransform().GetWorldPosition().y,
                                                              BossMonsterEffectZ});
                    Missile->SetStartPosition(Missile->GetTransform().GetWorldPosition());
                    Missile->SetDirection(Dir_);
                    Missile->SetGround(ColMap_);

                    DelayTime_ = 0.f;
                    ++MissileCount_;
                }

                else if (2 == MissileCount_)
                {
                    MagicMissile* Missile = GetLevel()->CreateActor<MagicMissile>();
                    Missile->GetTransform().SetWorldPosition({GetTransform().GetWorldPosition().x,
                                                              GetTransform().GetWorldPosition().y - 90.f,
                                                              BossMonsterEffectZ});
                    Missile->SetStartPosition(Missile->GetTransform().GetWorldPosition());
                    Missile->SetDirection(Dir_);
                    Missile->SetGround(ColMap_);

                    DelayTime_ = 0.f;
                    MissileCount_ = 0;
                    ++NestingCount_;
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

                MultipleMagicMissile* Missile = GetLevel()->CreateActor<MultipleMagicMissile>();
                Missile->GetTransform().SetWorldScale({2, 2, 1});
                Missile->GetTransform().SetWorldPosition(
                    {GetTransform().GetWorldPosition().x - 350.f, GetTransform().GetWorldPosition().y, FrontEffetZ});
                Missile->SetGround(ColMap_);

                MultipleMagicMissile* Missile1 = GetLevel()->CreateActor<MultipleMagicMissile>();
                Missile1->GetTransform().SetWorldScale({2, 2, 1});
                Missile1->GetTransform().SetWorldPosition(
                    {GetTransform().GetWorldPosition().x + 350.f, GetTransform().GetWorldPosition().y, FrontEffetZ});
                Missile1->SetGround(ColMap_);
            }
            break;
    }
}

void MagicMissileSpawner::End() {}
