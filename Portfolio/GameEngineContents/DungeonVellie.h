#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class DungeonVellie : public GameEngineLevel
{
public:
	DungeonVellie();
	~DungeonVellie();

	DungeonVellie(const DungeonVellie& _Other) = delete;
	DungeonVellie(DungeonVellie&& _Other) noexcept = delete;
	DungeonVellie& operator=(const DungeonVellie& _Other) = delete;
	DungeonVellie& operator=(DungeonVellie&& _Other) noexcept = delete;

protected:
	void UserStart() override;
	void UserUpdate(float _DeltaTime) override;
	void UserEnd() override;

private:

};

