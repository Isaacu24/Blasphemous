#pragma once
#include "GameEngineRes.h"

class GameEngineMetaData;
class GameEngineMetaDataFolder : public GameEngineRes<GameEngineMetaDataFolder>
{
public:
	GameEngineMetaDataFolder();
	~GameEngineMetaDataFolder();

	GameEngineMetaDataFolder(const GameEngineMetaDataFolder& _Other) = delete;
	GameEngineMetaDataFolder(GameEngineMetaDataFolder&& _Other) noexcept = delete;
	GameEngineMetaDataFolder& operator=(const GameEngineMetaDataFolder& _Other) = delete;
	GameEngineMetaDataFolder& operator=(GameEngineMetaDataFolder&& _Other) noexcept = delete;

	static GameEngineMetaDataFolder* Load(const std::string& _Path);

	static GameEngineMetaDataFolder* Load(const std::string& _Path, const std::string& _Name);

protected:
	void LoadMetaDataFolder(const std::string& _Path);

private:
	std::vector<GameEngineMetaData*> MetaDatas;
};

