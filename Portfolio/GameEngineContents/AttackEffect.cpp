#include "PreCompile.h"
#include "AttackEffect.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

AttackEffect::AttackEffect() {}

AttackEffect::~AttackEffect() {}


void AttackEffect::Start()
{
    Renderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_jumping_attack_slasheslvl2");

        Renderer_->CreateMetaAnimation(
            "penitent_jumping_attack_slasheslvl2",
            {"penitent_jumping_attack_slasheslvl2.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        Renderer_->AnimationBindEnd("penitent_jumping_attack_slasheslvl2",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_upward_attack_slash_lvl1");

        Renderer_->CreateMetaAnimation(
            "penitent_upward_attack_slash_lvl1",
            {"penitent_upward_attack_slash_lvl1.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        Renderer_->AnimationBindEnd("penitent_upward_attack_slash_lvl1",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("three_hits_attack_slashes_lvl1_anim");

        Renderer_->CreateMetaAnimation("three_hits_attack_slashes_lvl1_anim_0",
                                       {"three_hits_attack_slashes_lvl1_anim.png", 0, 2, 0.1f, true},
                                       Data);

        Renderer_->AnimationBindEnd("three_hits_attack_slashes_lvl1_anim_0",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });

        Renderer_->CreateMetaAnimation("three_hits_attack_slashes_lvl1_anim_1",
                                       {"three_hits_attack_slashes_lvl1_anim.png", 3, 5, 0.1f, true},
                                       Data);


        Renderer_->AnimationBindEnd("three_hits_attack_slashes_lvl1_anim_1",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });

        Renderer_->CreateMetaAnimation(
            "three_hits_attack_slashes_lvl1_anim_2",
            {"three_hits_attack_slashes_lvl1_anim.png", 6, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        Renderer_->AnimationBindEnd("three_hits_attack_slashes_lvl1_anim_2",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }


    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_verticalattack_landing_effects_anim");

        Renderer_->CreateMetaAnimation("penitent_verticalattack_landing_effects_anim",
                                       {"penitent_verticalattack_landing_effects_anim.png",
                                        0,
                                        static_cast<unsigned int>(Data.size() - 1),
                                        0.07f,
                                        false},
                                       Data);

        Renderer_->AnimationBindEnd("penitent_verticalattack_landing_effects_anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_healthpotion_consuming_aura_anim");

        Renderer_->CreateMetaAnimation("penitent_healthpotion_consuming_aura_anim",
                                       {"penitent_healthpotion_consuming_aura_anim.png",
                                        0,
                                        static_cast<unsigned int>(Data.size() - 1),
                                        0.07f,
                                        false},
                                       Data);

        Renderer_->AnimationBindEnd("penitent_healthpotion_consuming_aura_anim",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("guardian_lady_protect_and_vanish");

        Renderer_->CreateMetaAnimation(
            "guardian_lady_protect_and_vanish",
            {"guardian_lady_protect_and_vanish.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        Renderer_->AnimationBindEnd("guardian_lady_protect_and_vanish",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_respawning_anim_querubs");

        Renderer_->CreateMetaAnimation(
            "penitent_respawning_anim_querubs",
            {"penitent_respawning_anim_querubs.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, false},
            Data);

        Renderer_->AnimationBindEnd("penitent_respawning_anim_querubs",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("threeAnguishBigBeamBlue");

        Renderer_->CreateMetaAnimation(
            "threeAnguishBigBeamBlue",
            {"threeAnguishBigBeamBlue.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.06f, false},
            Data);

        Renderer_->AnimationBindEnd("threeAnguishBigBeamBlue",
                                    [&](const FrameAnimation_DESC& _Info)
                                    {
                                        Renderer_->CurAnimationReset();
                                        Renderer_->Off();
                                    });
    }

    Renderer_->SetPivot(PIVOTMODE::METABOT);
}   

void AttackEffect::Update(float _DeltaTime) {}

void AttackEffect::End() {}