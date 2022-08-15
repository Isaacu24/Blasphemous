#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Inventory.h"

class LeftTopUI;
class PlayerUI : public GameEngineActor
{
	friend class Penitent;

public:
	PlayerUI();
	~PlayerUI();

	PlayerUI(const PlayerUI& _Other) = delete;
	PlayerUI(PlayerUI&& _Other) noexcept = delete;
	PlayerUI& operator=(const PlayerUI& _Other) = delete;
	PlayerUI& operator=(PlayerUI&& _Other) noexcept = delete;

	void SetTear(int Value);
	void UseFlask(int _Index);

	void Damage();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	LeftTopUI* BarFrame_;

	Inventory* Inventory_;

	std::vector<GameEngineUIRenderer*> Flasks_;

	GameEngineUIRenderer* TearFrame_;

	std::vector<GameEngineUIRenderer*> TearRenderers_;

	LeftTopUI* HPBar_;
	LeftTopUI* MPBar_;

};


