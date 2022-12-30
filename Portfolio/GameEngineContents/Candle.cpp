#include "PreCompile.h"
#include "Candle.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

Candle::Candle() {}

Candle::~Candle() {}

void Candle::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("candlegroup02");

        MetaRenderer_->CreateMetaAnimation(
            "candlegroup02", {"candlegroup02.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.11f, true}, Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("candlegroup04");

        MetaRenderer_->CreateMetaAnimation(
            "candlegroup04", {"candlegroup04.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.11f, true}, Data);
    }

    MetaRenderer_->ChangeMetaAnimation("candlegroup02");
}

void Candle::Update(float _DeltaTime) {}

void Candle::End() {}
