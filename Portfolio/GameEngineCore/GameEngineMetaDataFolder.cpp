#include "PreCompile.h"
#include "GameEngineMetaDataFolder.h"
#include "GameEngineMetaData.h"

GameEngineMetaDataFolder::GameEngineMetaDataFolder()
{
}

GameEngineMetaDataFolder::~GameEngineMetaDataFolder()
{
}


GameEngineMetaDataFolder* GameEngineMetaDataFolder::Load(const std::string& _Path)
{
	return Load(_Path, GameEnginePath::GetFileName(_Path));
}

GameEngineMetaDataFolder* GameEngineMetaDataFolder::Load(const std::string& _Path, const std::string& _Name)
{
	GameEngineMetaDataFolder* NewMeta = CreateResName(_Name);
	NewMeta->LoadMetaDataFolder(_Path);
	return NewMeta;
}

void GameEngineMetaDataFolder::LoadMetaDataFolder(const std::string& _Path)
{
	GameEngineDirectory Dir = GameEngineDirectory(_Path);

	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineMetaData* MetaData = new GameEngineMetaData();
		MetaData->LoadMetaData(Files[i].GetFullPath());
		MetaDatas.push_back(MetaData);
	}
}