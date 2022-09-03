#include "PreCompile.h"
#include "AttackCorpseEffecter.h"
#include "Corpse.h"
#include "CorpseGroundEffect.h"

namespace
{
    constexpr float DEFAULT_DELAY_TIME = 0.1f;
}

AttackCorpseEffecter::AttackCorpseEffecter()
    : CreatePos_(float4::ZERO)
    , Index_(0)
{}

AttackCorpseEffecter::~AttackCorpseEffecter() {}

void AttackCorpseEffecter::Start() {}

void AttackCorpseEffecter::Update(float _DeltaTime)
{
    if (true == IsCreate_)
    {
        DelayTime_ += _DeltaTime;

        if (DEFAULT_DELAY_TIME < DelayTime_)
        {
            ++Index_;
            DelayTime_ -= DEFAULT_DELAY_TIME;

            CorpseGroundEffect* Effect = GetLevel()->CreateActor<CorpseGroundEffect>();
            Effect->GetTransform().SetWorldPosition({CreatePos_.x + ((DirX_ * 30.f) * Index_),
                                                     CreatePos_.y,
                                                     static_cast<int>(ACTORORDER::MonsterEffect)});

            Corpse* NewCorpse = GetLevel()->CreateActor<Corpse>();
            NewCorpse->SetCreatePos(CreatePos_);
            NewCorpse->GetTransform().SetWorldPosition({CreatePos_.x + ((DirX_ * 30.f) * Index_),
                                                        CreatePos_.y,
                                                        static_cast<int>(ACTORORDER::MonsterEffect)});

            if (5 == Index_)
            {
                Index_    = 0;
                IsCreate_ = false;
            }
        }
    }
}

void AttackCorpseEffecter::End() {}
