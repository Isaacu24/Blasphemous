#include "OwlBoy.h"
#include "Title.h"
#include "DungeonVellie.h"

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
