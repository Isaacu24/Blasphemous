#include "PreCompile.h"
#include "MultipleMagicMissile.h"
#include "MagicMissile.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

MultipleMagicMissile::MultipleMagicMissile()
    : IsCreate_(true)
{}

MultipleMagicMissile::~MultipleMagicMissile() {}

void MultipleMagicMissile::Start()
{
    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("BurntFaceHandShootingEffectBeam");

    {
        MetaRenderer_->CreateMetaAnimation(
            "Shoot",
            {"BurntFaceHandShootingEffectBeam.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.09f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("Shoot",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            ++AnimationCount_;

                                            if (2 == AnimationCount_)
                                            {
                                                IsCreate_ = false;
                                                MetaRenderer_->ChangeMetaAnimation("Death");
                                            }
                                        });
    }

    {
        std::vector<unsigned int> Frames = {};
        Frames.resize(8);

        Frames[0] = 7;
        Frames[1] = 6;
        Frames[2] = 5;
        Frames[3] = 4;
        Frames[4] = 3;
        Frames[5] = 2;
        Frames[6] = 1;
        Frames[7] = 0;

        MetaRenderer_->CreateMetaAnimation(
            "Death", {"BurntFaceHandShootingEffectBeam.png", Frames, 0.09f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("Death",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            AnimationCount_ = 0;
                                            Death();
                                        });
    }


    MetaRenderer_->ChangeMetaAnimation("Shoot");

    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);
}

void MultipleMagicMissile::Update(float _DeltaTime)
{
    if (true == IsCreate_)
    {
        return;
    }

    IsCreate_ = true;

    for (size_t i = 0; i < 6; i++)
    {
        MagicMissile* Clone = GetLevel()->CreateActor<MagicMissile>();
        Clone->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
        Clone->SetSpeed(100.f);

        switch (i)
        {
            case 0:
                Clone->SetDirection(float4::RIGHT);
                break;

            case 1:
                Clone->SetDirection(float4::RIGHT + float4::DOWN);
                Clone->GetTransform().SetWorldRotation({0, 0, -45});
                break;

            case 2:
                Clone->SetDirection(float4::LEFT + float4::DOWN);
                Clone->GetTransform().PixLocalNegativeX();
                Clone->GetTransform().SetWorldRotation({0, 0, 45});
                break;

            case 3:
                Clone->SetDirection(float4::LEFT);
                Clone->GetTransform().PixLocalNegativeX();
                break;

            case 4:
                Clone->SetDirection(float4::LEFT + float4::UP);
                Clone->GetTransform().PixLocalNegativeX();
                Clone->GetTransform().SetWorldRotation({0, 0, -45});
                break;

            case 5:
                Clone->SetDirection(float4::RIGHT + float4::UP);
                Clone->GetTransform().SetWorldRotation({0, 0, 45});
                break;
        }
    }
}

void MultipleMagicMissile::End() {}
