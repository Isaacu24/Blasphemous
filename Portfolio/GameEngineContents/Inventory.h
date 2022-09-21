#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Item.h"

enum class InventoryType
{
    RosaryBeads,     //����
    Relics,          //����
    QuestItem,       //����Ʈ ������
    MeaCulpaHearts,  //�޾� ���� ����
    Prayers,         //�⵵
    Abilities,       //�ɷ�
    Collectibles     //����ǰ
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

    void InitEquipSlotList();

    void ChangeInventoryIndex();

    void ChangeInventory();

    void CursorMove();

    void CursorReset();

    //Ŀ���� ������ ������
    void UpdateSlot();
    
    void AllSlotOff();

    void Equip(const ItemInfo& _Info);

    void Release(const ItemInfo& _Info);

    void OnEvent() override;
    void OffEvent() override;

private:
    InventoryType InventoryType_;

    GameEngineUIRenderer* InventoryRenderer_;

    GameEngineUIRenderer* IconRenderer_;

    GameEngineUIRenderer* ButtonRenderer_;
    class GameEngineFontRenderer* ButtonName_;

    GameEngineFontRenderer* ItemName_;
    GameEngineFontRenderer* ItemDesc_;
    
    int InventoryIndex_;

    std::vector<std::vector<class ItemSlot*>> ItemSlotLists_;

    std::vector<std::vector<ItemSlot*>> EquipSlotLists_;

    int CursorPos_;

    int MaxSlotIndex_;

    int LineSlotCount_;
};
    