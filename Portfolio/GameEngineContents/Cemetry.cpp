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

    std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("breakableSymbolStatue01");

    {
        MetaRenderer_->CreateMetaAnimation(
            "breakableSymbolStatue01", {"breakableSymbolStatue01.png", 0, 5, 0.1f, true}, Data);
    }

    {
        MetaRenderer_->CreateMetaAnimation(
            "breakableSymbolStatue01_Explode",
            {"breakableSymbolStatue01.png", 6, static_cast<unsigned int>(Data.size() - 1), 0.08f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("breakableSymbolStatue01_Explode",
                                        [&](const FrameAnimation_DESC& _Info) { Death(); });
    }

    MetaRenderer_->ChangeMetaAnimation("breakableSymbolStatue01");

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->GetTransform().SetWorldScale({75.f, 100.f, 1.f});
    Collider_->ChangeOrder(COLLISIONORDER::Object);
    Collider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    Collider_->GetTransform().SetWorldMove({0.f, 50.f, 1.f});
}

void Cemetry::Update(float _DeltaTime)
{
    if (false == IsExplode_)
    {
        if (true
            == Collider_->IsCollision(
                CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
        {
            IsExplode_ = true;
            MetaRenderer_->ChangeMetaAnimation("breakableSymbolStatue01_Explode");
        }
    }
}

void Cemetry::End() {}
