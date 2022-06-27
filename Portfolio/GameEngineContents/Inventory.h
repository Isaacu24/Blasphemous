#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class InventoryType
{
	RosaryBeads, //묵주
	Relics, //유물
	QuestItem, //퀘스트 아이템
	MeaCulpaHearts, //메아 쿨파 심장
	Prayers, //기도
	Abilities, //능력
	Collectibles //수집품
};

class Inventory : public GameEngineActor
{
public:
	Inventory();
	~Inventory();

	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

protected:

private:
	InventoryType InventoryType_;

};

