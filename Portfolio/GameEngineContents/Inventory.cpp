#include "PreCompile.h"
#include "Inventory.h"

Inventory::Inventory()
	: InventoryType_(InventoryType::RosaryBeads)
	, InventoryRenderer_(nullptr)
	, InventoryIndex_(1)
{
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	InventoryRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	InventoryRenderer_->GetTransform().SetWorldScale({1280, 800});
	InventoryRenderer_->SetTexture("Inventory_0.png");

	GameEngineInput::GetInst()->CreateButton("InventoryLeftButton", GAMEPAD_LEFT_SHOULDER);
	GameEngineInput::GetInst()->CreateButton("InventoryRightButton", GAMEPAD_RIGHT_SHOULDER);

	GameEngineInput::GetInst()->CreateKey("InventoryLeftKey", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("InventoryRightKey", VK_RIGHT);
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
		break;
	case 2:
		InventoryType_ = InventoryType::Relics;
		break;
	case 3:
		InventoryType_ = InventoryType::QuestItem;
		break;
	case 4:
		InventoryType_ = InventoryType::MeaCulpaHearts;
		break;
	case 5:
		InventoryType_ = InventoryType::Prayers;
		break;
	case 6:
		InventoryType_ = InventoryType::Abilities;
		break;
	case 7:
		InventoryType_ = InventoryType::Collectibles;
		break;

	default:
		InventoryType_ = InventoryType::Collectibles;
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
