#include "PreCompile.h"
#include "PlatformSpawner.h"
#include "Platform.h"

PlatformSpawner::PlatformSpawner() 
{
}

PlatformSpawner::~PlatformSpawner() 
{
}

void PlatformSpawner::CreateFristPattern(GameEngineLevel* _Level)
{
	_Level->CreateActor<Platform>();
	_Level->CreateActor<Platform>();
	_Level->CreateActor<Platform>();
	_Level->CreateActor<Platform>();
	_Level->CreateActor<Platform>();
}

void PlatformSpawner::CreateSecondPattern(GameEngineLevel* _Level)
{
}

void PlatformSpawner::CreateThirdPattern(GameEngineLevel* _Level)
{
}

void PlatformSpawner::CreateFourthPattern(GameEngineLevel* _Level)
{
}

void PlatformSpawner::CreateFifthPattern(GameEngineLevel* _Level)
{
}
