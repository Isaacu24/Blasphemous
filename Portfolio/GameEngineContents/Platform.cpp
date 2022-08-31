#include "PreCompile.h"
#include "Platform.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

Platform::Platform()
    : LifeTime_(0.f)
{}

Platform::~Platform() {}

void Platform::Start()
{
    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("bloodsand_platform_64x64_novisible_to_visible");

        MetaRenderer_->CreateMetaAnimation("bloodsand_platform_64x64_novisible_to_visible",
                                           {"bloodsand_platform_64x64_novisible_to_visible.png",
                                            0,
                                            static_cast<unsigned int>(Data.size() - 1),
                                            0.07f,
                                            true},
                                           Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ashplatform_64x64_anim");

        MetaRenderer_->CreateMetaAnimation(
            "ashplatform_64x64_anim",
            {"ashplatform_64x64_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("bloodsand_platform_64x64_visible_to_novisible");

        MetaRenderer_->CreateMetaAnimation("bloodsand_platform_64x64_visible_to_novisible",
                                           {"bloodsand_platform_64x64_visible_to_novisible.png",
                                            0,
                                            static_cast<unsigned int>(Data.size() - 1),
                                            0.07f,
                                            true},
                                           Data);
    }


    MetaRenderer_->AnimationBindEnd("bloodsand_platform_64x64_novisible_to_visible",
                                    [&](const FrameAnimation_DESC& _Info)
                                    { MetaRenderer_->ChangeMetaAnimation("ashplatform_64x64_anim"); });

    MetaRenderer_->AnimationBindFrame(
        "bloodsand_platform_64x64_novisible_to_visible",
        [&](const FrameAnimation_DESC& _Info)
        {
            if (1 == _Info.CurFrame)
            {
                MetaRenderer_->GetColorData().MulColor = float4{5.0f, 5.0f, 5.0f, 1.0f};
            }

            if (5 == _Info.CurFrame)
            {
                MetaRenderer_->GetColorData().MulColor = float4{1.0f, 1.0f, 1.0f, 1.0f};
            }
        });


    MetaRenderer_->AnimationBindEnd("bloodsand_platform_64x64_visible_to_novisible",
                                    [&](const FrameAnimation_DESC& _Info) { Death(); });

    MetaRenderer_->AnimationBindFrame("bloodsand_platform_64x64_visible_to_novisible",
                                      [&](const FrameAnimation_DESC& _Info)
                                      {
                                          if (1 == _Info.CurFrame)
                                          {
                                              MetaRenderer_->GetColorData().MulColor = float4{5.0f, 5.0f, 5.0f, 1.0f};
                                          }

                                          if (6 == _Info.CurFrame)
                                          {
                                              Collider_->Off();
                                          }
                                      });

    MetaRenderer_->ChangeMetaAnimation("bloodsand_platform_64x64_novisible_to_visible");
    MetaRenderer_->SetPivot(PIVOTMODE::TOP);

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::Platform);
    Collider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.5f, 0.1f, 0.5f, 0.1f});
    Collider_->GetTransform().SetWorldScale({60.f, 20.f, 1.0f});
    Collider_->GetTransform().SetWorldMove({0, -35});
}

void Platform::Update(float _DeltaTime)
{
    LifeTime_ += _DeltaTime;

    if (DeathTime_ <= LifeTime_)
    {
        MetaRenderer_->ChangeMetaAnimation("bloodsand_platform_64x64_visible_to_novisible");
    }
}

void Platform::End() {}
