#include "PreCompile.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemSlot.h"

Inventory::Inventory()
    : InventoryType_(InventoryType::RosaryBeads)
    , InventoryRenderer_(nullptr)
    , InventoryIndex_(1)
    , CursorPos_(1)
    , MaxSlotIndex_(24)
    , LineSlotCount_(8)
{}

Inventory::~Inventory() {}

void Inventory::Start()
{
    InventoryRenderer_ = CreateComponent<GameEngineUIRenderer>();
    InventoryRenderer_->SetTexture("Inventory_0.png");
    InventoryRenderer_->ScaleToTexture();
    InventoryRenderer_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(UIORDER::Inventory)});

    GameEngineInput::GetInst()->CreateButton("InventoryLeftButton", GAMEPAD_LEFT_SHOULDER);
    GameEngineInput::GetInst()->CreateButton("InventoryRightButton", GAMEPAD_RIGHT_SHOULDER);

    GameEngineInput::GetInst()->CreateKey("InventoryLeftKey", VK_LEFT);
    GameEngineInput::GetInst()->CreateKey("InventoryRightKey", VK_RIGHT);

    GameEngineInput::GetInst()->CreateKey("CursorLeftKey", 'A');
    GameEngineInput::GetInst()->CreateKey("CursorRightKey", 'D');
    GameEngineInput::GetInst()->CreateKey("CursorDownKey", 'S');
    GameEngineInput::GetInst()->CreateKey("CursorUpKey", 'W');

    ItemSlotLists_.resize(6);

    ItemSlotLists_[static_cast<int>(InventoryType::RosaryBeads)].resize(24);

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::RosaryBeads)].size(); i++)
    {
        float XPos_ = -435.f;
        float YPos_ = -40.f;

        size_t OffsetX = i;
        size_t OffsetY = 1;

        ItemSlot* Slot = GetLevel()->CreateActor<ItemSlot>();
        Slot->SetFrameRenderer(2);
        Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});

        if (8 <= i)
        {
            OffsetX = i - 8;
            OffsetY = 2;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        if (16 <= i)
        {
            OffsetX = i - 16;
            OffsetY = 3;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        ItemSlotLists_[static_cast<int>(InventoryType::RosaryBeads)][i] = Slot;
        Slot->Off();
    }

    ItemSlotLists_[static_cast<int>(InventoryType::Relics)].resize(7);

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::Relics)].size(); i++)
    {
        float XPos_ = -435.f;
        float YPos_ = -40.f;

        size_t OffsetX = i;
        size_t OffsetY = 1;

        ItemSlot* Slot = GetLevel()->CreateActor<ItemSlot>();
        Slot->SetFrameRenderer(2);
        Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});

        ItemSlotLists_[static_cast<int>(InventoryType::Relics)][i] = Slot;
        Slot->Off();
    }

    ItemSlotLists_[static_cast<int>(InventoryType::QuestItem)].resize(35);

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::QuestItem)].size(); i++)
    {
        float XPos_ = 130.f;
        float YPos_ = 215.f;

        size_t OffsetX = i;
        size_t OffsetY = 1;

        ItemSlot* Slot = GetLevel()->CreateActor<ItemSlot>();
        Slot->SetFrameRenderer(2);
        Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});

        if (5 <= i)
        {
            OffsetX = i - 5;
            OffsetY = 1;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        if (10 <= i)
        {
            OffsetX = i - 10;
            OffsetY = 2;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        if (15 <= i)
        {
            OffsetX = i - 15;
            OffsetY = 3;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        if (20 <= i)
        {
            OffsetX = i - 20;
            OffsetY = 4;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        if (25 <= i)
        {
            OffsetX = i - 25;
            OffsetY = 5;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        if (30 <= i)
        {
            OffsetX = i - 30;
            OffsetY = 6;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        if (35 <= i)
        {
            OffsetX = i - 35;
            OffsetY = 7;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        ItemSlotLists_[static_cast<int>(InventoryType::QuestItem)][i] = Slot;
        Slot->Off();
    }

    ItemSlotLists_[static_cast<int>(InventoryType::MeaCulpaHearts)].resize(11);

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::MeaCulpaHearts)].size(); i++)
    {
        float XPos_ = -435.f;
        float YPos_ = -40.f;

        size_t OffsetX = i;
        size_t OffsetY = 1;

        ItemSlot* Slot = GetLevel()->CreateActor<ItemSlot>();
        Slot->SetFrameRenderer(2);
        Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});

        if (8 <= i)
        {
            OffsetX = i - 8;
            OffsetY = 2;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        ItemSlotLists_[static_cast<int>(InventoryType::MeaCulpaHearts)][i] = Slot;
        Slot->Off();
    }

    ItemSlotLists_[static_cast<int>(InventoryType::Prayers)].resize(17);

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::Prayers)].size(); i++)
    {
        float XPos_ = -435.f;
        float YPos_ = -40.f;

        size_t OffsetX = i;
        size_t OffsetY = 1;

        ItemSlot* Slot = GetLevel()->CreateActor<ItemSlot>();
        Slot->SetFrameRenderer(2);
        Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});

        if (8 <= i)
        {
            OffsetX = i - 8;
            OffsetY = 2;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        if (16 <= i)
        {
            OffsetX = i - 16;
            OffsetY = 3;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        ItemSlotLists_[static_cast<int>(InventoryType::Prayers)][i] = Slot;
        Slot->Off();
    }

    ItemSlotLists_[static_cast<int>(InventoryType::Collectibles) - 1].resize(24);

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::Collectibles) - 1].size(); i++)
    {
        float XPos_ = -435.f;
        float YPos_ = -40.f;

        size_t OffsetX = i;
        size_t OffsetY = 1;

        ItemSlot* Slot = GetLevel()->CreateActor<ItemSlot>();
        Slot->SetFrameRenderer(2);
        Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});

        if (8 <= i)
        {
            OffsetX = i - 8;
            OffsetY = 2;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        if (16 <= i)
        {
            OffsetX = i - 16;
            OffsetY = 3;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        if (24 <= i)
        {
            OffsetX = i - 24;
            OffsetY = 4;
            Slot->GetTransform().SetWorldPosition(float4{XPos_ + (OffsetX * 70.f), YPos_ - (OffsetY * 65.f)});
        }

        ItemSlotLists_[static_cast<int>(InventoryType::Collectibles) - 1][i] = Slot;
        Slot->Off();
    }
}

