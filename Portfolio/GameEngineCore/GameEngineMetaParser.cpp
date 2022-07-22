#include "PreCompile.h"
#include "GameEngineMetaParser.h"
#include <GameEngineBase/GameEngineString.h>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <iostream>

GameEngineMetaParser::GameEngineMetaParser()
{
}

GameEngineMetaParser::~GameEngineMetaParser()
{
}

void GameEngineMetaParser::ReadMetafile(GameEngineMeta& _Meta)
{
	//std::stringstream ReadStr_{ _Meta.GetMetafile() };
	//std::string Token_;

	//while (std::getline(ReadStr_, Token_, '\n'))
	//{

	//}
}

int GameEngineMetaParser::ReadToX()
{
	return 0;
}

int GameEngineMetaParser::ReadToY()
{
	return 0;
}

int GameEngineMetaParser::ReadToHeight()
{
	return 0;
}

int GameEngineMetaParser::ReadToWidth()
{
	return 0;
}

float4 GameEngineMetaParser::ReadToPivot()
{
	return float4();
}

const GameEngineMeta* GameEngineMetaParser::Find(const std::string& _Name)
{
	std::string Name = GameEngineString::ToUpperReturn(_Name);

	if (Metafiles_.end() == Metafiles_.find(Name))
	{
		MsgBoxAssert("존재하지 않는 메타 정보를 찾으려고 했습니다.");
		return nullptr;
	}

	std::map<std::string, GameEngineMeta*>::iterator FideIter = Metafiles_.find(Name);

	return FideIter->second;
}