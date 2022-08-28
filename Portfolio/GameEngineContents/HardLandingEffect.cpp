#include "PreCompile.h"
#include "HardLandingEffect.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

HardLandingEffect::HardLandingEffect() {}

HardLandingEffect::~HardLandingEffect() {}


void HardLandingEffect::Start()
{
    Renderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_hardlanding_effects");

        Renderer_->CreateMetaAnimation(
            "penitent_hardlanding_effects",
            {"penitent_hardlanding_effects.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);

        Renderer_->AnimationBindEnd("penitent_hardlanding_effects",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }
}

void HardLandingEffect::Update(float _DeltaTime) {}

void HardLandingEffect::End() {}
