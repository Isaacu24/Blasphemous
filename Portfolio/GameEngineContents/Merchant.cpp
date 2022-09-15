#include "PreCompile.h"
#include "Merchant.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

Merchant::Merchant() {}

Merchant::~Merchant() {}

void Merchant::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ladrona_idle_anim");

        MetaRenderer_->CreateMetaAnimation(
            "ladrona_idle_anim",
            {"ladrona_idle_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ladrona_death_anim_0");

        MetaRenderer_->CreateMetaAnimation(
            "ladrona_death_anim_0",
            {"ladrona_death_anim_0.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }


    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ladrona_hit_reaction_anim");

        MetaRenderer_->CreateMetaAnimation(
            "ladrona_hit_reaction_anim",
            {"ladrona_hit_reaction_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    MetaRenderer_->ChangeMetaAnimation("ladrona_idle_anim");
    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);
}

void Merchant::Update(float _Update) {}

void Merchant::End() {}
