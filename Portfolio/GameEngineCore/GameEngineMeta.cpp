#include "PreCompile.h"
#include "GameEngineMeta.h"

GameEngineMeta::GameEngineMeta() 
{
}

GameEngineMeta::~GameEngineMeta() 
{
}

GameEngineMeta* GameEngineMeta::Load(const std::string& _Path, const std::string& _Name)
{
	GameEngineMeta* NewRes = CreateResName(_Name);
	NewRes->MetaFileLoad(_Path);
	return NewRes;
}

void GameEngineMeta::MetaFileLoad(const std::string& _Path)
{
	std::filesystem::directory_iterator DirIter(_Path);
	Metafile_ = DirIter;
}
