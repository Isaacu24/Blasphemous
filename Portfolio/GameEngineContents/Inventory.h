#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class InventoryType
{
	RosaryBeads, //����
	Relics, //����
	QuestItem, //����Ʈ ������
	MeaCulpaHearts, //�޾� ���� ����
	Prayers, //�⵵
	Abilities, //�ɷ�
	Collectibles //����ǰ
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

