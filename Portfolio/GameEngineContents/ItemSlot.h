#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MetaTextureRenderer.h"
#include "Item.h"

class ItemSlot : public GameEngineActor
{
    friend class Inventory;

public:
    ItemSlot();
    ~ItemSlot();

    ItemSlot(const ItemSlot& _Other)                = delete;
    ItemSlot(ItemSlot&& _Other) noexcept            = delete;
    ItemSlot& operator=(const ItemSlot& _Other)     = delete;
    ItemSlot& operator=(ItemSlot&& _Other) noexcept = delete;

    void SetItemInfo(const ItemInfo& _Info);
  
    inline const ItemInfo& GetItemInfo() { return ItemInfo_; }

    inline void SetFrameRenderer(size_t _Index)
    {
        FrameRenderer_->SetTexture("items-icons-spritesheet.png", static_cast<int>(_Index));
        FrameRenderer_->ScaleToCutTexture(static_cast<int>(_Index));
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void OnEvent() override;
    void OffEvent() override;

private:
    MetaTextureRenderer* SelectRenderer_;
    MetaTextureRenderer* FrameRenderer_;
    MetaTextureRenderer* IconRenderer_;

    ItemInfo             ItemInfo_;
};
