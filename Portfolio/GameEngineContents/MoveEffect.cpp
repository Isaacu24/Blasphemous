#include "PreCompile.h"
#include "MoveEffect.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

MoveEffect::MoveEffect() {}

MoveEffect::~MoveEffect() {}

void MoveEffect::Start()
{
    Renderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_running_dust_anim");

        Renderer_->CreateMetaAnimation(
            "penitent_running_dust_anim",
            {"penitent_running_dust_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        Renderer_->AnimationBindEnd("penitent_running_dust_anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent-stop-running-dust");

        Renderer_->CreateMetaAnimation(
            "penitent-stop-running-dust",
            {"penitent-stop-running-dust.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        Renderer_->AnimationBindEnd("penitent-stop-running-dust",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent-jumping-landing-dust-anim");

        Renderer_->CreateMetaAnimation(
            "penitent-jumping-dust-anim", {"penitent-jumping-landing-dust-anim.png", 0, 3, 0.07f, false}, Data);

        Renderer_->AnimationBindEnd("penitent-jumping-dust-anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });

        Renderer_->CreateMetaAnimation(
            "penitent-landing-dust-anim", {"penitent-jumping-landing-dust-anim.png", 4, 6, 0.07f, false}, Data);

        Renderer_->AnimationBindEnd("penitent-landing-dust-anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_start_dodge_dust_anim");

        Renderer_->CreateMetaAnimation(
            "penitent_start_dodge_dust_anim",
            {"penitent_start_dodge_dust_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        Renderer_->AnimationBindEnd("penitent_start_dodge_dust_anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_stop_dodge_dust_anim");

        Renderer_->CreateMetaAnimation(
            "penitent_stop_dodge_dust_anim",
            {"penitent_stop_dodge_dust_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        Renderer_->AnimationBindEnd("penitent_stop_dodge_dust_anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_pushback_grounded_dust_effect_anim");

        Renderer_->CreateMetaAnimation("penitent_pushback_grounded_dust_effect_anim",
                                       {"penitent_pushback_grounded_dust_effect_anim.png",
                                        0,
                                        static_cast<unsigned int>(Data.size() - 1),
                                        0.07f,
                                        true},
                                       Data);

        Renderer_->AnimationBindEnd("penitent_pushback_grounded_dust_effect_anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_throwback_ground_contact_dust_anim");

        Renderer_->CreateMetaAnimation("penitent_throwback_ground_contact_dust_anim",
                                       {"penitent_throwback_ground_contact_dust_anim.png",
                                        0,
                                        static_cast<unsigned int>(Data.size() - 1),
                                        0.07f,
                                        true},
                                       Data);

        Renderer_->AnimationBindEnd("penitent_throwback_ground_contact_dust_anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    Renderer_->SetPivot(PIVOTMODE::METABOT);
}

void MoveEffect::Update(float _DeltaTime) {}

void MoveEffect::End() {}
