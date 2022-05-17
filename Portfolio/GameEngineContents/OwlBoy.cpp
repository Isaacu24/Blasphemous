#include "OwlBoy.h"
#include "Title.h"
#include "DungeonVellie.h"
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineDirectory.h>

#pragma comment(lib, "GameEngineBase.lib")

OwlBoy::OwlBoy() 
{
}

OwlBoy::~OwlBoy() 
{
}

void OwlBoy::UserStart()
{
	CreateLevel<Title>("Title");
	CreateLevel<DungeonVellie>("DungeonVellie");

	ChangeLevel("Title");
}

void OwlBoy::UserUpdate(float _DeltaTime)
{
}

void OwlBoy::UserEnd()
{
}

void OwlBoy::ResourceInit()
{
	//GameEngineDirectory ResourecesDir;
	//ResourecesDir.MoveParent("Portfolio");
	//ResourecesDir.Move("APIResources");
	//ResourecesDir.Move("Level");
	//ResourecesDir.Move("GO_IMAGES");

	//std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

	//for (size_t i = 0; i < AllImageFileList.size(); i++)
	//{
	//	GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	//};
}
