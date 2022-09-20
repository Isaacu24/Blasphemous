#include "PreCompile.h"
#include "ItemSlot.h"

ItemSlot::ItemSlot() 
{
}

ItemSlot::~ItemSlot() 
{
}

void ItemSlot::Start() 
{
    GetTransform().SetWorldScale({2.f, 2.f, 1});

    FrameRenderer_ = CreateComponent<MetaTextureRenderer>();
    FrameRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
    FrameRenderer_->Off();
}

void ItemSlot::Update(float _DeltaTime) {}

void ItemSlot::End() {}
