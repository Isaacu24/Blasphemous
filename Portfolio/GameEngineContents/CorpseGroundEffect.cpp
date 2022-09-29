#include "PreCompile.h"
#include "CorpseGroundEffect.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

CorpseGroundEffect::CorpseGroundEffect() {}

CorpseGroundEffect::~CorpseGroundEffect() {}

void CorpseGroundEffect::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("burntFace_rayBeam_impact");

        MetaRenderer_->CreateMetaAnimation(
            "burntFace_rayBeam_impact",
            {"burntFace_rayBeam_impact.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.06f, false},
            Data);

        MetaRenderer_->AnimationBindFrame("burntFace_rayBeam_impact",
                                          [&](const FrameAnimation_DESC& _Info)
                                          {
                                              if (1 == _Info.CurFrame)
                                              {
                                                  Collider_->On();
                                              }

                                              else if (10 == _Info.CurFrame)
                                              {
                                                  Collider_->Off();
                                              }
                                          });

        MetaRenderer_->AnimationBindEnd("burntFace_rayBeam_impact", [&](const FrameAnimation_DESC& _Info) { Death(); });
    }

    MetaRenderer_->ChangeFrameAnimation("burntFace_rayBeam_impact");

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::BossMonsterAttack);
    Collider_->GetTransform().SetWorldScale({100.0f, 100.0f});
    Collider_->SetDebugSetting(CollisionType::CT_OBB, float4{1.0f, 0.0f, 0.5f, 0.25f});
    Collider_->Off();
}

void CorpseGroundEffect::Update(float _DeltaTime) {}

void CorpseGroundEffect::End() {}
