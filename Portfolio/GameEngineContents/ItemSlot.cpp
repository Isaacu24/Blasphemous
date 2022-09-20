#include "PreCompile.h"
#include "ItemSlot.h"

ItemSlot::ItemSlot()
    : FrameRenderer_(nullptr)
    , ItemInfo_{}
{}

ItemSlot::~ItemSlot() {}


void ItemSlot::Start()
{
    GetTransform().SetWorldScale({2.f, 2.f, 1});

    FrameRenderer_ = CreateComponent<MetaTextureRenderer>();
    FrameRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
    FrameRenderer_->Off();

    IconRenderer_ = CreateComponent<MetaTextureRenderer>();
    IconRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
    IconRenderer_->Off();

    SelectRenderer_ = CreateComponent<MetaTextureRenderer>();
    SelectRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
    SelectRenderer_->SetTexture("items-icons-spritesheet.png", 0);
    SelectRenderer_->ScaleToCutTexture(0);
    SelectRenderer_->Off();
}

void ItemSlot::Update(float _DeltaTime) {}

void ItemSlot::End() {}


void ItemSlot::SetItemInfo(const ItemInfo& _Info)
{
    ItemInfo_ = _Info;

    IconRenderer_->SetTexture("items-icons-spritesheet.png", ItemInfo_.ItemIndex_);
    IconRenderer_->ScaleToCutTexture(ItemInfo_.ItemIndex_);
}

void ItemSlot::OnEvent()    
{
    if (ItemInfo{} != ItemInfo_)
    {
        IconRenderer_->On();
        FrameRenderer_->SetTexture("items-icons-spritesheet.png", 6);
    }

    FrameRenderer_->On();
}

void ItemSlot::OffEvent()
{
    IconRenderer_->Off();
    FrameRenderer_->Off();
}
