#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MetaTextureRenderer.h"

class Item;
class ItemSlot : public GameEngineActor
{
public:
    ItemSlot();
    ~ItemSlot();

    ItemSlot(const ItemSlot& _Other)                = delete;
    ItemSlot(ItemSlot&& _Other) noexcept            = delete;
    ItemSlot& operator=(const ItemSlot& _Other)     = delete;
    ItemSlot& operator=(ItemSlot&& _Other) noexcept = delete;

    inline void SetItem(Item* _Item)
    {
        if (nullptr != _Item)
        {
            SlotItem_ = _Item;
        }
    }

    inline void SetFrameRenderer(size_t _Index)
    {
        FrameRenderer_->On();
        FrameRenderer_->SetTexture("items-icons-spritesheet.png", _Index);
        FrameRenderer_->ScaleToCutTexture(_Index);
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    MetaTextureRenderer* FrameRenderer_;
    Item*                SlotItem_;
};
