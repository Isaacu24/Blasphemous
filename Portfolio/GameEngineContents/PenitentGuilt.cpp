#include "PreCompile.h"
#include "PenitentGuilt.h"

PenitentGuilt::PenitentGuilt() {}

PenitentGuilt::~PenitentGuilt() {}

// GameEngineTexture::Cut("guiltSystem_blinkFxs.png", 7, 5);
// GameEngineTexture::Cut("guiltDropVanish.png", 5, 2);

void PenitentGuilt::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();

    Renderer_->CreateFrameAnimationCutTexture("guiltSystem_blinkFxs", {"guiltSystem_blinkFxs.png", 0, 32, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("guiltDropVanish", {"guiltDropVanish.png", 0, 7, 0.1f, true});

    Renderer_->AnimationBindEnd("guiltDropVanish",
                                [&](const FrameAnimation_DESC&) { Death();
                                });

    Renderer_->ChangeFrameAnimation("guiltSystem_blinkFxs");
    Renderer_->GetTransform().SetWorldScale({200, 200, 1});
    Renderer_->SetPivot(PIVOTMODE::BOT);
}

void PenitentGuilt::Update(float _DeltaTime) {}

void PenitentGuilt::End() {}

void PenitentGuilt::Expiation() { Renderer_->ChangeFrameAnimation("guiltDropVanish"); }
