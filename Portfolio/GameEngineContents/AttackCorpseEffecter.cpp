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

void AttackCorpseEffecter::Start() {}

void AttackCorpseEffecter::Update(float _DeltaTime)
{
}

void AttackCorpseEffecter::End() {}
