#include "PreCompile.h"
#include "Item.h"

Item::Item() 
{
}

Item::~Item() 
{
}

void Item::Start() 
{
    GetTransform().SetWorldScale({2.f, 2.f, 1});

    IconRenderer_  = CreateComponent<MetaTextureRenderer>();
    IconRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
    IconRenderer_->Off();

    FrameRenderer_ = CreateComponent<MetaTextureRenderer>();
    FrameRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
    FrameRenderer_->Off();

    ItemName_ = CreateComponent<GameEngineFontRenderer>();
    ItemName_->ChangeCamera(CAMERAORDER::UICAMERA);

    ItemInfo_ = CreateComponent<GameEngineFontRenderer>();
    ItemInfo_->ChangeCamera(CAMERAORDER::UICAMERA);
}

void Item::Update(float _DeltaTime) 
{

}

void Item::End() 
{

}
