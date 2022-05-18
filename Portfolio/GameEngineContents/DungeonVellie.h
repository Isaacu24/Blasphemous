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
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

