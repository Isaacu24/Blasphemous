#include "PreCompile.h"
#include "Fly.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

Fly::Fly() 
{
}

Fly::~Fly() 
{
}

void Fly::Start() 
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ashplatform_32x32_deactivev_brightbackground");

        MetaRenderer_->CreateMetaAnimation(
            "ashplatform_32x32_deactivev_brightbackground",
            {"ashplatform_32x32_deactivev_brightbackground.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.06f, true},
            Data);
    }

    MetaRenderer_->ChangeMetaAnimation("ashplatform_32x32_deactivev_brightbackground");
    MetaRenderer_->GetColorData().MulColor = float4{4.0f, 4.0f, 4.0f, 1.0f};
}

void Fly::Update(float _DeltaTime) {}

void Fly::End() {}
