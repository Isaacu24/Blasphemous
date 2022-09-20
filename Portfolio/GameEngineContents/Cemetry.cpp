#include "PreCompile.h"
#include "Cemetry.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

Cemetry::Cemetry() {}

Cemetry::~Cemetry() {}

void Cemetry::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("breakableSymbolStatue01");

        MetaRenderer_->CreateMetaAnimation(
            "breakableSymbolStatue01", {"breakableSymbolStatue01.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true}, Data);
    }

    MetaRenderer_->ChangeMetaAnimation("breakableSymbolStatue01");
}

void Cemetry::Update(float _DeltaTime) {}

void Cemetry::End() {}
