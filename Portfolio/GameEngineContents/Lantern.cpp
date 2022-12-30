#include "PreCompile.h"
#include "Lantern.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

Lantern::Lantern() {}

Lantern::~Lantern() {}

void Lantern::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("BreakableLantern01");

    {
        MetaRenderer_->CreateMetaAnimation("BreakableLantern01", {"BreakableLantern01.png", 0, 5, 0.1f, true}, Data);
    }

    {
        MetaRenderer_->CreateMetaAnimation(
            "BreakableLantern01_Explode",
            {"BreakableLantern01.png", 6, static_cast<unsigned int>(Data.size() - 1), 0.08f, false},
            Data);


        MetaRenderer_->AnimationBindFrame(
            "BreakableLantern01_Explode",
            [&](const FrameAnimation_DESC& _Info)
            {
                if (1 == _Info.CurFrame)
                {
                    SoundPlayer_ = GameEngineSound::SoundPlayControl("GLASS_PLATFORM_COLLAPSE.wav");
                    SoundPlayer_.Volume(0.3f);
                }
            });
    }

    MetaRenderer_->ChangeMetaAnimation("BreakableLantern01");

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->GetTransform().SetWorldScale({75.f, 100.f, 1.f});
    Collider_->ChangeOrder(COLLISIONORDER::Object);
    Collider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    Collider_->GetTransform().SetWorldMove({0.f, 50.f, 1.f});
}

void Lantern::Update(float _DeltaTime)
{
    if (false == IsExplode_)
    {
        if (true
            == Collider_->IsCollision(
                CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
        {
            IsExplode_ = true;
            MetaRenderer_->ChangeMetaAnimation("BreakableLantern01_Explode");
        }
    }
}

void Lantern::End() {}
