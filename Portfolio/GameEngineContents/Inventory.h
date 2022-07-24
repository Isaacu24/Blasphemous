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


class GameEngineTextureRenderer;
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
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void ChangeInventoryIndex();
	void ChangeInventory();

	void CursorMove();

private:
	InventoryType InventoryType_;
	
	GameEngineTextureRenderer* InventoryRenderer_;
	int InventoryIndex_;

	//std::vector<Item> Items_;

	GameEngineTextureRenderer* Cursor_;
	int CursorPos_;
};

