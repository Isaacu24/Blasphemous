#include "PreCompile.h"
#include "Inventory.h"

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

    Cursor_ = CreateComponent<GameEngineUIRenderer>();
    Cursor_->CreateFrameAnimationCutTexture("ItemCursorAlt", {"ItemCursorAlt.png", 0, 15, 0.1f, true});
    Cursor_->ChangeFrameAnimation("ItemCursorAlt");
    Cursor_->GetTransform().SetWorldScale({55, 55});
    Cursor_->GetTransform().SetWorldPosition({-425, -115, static_cast<int>(UIORDER::Inventory)});

    GameEngineInput::GetInst()->CreateButton("InventoryLeftButton", GAMEPAD_LEFT_SHOULDER);
    GameEngineInput::GetInst()->CreateButton("InventoryRightButton", GAMEPAD_RIGHT_SHOULDER);

    GameEngineInput::GetInst()->CreateKey("InventoryLeftKey", VK_LEFT);
    GameEngineInput::GetInst()->CreateKey("InventoryRightKey", VK_RIGHT);

    GameEngineInput::GetInst()->CreateKey("CursorLeftKey", 'A');
    GameEngineInput::GetInst()->CreateKey("CursorRightKey", 'D');
    GameEngineInput::GetInst()->CreateKey("CursorDownKey", 'S');
    GameEngineInput::GetInst()->CreateKey("CursorUpKey", 'W');
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

    GameEngineDebug::OutPutString("CursorPosX : " + std::to_string(Cursor_->GetTransform().GetWorldPosition().x));
    GameEngineDebug::OutPutString("CursorPosY : " + std::to_string(Cursor_->GetTransform().GetWorldPosition().y));
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
            Cursor_->GetTransform().SetWorldPosition({-425, -115, 0.0f});
            break;
        case 2:
            InventoryType_ = InventoryType::Relics;
            CursorPos_     = 1;
            MaxSlotIndex_  = 7;
            LineSlotCount_ = 7;
            Cursor_->GetTransform().SetWorldPosition({-425, -115, 0.0f});
            break;
        case 3:
            InventoryType_ = InventoryType::QuestItem;
            CursorPos_     = 1;
            LineSlotCount_ = 5;
            MaxSlotIndex_  = 35;
            Cursor_->GetTransform().SetWorldPosition({135, 180, 0.0f});
            break;
        case 4:
            InventoryType_ = InventoryType::MeaCulpaHearts;
            CursorPos_     = 1;
            LineSlotCount_ = 8;
            MaxSlotIndex_  = 11;
            Cursor_->GetTransform().SetWorldPosition({-425, -115, 0.0f});
            break;
        case 5:
            InventoryType_ = InventoryType::Prayers;
            CursorPos_     = 1;
            MaxSlotIndex_  = 17;
            Cursor_->GetTransform().SetWorldPosition({-425, -115, -0.1f});
            break;
        case 6:
            InventoryType_ = InventoryType::Abilities;
            CursorPos_     = 1;
            Cursor_->GetTransform().SetWorldPosition({-425, -115, 1.0f});
            break;
        case 7:
            InventoryType_ = InventoryType::Collectibles;
            CursorPos_     = 1;
            MaxSlotIndex_  = 24;
            Cursor_->GetTransform().SetWorldPosition({-425, -115, -0.1f});
            break;

        default:
            InventoryType_ = InventoryType::RosaryBeads;
            CursorPos_     = 1;
            Cursor_->GetTransform().SetWorldPosition({-425, -115, 0.0f});
            break;
    }

    ChangeInventory();
}

void Inventory::ChangeInventory()
{
    switch (InventoryType_)
    {
        case InventoryType::RosaryBeads:
            InventoryRenderer_->SetTexture("Inventory_0.png");
            break;
        case InventoryType::Relics:
            InventoryRenderer_->SetTexture("Inventory_1.png");
            break;
        case InventoryType::QuestItem:
            InventoryRenderer_->SetTexture("Inventory_2.png");
            break;
        case InventoryType::MeaCulpaHearts:
            InventoryRenderer_->SetTexture("Inventory_3.png");
            break;
        case InventoryType::Prayers:
            InventoryRenderer_->SetTexture("Inventory_4.png");
            break;
        case InventoryType::Abilities:
            InventoryRenderer_->SetTexture("Inventory_5.png");
            Cursor_->GetTransform().SetWorldPosition({0, 0, 100.0f});
            break;
        case InventoryType::Collectibles:
            InventoryRenderer_->SetTexture("Inventory_6.png");
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

        Cursor_->GetTransform().SetWorldMove({-68, 0, 0});

        LineBreakCuror();
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("CursorRightKey"))
    {
        if (MaxSlotIndex_ < CursorPos_ + 1)
        {
            return;
        }

        ++CursorPos_;

        Cursor_->GetTransform().SetWorldMove({68, 0, 0});

        LineBreakCuror();
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("CursorDownKey"))
    {
        if (MaxSlotIndex_ < CursorPos_ + LineSlotCount_)
        {
            return;
        }

        CursorPos_ += LineSlotCount_;
        Cursor_->GetTransform().SetWorldMove({0, -60, 0});

        LineBreakCuror();
    }

    else if (true == GameEngineInput::GetInst()->IsDownKey("CursorUpKey"))
    {
        if (0 >= CursorPos_ - LineSlotCount_)
        {
            return;
        }

        CursorPos_ -= LineSlotCount_;
        Cursor_->GetTransform().SetWorldMove({0, 60, 0});

        LineBreakCuror();
    }
}

void Inventory::LineBreakCuror()
{
    if (InventoryType_ == InventoryType::QuestItem)
    {
        switch (CursorPos_)
        {
            case 5:
                Cursor_->GetTransform().SetWorldPosition({407, 180, 0.0f});
                break;
            case 6:
                Cursor_->GetTransform().SetWorldPosition({135, 112, 0.0f});
                break;

            case 10:
                Cursor_->GetTransform().SetWorldPosition({407, 112, 0.0f});
                break;
            case 11:
                Cursor_->GetTransform().SetWorldPosition({135, 46, 0.0f});
                break;
                    
            case 15:
                Cursor_->GetTransform().SetWorldPosition({407, 46, 0.0f});
                break;
            case 16:
                Cursor_->GetTransform().SetWorldPosition({135, 0, 0.0f});
                break;

            case 20:
                Cursor_->GetTransform().SetWorldPosition({407, 0, 0.0f});
                break;
            case 21:
                Cursor_->GetTransform().SetWorldPosition({135, -66, 0.0f});
                break;

            case 25:
                Cursor_->GetTransform().SetWorldPosition({407, -66, 0.0f});
                break;
            case 26:
                Cursor_->GetTransform().SetWorldPosition({135, -131, 0.0f});
                break;

            case 30:
                Cursor_->GetTransform().SetWorldPosition({407, -131, 0.0f});
                break;
            case 31:
                Cursor_->GetTransform().SetWorldPosition({135, -188, 0.0f});
                break;
        }
    }

    else
    {
        switch (CursorPos_)
        {
            case 8:
                Cursor_->GetTransform().SetWorldPosition({51, -115, 0.0f});
                break;
            case 9:
                Cursor_->GetTransform().SetWorldPosition({-425, -170, 0.0f});
                break;
            case 16:
                Cursor_->GetTransform().SetWorldPosition({51, -170, 0.0f});
                break;
            case 17:
                Cursor_->GetTransform().SetWorldPosition({-425, -235, 0.0f});
                break;
            default:
                break;
        }
    }
}
