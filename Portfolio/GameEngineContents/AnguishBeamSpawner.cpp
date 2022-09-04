#include "PreCompile.h"
#include "AnguishBeamSpawner.h"
#include "AnguishBeam.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

AnguishBeamSpawner::AnguishBeamSpawner() {}

AnguishBeamSpawner::~AnguishBeamSpawner() {}


void AnguishBeamSpawner::Start() {}

void AnguishBeamSpawner::Update(float _DeltaTime)
{
    if (true == IsStop_)
    {
        if (true == Beam_->IsDeath())
        {
            SpawnerEnd_ = true;
        }
    }
}

void AnguishBeamSpawner::End() {}


void AnguishBeamSpawner::CreateOnce()
{
    Beam_ = GetLevel()->CreateActor<AnguishBeam>();
    Beam_->GetTransform().SetWorldScale({2.f, 2.25f, 1.f});
    Beam_->GetTransform().SetWorldPosition(float4{1250, -965, static_cast<int>(ACTORORDER::MonsterEffect)});
    Beam_->MetaRenderer_->ChangeMetaAnimation("threeAnguishBigBeam");

    IsStop_ = true;
}

void AnguishBeamSpawner::CreateTwice()
{
    {
        Beam_ = GetLevel()->CreateActor<AnguishBeam>();
        Beam_->GetTransform().SetWorldScale({2.f, 2.25f, 1.f});
        Beam_->GetTransform().SetWorldPosition(float4{600, -965, static_cast<int>(ACTORORDER::MonsterEffect)});
        Beam_->MetaRenderer_->ChangeMetaAnimation("threeAnguishBigBeam");
    }

    {
        Beam_ = GetLevel()->CreateActor<AnguishBeam>();
        Beam_->GetTransform().SetWorldScale({2.f, 2.25f, 1.f});
        Beam_->GetTransform().SetWorldPosition(float4{1900, -965, static_cast<int>(ACTORORDER::MonsterEffect)});
        Beam_->MetaRenderer_->ChangeMetaAnimation("threeAnguishBigBeam");
    }

    IsStop_ = true;
}
