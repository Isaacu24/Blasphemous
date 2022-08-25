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
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_jumping_attack_slasheslvl1");

        Renderer_->CreateMetaAnimation(
            "penitent_jumping_attack_slasheslvl1",
            {"penitent_jumping_attack_slasheslvl1.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        Renderer_->AnimationBindEnd("penitent_jumping_attack_slasheslvl1",
                                    [&](const FrameAnimation_DESC& _Info) { Renderer_->Off(); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_jumping_attack_slasheslvl2");

        Renderer_->CreateMetaAnimation(
            "penitent_jumping_attack_slasheslvl2",
            {"penitent_jumping_attack_slasheslvl2.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        Renderer_->AnimationBindEnd("penitent_jumping_attack_slasheslvl2",
                                    [&](const FrameAnimation_DESC& _Info) { Renderer_->Off(); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_verticalattack_landing_effects_anim");

        Renderer_->CreateMetaAnimation(
            "penitent_verticalattack_landing_effects_anim",
            {"penitent_verticalattack_landing_effects_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        Renderer_->AnimationBindEnd("penitent_verticalattack_landing_effects_anim",
                                    [&](const FrameAnimation_DESC& _Info) { Renderer_->Off(); });
    }

    Renderer_->SetPivot(PIVOTMODE::METABOT);
}

void AttackEffect::Update(float _DeltaTime) {}

void AttackEffect::End() {}