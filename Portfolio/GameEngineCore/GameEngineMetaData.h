#pragma once
#include "GameEngineRes.h"

class GameEngineMetaData: public GameEngineRes<GameEngineMetaData>
{
public:
	GameEngineMetaData();
	~GameEngineMetaData();

	GameEngineMetaData(const GameEngineMetaData& _Other) = delete;
	GameEngineMetaData(GameEngineMetaData&& _Other) noexcept = delete;
	GameEngineMetaData& operator=(const GameEngineMetaData& _Other) = delete;
	GameEngineMetaData& operator=(GameEngineMetaData&& _Other) noexcept = delete;

	static GameEngineMetaData* Load(const std::string& _Path);

	static GameEngineMetaData* Load(const std::string& _Path, const std::string& _Name);

	void LoadMetaData(const std::string& _Path);

protected:

private:
	std::string Data;
};

