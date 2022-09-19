#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MetaTextureRenderer.h"

enum class ItemType
{
    RosaryBeads,     //묵주
    Relics,          //유물
    QuestItem,       //퀘스트 아이템
    MeaCulpaHearts,  //메아 쿨파 심장
    Prayers,         //기도
    Abilities,       //능력
    Collectibles     //수집품
};

//스킬도 포함
class Item : public GameEngineActor
{
    friend class Inventory;

public:
    Item();
    ~Item();

    Item(const Item& _Other)                = delete;
    Item(Item&& _Other) noexcept            = delete;
    Item& operator=(const Item& _Other)     = delete;
    Item& operator=(Item&& _Other) noexcept = delete;

    inline void SetFrameRenderer(size_t _Index)
    {
        FrameRenderer_->On();
        FrameRenderer_->SetTexture("items-icons-spritesheet.png", _Index);
        FrameRenderer_->ScaleToCutTexture(_Index);
    }

    inline void SetIconRenderer(size_t _Index)
    {
        IconRenderer_->On();
        IconRenderer_->SetTexture("items-icons-spritesheet.png", _Index);
        IconRenderer_->ScaleToCutTexture(_Index);
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    MetaTextureRenderer* IconRenderer_;
    MetaTextureRenderer* FrameRenderer_;

    ItemType MyType_;

    GameEngineFontRenderer* ItemName_;
    GameEngineFontRenderer* ItemInfo_;

    size_t CurIndex_;
};