void Inventory::Update(float _DeltaTime)
{
    if (GameEngineInput::GetInst()->IsDownButton("InventoryLeftButton")
        || GameEngineInput::GetInst()->IsDownKey("InventoryLeftKey"))
    {
        if (1 == InventoryIndex_)
        {
            InventoryIndex_ = 7;
            ChangeInventoryIndex();
            return;
        }

        --InventoryIndex_;
        ChangeInventoryIndex();
    }

    if (GameEngineInput::GetInst()->IsDownButton("InventoryRightButton")
        || GameEngineInput::GetInst()->IsDownKey("InventoryRightKey"))
    {
        if (7 == InventoryIndex_)
        {
            InventoryIndex_ = 1;
            ChangeInventoryIndex();
            return;
        }

        ++InventoryIndex_;
        ChangeInventoryIndex();
    }

    CursorMove();

    GameEngineDebug::OutPutString("CursorPos : " + std::to_string(CursorPos_));
}

void Inventory::End() {}


void Inventory::ChangeInventoryIndex()
{
    switch (InventoryIndex_)
    {
        case 1:
            InventoryType_ = InventoryType::RosaryBeads;
            CursorPos_     = 1;
            LineSlotCount_ = 8;
            MaxSlotIndex_  = 24;
            break;

        case 2:
            InventoryType_ = InventoryType::Relics;
            CursorPos_     = 1;
            MaxSlotIndex_  = 7;
            LineSlotCount_ = 7;
            break;

        case 3:
            InventoryType_ = InventoryType::QuestItem;
            CursorPos_     = 1;
            LineSlotCount_ = 5;
            MaxSlotIndex_  = 35;
            break;

        case 4:
            InventoryType_ = InventoryType::MeaCulpaHearts;
            CursorPos_     = 1;
            LineSlotCount_ = 8;
            MaxSlotIndex_  = 11;
            break;

        case 5:
            InventoryType_ = InventoryType::Prayers;
            CursorPos_     = 1;
            MaxSlotIndex_  = 17;
            break;

        case 6:
            InventoryType_ = InventoryType::Abilities;
            CursorPos_     = 1;
            break;

        case 7:
            InventoryType_ = InventoryType::Collectibles;
            CursorPos_     = 1;
            MaxSlotIndex_  = 24;
            break;

        default:
            InventoryType_ = InventoryType::RosaryBeads;
            CursorPos_     = 1;
            break;
    }

    Reset();
    ChangeInventory();
}

