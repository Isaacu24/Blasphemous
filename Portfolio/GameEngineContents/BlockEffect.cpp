#include "PreCompile.h"
#include "BlockEffect.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

BlockEffect::BlockEffect() 
{
}

BlockEffect::~BlockEffect() 
{
}

void BlockEffect::Start() 
{
    Renderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldmaiden_blockEffect");

        Renderer_->CreateMetaAnimation(
            "shieldmaiden_blockEffect",
            {"shieldmaiden_blockEffect.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, true},
            Data);
            
        Renderer_->AnimationBindEnd("shieldmaiden_blockEffect",
                                    [&](const FrameAnimation_DESC& _Info) { Renderer_->Off(); });
    }

    Renderer_->ChangeMetaAnimation("shieldmaiden_blockEffect");
    Renderer_->Off();

    Renderer_->SetPivot(PIVOTMODE::BOT);
}

void BlockEffect::Update(float _DeltaTime) {}

void BlockEffect::End() {}
