#include "PreCompile.h"
#include "HitEffect.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

HitEffect::HitEffect() {}

HitEffect::~HitEffect() {}

void HitEffect::Start()
{
    Renderer_ = CreateComponent<MetaTextureRenderer>();

    //ÇÇ°Ý
    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("pushback_sparks_anim");

        Renderer_->CreateMetaAnimation(
            "pushback_sparks_anim",
            {"pushback_sparks_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);

        Renderer_->AnimationBindFrame("pushback_sparks_anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                          if (1 == _Info.CurFrame)
                                          {
                                              int a = 0;
                                          }
                                    });

        Renderer_->AnimationBindEnd("pushback_sparks_anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    Renderer_->SetPivot(PIVOTMODE::METABOT);
}

void HitEffect::Update(float _DeltaTime) {}

void HitEffect::End() {}
