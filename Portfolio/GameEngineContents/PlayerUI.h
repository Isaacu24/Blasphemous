#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PlayerUI : public GameEngineActor
{
public:
	PlayerUI();
	~PlayerUI();

	PlayerUI(const PlayerUI& _Other) = delete;
	PlayerUI(PlayerUI&& _Other) noexcept = delete;
	PlayerUI& operator=(const PlayerUI& _Other) = delete;
	PlayerUI& operator=(PlayerUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	class LeftTopUI* BarFrame_;

	std::vector<GameEngineUIRenderer*> Flasks_;

	GameEngineUIRenderer* BalanceFrame_;

	LeftTopUI* HPBar_;
	LeftTopUI* MPBar_;

};


