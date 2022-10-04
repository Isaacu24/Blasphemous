#include "PreCompile.h"
#include "AttackCorpseEffecter.h"
#include "Corpse.h"
#include "CorpseGroundEffect.h"

namespace
{
    constexpr float DEFAULT_DELAY_TIME = 0.15f;
}

AttackCorpseEffecter::AttackCorpseEffecter()
    : CreatePos_(float4::ZERO)
    , Index_(0)
{}

AttackCorpseEffecter::~AttackCorpseEffecter() {}

void AttackCorpseEffecter::CreateEffect() 
    {
    float FRandom = GameEngineRandom::MainRandom.RandomFloat(30, 80);

    CorpseGroundEffect* Effect = GetLevel()->CreateActor<CorpseGroundEffect>();
    Effect->GetTransform().SetWorldPosition(
        {CreatePos_.x + ((DirX_ * 30.f) * Index_), CreatePos_.y, BossMonsterEffectZ});

    float IRandom = GameEngineRandom::MainRandom.RandomInt(0, 1);

    Corpse* NewCorpse = GetLevel()->CreateActor<Corpse>();
    NewCorpse->SetCreatePos(CreatePos_ + float4{0, FRandom + (10.f * Index_)});
    NewCorpse->GetTransform().SetWorldPosition(
        {CreatePos_.x + ((DirX_ * 30.f) * Index_), CreatePos_.y, BossMonsterEffectZ});

    if (0 == IRandom)
    {
        NewCorpse->GetTransform().PixLocalNegativeX();
    }

    switch (SoundIndex_)
    {
        case 0:
            SoundPlayer_ = GameEngineSound::SoundPlayControl("ELDER_BROTHER_CORPSE_WAVE.wav");
            break;

        case 1:
            SoundPlayer_ = GameEngineSound::SoundPlayControl("ELDER_BROTHER_CORPSE_WAVE_2.wav");
            break;

        case 2:
            SoundPlayer_ = GameEngineSound::SoundPlayControl("ELDER_BROTHER_CORPSE_WAVE_3.wav");
            break;
    }

    ++SoundIndex_;

    if (2 <= SoundIndex_)
    {
        SoundIndex_ = 0;
    }
}

void AttackCorpseEffecter::Start() {}

void AttackCorpseEffecter::Update(float _DeltaTime)
{
}

void AttackCorpseEffecter::End() {}
