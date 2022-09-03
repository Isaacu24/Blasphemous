#include "PreCompile.h"
#include "AnguishBeamSpawner.h"
#include "AnguishBeam.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

AnguishBeamSpawner::AnguishBeamSpawner() {}

AnguishBeamSpawner::~AnguishBeamSpawner() {}


void AnguishBeamSpawner::Start() {}

void AnguishBeamSpawner::Update(float _DeltaTime) {}

void AnguishBeamSpawner::End() {}


void AnguishBeamSpawner::CreateOnce() 
{ 
	AnguishBeam* Beam = GetLevel()->CreateActor<AnguishBeam>(); 
	Beam->GetTransform().SetWorldPosition(float4{1000, -800, static_cast<int>(ACTORORDER::MonsterEffect)});
    Beam->MetaRenderer_->ChangeMetaAnimation("threeAnguishBigBeam");

    SpawnerEnd_ = true;
}

void AnguishBeamSpawner::CreateTwice() 
{
	{
        AnguishBeam* Beam = GetLevel()->CreateActor<AnguishBeam>();
        Beam->GetTransform().SetWorldPosition(float4{500, -800, static_cast<int>(ACTORORDER::MonsterEffect)});
        Beam->MetaRenderer_->ChangeMetaAnimation("threeAnguishBigBeam");
	}

	{
        AnguishBeam* Beam = GetLevel()->CreateActor<AnguishBeam>();
        Beam->GetTransform().SetWorldPosition(float4{1500, -800, static_cast<int>(ACTORORDER::MonsterEffect)});
        Beam->MetaRenderer_->ChangeMetaAnimation("threeAnguishBigBeam");
	}

    SpawnerEnd_ = true;

}
