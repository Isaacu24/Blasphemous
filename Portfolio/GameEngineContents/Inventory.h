#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Item.h"

enum class InventoryType
{
    RosaryBeads,     //묵주
    Relics,          //유물
    QuestItem,       //퀘스트 아이템
    MeaCulpaHearts,  //메아 쿨파 심장
    Prayers,         //기도
    Abilities,       //능력
    Collectibles     //수집품
};

class GameEngineTextureRenderer;
class Inventory : public GameEngineActor
{
public:
    Inventory();
    ~Inventory();

    Inventory(const Inventory& _Other)                = delete;
    Inventory(Inventory&& _Other) noexcept            = delete;
    Inventory& operator=(const Inventory& _Other)     = delete;
    Inventory& operator=(Inventory&& _Other) noexcept = delete;

    void PushBackItem(const ItemInfo& _Info);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void ChangeInventoryIndex();

    void ChangeInventory();

    void CursorMove();

    void CursorReset();

    void AllSlotOff();

    void OnEvent() override;
    void OffEvent() override;

private:
    InventoryType InventoryType_;

    GameEngineUIRenderer* InventoryRenderer_;

    GameEngineUIRenderer* IconRenderer_;
    class GameEngineFontRenderer* ItemName_;
    GameEngineFontRenderer* ItemDesc_;

    int InventoryIndex_;

    std::vector<std::vector<class ItemSlot*>> ItemSlotLists_;

    int CursorPos_;

    int MaxSlotIndex_;

    int LineSlotCount_;
};
    