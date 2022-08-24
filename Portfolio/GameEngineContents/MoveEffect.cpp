#include "PreCompile.h"
#include "MoveEffect.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

MoveEffect::MoveEffect() 
{
}

MoveEffect::~MoveEffect() 
{
}

void MoveEffect::Start() 
{
    Renderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent-stop-running-dust");

        Renderer_->CreateMetaAnimation(
            "penitent-stop-running-dust",
            {"penitent-stop-running-dust.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        Renderer_->AnimationBindEnd("penitent-stop-running-dust",
                                    [&](const FrameAnimation_DESC& _Info) { Renderer_->Off(); });
    }   

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent-jumping-landing-dust-anim");

        Renderer_->CreateMetaAnimation(
            "penitent-jumping-landing-dust-anim",
            {"penitent-jumping-landing-dust-anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        Renderer_->AnimationBindEnd("penitent-jumping-landing-dust-anim",
                                    [&](const FrameAnimation_DESC& _Info) { Renderer_->Off(); });
    }

    Renderer_->SetPivot(PIVOTMODE::METABOT);
}

void MoveEffect::Update(float _DeltaTime) {}

void MoveEffect::End() {}
