#include "PreCompile.h"
#include "GameEngineMetaData.h"


GameEngineMetaData::GameEngineMetaData()
{
}

GameEngineMetaData::~GameEngineMetaData()
{
}

GameEngineMetaData* GameEngineMetaData::Load(const std::string& _Path)
{
	return Load(_Path, GameEnginePath::GetFileName(_Path));
}

GameEngineMetaData* GameEngineMetaData::Load(const std::string& _Path, const std::string& _Name)
{
	GameEngineMetaData* NewMeta = CreateResName(_Name);
	NewMeta->LoadMetaData(_Path);
	return NewMeta;
}

void GameEngineMetaData::LoadMetaData(const std::string& _Path)
{
	GameEngineFile InputFile{ _Path };

	InputFile.Open(OpenMode::Read, FileMode::Text);
	std::string Data = InputFile.GetString();
}


