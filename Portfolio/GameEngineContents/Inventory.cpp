#include "PreCompile.h"
#include "Inventory.h"

Inventory::Inventory()
	: InventoryType_(InventoryType::RosaryBeads)
	, InventoryRenderer_(nullptr)
	, InventoryIndex_(1)
	, CursorPos_(1)
	, MaxSlotIndex_(24)
	, LineSlotCount_(8)
{
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	InventoryRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	InventoryRenderer_->GetTransform().SetWorldScale({ 1280, 800});
	InventoryRenderer_->SetTexture("Inventory_0.png");

	Cursor_ = CreateComponent<GameEngineTextureRenderer>();
	Cursor_->CreateFrameAnimation("ItemCursorAlt", { "ItemCursorAlt.png", 0, 15, 0.1f, true });
	Cursor_->ChangeFrameAnimation("ItemCursorAlt");
	Cursor_->GetTransform().SetWorldScale({ 55, 55 });
	Cursor_->GetTransform().SetWorldPosition({-425, -125, 0.0f});

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

void Inventory::End()
{

}

void Inventory::ChangeInventoryIndex()
{
	switch (InventoryIndex_)
	{
	case 1:
		InventoryType_ = InventoryType::RosaryBeads;
		CursorPos_ = 1;
		LineSlotCount_ = 8;
		MaxSlotIndex_ = 24;
		Cursor_->GetTransform().SetWorldPosition({ -425, -125, 0.0f });
		break;
	case 2:
		InventoryType_ = InventoryType::Relics;
		CursorPos_ = 1;
		MaxSlotIndex_ = 7;
		LineSlotCount_ = 7;
		Cursor_->GetTransform().SetWorldPosition({ -425, -125, 0.0f });
		break;
	case 3:
		InventoryType_ = InventoryType::QuestItem;
		CursorPos_ = 1;
		LineSlotCount_ = 5;
		MaxSlotIndex_ = 35;
		Cursor_->GetTransform().SetWorldPosition({ 135, 190, 0.0f });
		break;
	case 4:
		InventoryType_ = InventoryType::MeaCulpaHearts;
		CursorPos_ = 1;
		LineSlotCount_ = 8;
		MaxSlotIndex_ = 11;
		Cursor_->GetTransform().SetWorldPosition({ -425, -125, 0.0f });
		break;
	case 5:
		InventoryType_ = InventoryType::Prayers;
		CursorPos_ = 1;
		MaxSlotIndex_ = 17;
		Cursor_->GetTransform().SetWorldPosition({ -425, -125, -0.1f });
		break;
	case 6:
		InventoryType_ = InventoryType::Abilities;
		CursorPos_ = 1;
		Cursor_->GetTransform().SetWorldPosition({ -425, -125, 1.0f });
		break;
	case 7:
		InventoryType_ = InventoryType::Collectibles;
		CursorPos_ = 1;
		MaxSlotIndex_ = 24;
		Cursor_->GetTransform().SetWorldPosition({ -425, -125, -0.1f });
		break;

	default:
		InventoryType_ = InventoryType::RosaryBeads;
		CursorPos_ = 1;
		Cursor_->GetTransform().SetWorldPosition({ -425, -125, 0.0f });
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

		Cursor_->GetTransform().SetWorldMove({ 68, 0, 0});

		LineBreakCuror();
	}

	else if (true == GameEngineInput::GetInst()->IsDownKey("CursorDownKey"))
	{
		if (MaxSlotIndex_ < CursorPos_ + LineSlotCount_)
		{
			return;
		}

		CursorPos_ += LineSlotCount_;
		Cursor_->GetTransform().SetWorldMove({ 0, -67, 0 });

		LineBreakCuror();
	}

	else if (true == GameEngineInput::GetInst()->IsDownKey("CursorUpKey"))
	{
		if (0 >= CursorPos_ - LineSlotCount_)
		{
			return;
		}

		CursorPos_ -= LineSlotCount_;
		Cursor_->GetTransform().SetWorldMove({ 0, 67, 0 });

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
			Cursor_->GetTransform().SetWorldPosition({ 407, 190, 0.0f });
			break;
		case 6:
			Cursor_->GetTransform().SetWorldPosition({ 135, 122, 0.0f });
			break;

		case 10:
			Cursor_->GetTransform().SetWorldPosition({ 407, 122, 0.0f });
			break;
		case 11:
			Cursor_->GetTransform().SetWorldPosition({ 135, 56, 0.0f });
			break;

		case 15:
			Cursor_->GetTransform().SetWorldPosition({ 407, 56, 0.0f });
			break;
		case 16:
			Cursor_->GetTransform().SetWorldPosition({ 135, -10, 0.0f });
			break;

		case 20:
			Cursor_->GetTransform().SetWorldPosition({ 407, -10, 0.0f });
			break;
		case 21:
			Cursor_->GetTransform().SetWorldPosition({ 135, -76, 0.0f });
			break;

		case 25:
			Cursor_->GetTransform().SetWorldPosition({ 407, -76, 0.0f });
			break;
		case 26:
			Cursor_->GetTransform().SetWorldPosition({ 135, -141, 0.0f });
			break;

		case 30:
			Cursor_->GetTransform().SetWorldPosition({ 407, -141, 0.0f });
			break;
		case 31:
			Cursor_->GetTransform().SetWorldPosition({ 135, -208, 0.0f });
			break;
		}
	}

	else
	{
		switch (CursorPos_)
		{
		case 8:
			Cursor_->GetTransform().SetWorldPosition({ 51, -125, 0.0f });
			break;
		case 9:
			Cursor_->GetTransform().SetWorldPosition({ -425, -190, 0.0f });
			break;
		case 16:
			Cursor_->GetTransform().SetWorldPosition({ 51, -190, 0.0f });
			break;
		case 17:
			Cursor_->GetTransform().SetWorldPosition({ -425, -255, 0.0f });
			break;
		default:
			break;
		}
	}
}
