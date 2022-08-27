#include "PreCompile.h"
#include "CorpseGroundEffect.h"

CorpseGroundEffect::CorpseGroundEffect() 
{
}

CorpseGroundEffect::~CorpseGroundEffect() 
{
}

void CorpseGroundEffect::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationCutTexture("burntFace_rayBeam_impact", { "burntFace_rayBeam_impact.png", 0, 19, 0.07f, false });
	Renderer_->ChangeFrameAnimation("burntFace_rayBeam_impact");
    Renderer_->GetTransform().SetWorldScale({220.f, 220.f});

	Renderer_->AnimationBindEnd("burntFace_rayBeam_impact", std::bind(&CorpseGroundEffect::EffetEnd, this, std::placeholders::_1, this));
}

void CorpseGroundEffect::Update(float _DeltaTime)
{
}

void CorpseGroundEffect::End()
{
}
