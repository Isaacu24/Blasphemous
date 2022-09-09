#include "PreCompile.h"
#include "AnguishBeam.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

AnguishBeam::AnguishBeam() {}

AnguishBeam::~AnguishBeam() {}

void AnguishBeam::Start()
{
    GetTransform().SetWorldScale({2.f, 2.f, 1.f});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->GetTransform().SetWorldScale({400.f, 600.f, 1.f});
    Collider_->ChangeOrder(COLLISIONORDER::BossMonsterAttack);
    Collider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.7f, 0.1f, 0.8f, 0.5f});
    Collider_->GetTransform().SetWorldMove({0.f, 300.f});
    Collider_->Off();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("threeAnguishBigBeam");

        MetaRenderer_->CreateMetaAnimation(
            "threeAnguishBigBeam",
            {"threeAnguishBigBeam.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        MetaRenderer_->AnimationBindFrame("threeAnguishBigBeam",
                                          [&](const FrameAnimation_DESC& _Info)
                                          {
                                              if (45 == _Info.CurFrame)
                                              {
                                                  Collider_->On();
                                              }

                                              if (55 == _Info.CurFrame)
                                              {
                                                  Collider_->Off();
                                              }
                                          });

        MetaRenderer_->AnimationBindEnd("threeAnguishBigBeam", [&](const FrameAnimation_DESC& _Info) { Death(); });
    }

    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);
}

void AnguishBeam::Update(float _DeltaTime) {}

void AnguishBeam::End() {}
