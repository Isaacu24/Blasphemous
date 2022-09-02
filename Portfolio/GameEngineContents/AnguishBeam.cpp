#include "PreCompile.h"
#include "AnguishBeam.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

AnguishBeam::AnguishBeam() 
{
}

AnguishBeam::~AnguishBeam() 
{
}

void AnguishBeam::Start() 
{
    GetTransform().SetWorldScale({2.f, 2.f, 1.f});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("threeAnguishBigBeam");

        MetaRenderer_->CreateMetaAnimation(
            "threeAnguishBigBeam", {"threeAnguishBigBeam.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true}, Data);

        MetaRenderer_->AnimationBindEnd("threeAnguishBigBeam",
                                        [&](const FrameAnimation_DESC& _Info) { MetaRenderer_->Off(); });
    }

    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);
}

void AnguishBeam::Update(float _DeltaTime) {}

void AnguishBeam::End() {}
