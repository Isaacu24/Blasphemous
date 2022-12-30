#include "PreCompile.h"
#include "ShopObejct.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

ShopObejct::ShopObejct() {}

ShopObejct::~ShopObejct() {}

void ShopObejct::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("merchantTent_censer01");

        MetaRenderer_->CreateMetaAnimation(
            "merchantTent_censer01",
            {"merchantTent_censer01.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("merchantTent_lamp01");

        MetaRenderer_->CreateMetaAnimation(
            "merchantTent_lamp01",
            {"merchantTent_lamp01.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("merchantTent_pennant01");

        MetaRenderer_->CreateMetaAnimation(
            "merchantTent_pennant01",
            {"merchantTent_pennant01.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("merchantTent_pennant02");

        MetaRenderer_->CreateMetaAnimation(
            "merchantTent_pennant02",
            {"merchantTent_pennant02.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("merchantTent_pennant03");

        MetaRenderer_->CreateMetaAnimation(
            "merchantTent_pennant03",
            {"merchantTent_pennant03.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, true},
            Data);
    }

    MetaRenderer_->ChangeMetaAnimation("merchantTent_censer01");
}

void ShopObejct::Update(float _DeltaTime) {}

void ShopObejct::End() {}