void Inventory::ChangeInventory()
{
    switch (InventoryType_)
    {
        case InventoryType::RosaryBeads:
            InventoryRenderer_->SetTexture("Inventory_0.png");

            for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::RosaryBeads)].size(); i++)
            {
                ItemSlotLists_[static_cast<int>(InventoryType::RosaryBeads)][i]->On();
            }
            break;

        case InventoryType::Relics:
            InventoryRenderer_->SetTexture("Inventory_1.png");

            for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::Relics)].size(); i++)
            {
                ItemSlotLists_[static_cast<int>(InventoryType::Relics)][i]->On();
            }
            break;

        case InventoryType::QuestItem:
            InventoryRenderer_->SetTexture("Inventory_2.png");

            for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::QuestItem)].size(); i++)
            {
                ItemSlotLists_[static_cast<int>(InventoryType::QuestItem)][i]->On();
            }
            break;

        case InventoryType::MeaCulpaHearts:
            InventoryRenderer_->SetTexture("Inventory_3.png");

            for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::MeaCulpaHearts)].size(); i++)
            {
                ItemSlotLists_[static_cast<int>(InventoryType::MeaCulpaHearts)][i]->On();
            }
            break;

        case InventoryType::Prayers:
            InventoryRenderer_->SetTexture("Inventory_4.png");

            for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::Prayers)].size(); i++)
            {
                ItemSlotLists_[static_cast<int>(InventoryType::Prayers)][i]->On();
            }
            break;

        case InventoryType::Abilities:
            InventoryRenderer_->SetTexture("Inventory_5.png");
            break;

        case InventoryType::Collectibles:
            InventoryRenderer_->SetTexture("Inventory_6.png");

            for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::Collectibles) - 1].size(); i++)
            {
                ItemSlotLists_[static_cast<int>(InventoryType::Collectibles) - 1][i]->On();
            }
            break;
    }
}

void Inventory::CursorMove()
{
    if (true == GameEngineInput::GetInst()->IsDownKey("CursorLeftKey"))
    {
        if (0 >= CursorPos_ - 1)
        {
            return;
        }

        --CursorPos_;
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("CursorRightKey"))
    {
        if (MaxSlotIndex_ < CursorPos_ + 1)
        {
            return;
        }

        ++CursorPos_;
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("CursorDownKey"))
    {
        if (MaxSlotIndex_ < CursorPos_ + LineSlotCount_)
        {
            return;
        }

        CursorPos_ += LineSlotCount_;
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("CursorUpKey"))
    {
        if (0 >= CursorPos_ - LineSlotCount_)
        {
            return;
        }

        CursorPos_ -= LineSlotCount_;
    }
}

void Inventory::Reset()
{
    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::RosaryBeads)].size(); i++)
    {
        ItemSlotLists_[static_cast<int>(InventoryType::RosaryBeads)][i]->Off();
    }

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::Relics)].size(); i++)
    {
        ItemSlotLists_[static_cast<int>(InventoryType::Relics)][i]->Off();
    }

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::QuestItem)].size(); i++)
    {
        ItemSlotLists_[static_cast<int>(InventoryType::QuestItem)][i]->Off();
    }

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::MeaCulpaHearts)].size(); i++)
    {
        ItemSlotLists_[static_cast<int>(InventoryType::MeaCulpaHearts)][i]->Off();
    }

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::Prayers)].size(); i++)
    {
        ItemSlotLists_[static_cast<int>(InventoryType::Prayers)][i]->Off();
    }

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::Collectibles) - 1].size(); i++)
    {
        ItemSlotLists_[static_cast<int>(InventoryType::Collectibles) - 1][i]->Off();
    }

    for (size_t i = 0; i < ItemSlotLists_[static_cast<int>(InventoryType::RosaryBeads)].size(); i++)
    {
        ItemSlotLists_[static_cast<int>(InventoryType::RosaryBeads)][i]->Off();
    }
}

void Inventory::OnEvent() { ChangeInventory(); }

void Inventory::OffEvent() { Reset(); }
