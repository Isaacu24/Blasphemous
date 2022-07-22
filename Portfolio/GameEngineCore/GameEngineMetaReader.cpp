#include "PreCompile.h"
#include "GameEngineMetaReader.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineMetaReader::GameEngineMetaReader()
{
}

GameEngineMetaReader::~GameEngineMetaReader()
{
}

void GameEngineMetaReader::ReadMetafile(const GameEngineMeta& _Meta)
{

}

int GameEngineMetaReader::ReadToX()
{
	return 0;
}

int GameEngineMetaReader::ReadToY()
{
	return 0;
}

int GameEngineMetaReader::ReadToHeight()
{
	return 0;
}

int GameEngineMetaReader::ReadToWidth()
{
	return 0;
}

float4 GameEngineMetaReader::ReadToPivot()
{
	return float4();
}

const GameEngineMeta* GameEngineMetaReader::Find(const std::string& _Name)
{
	std::string Name = GameEngineString::ToUpperReturn(_Name);

	if (Metafiles_.end() == Metafiles_.find(Name))
	{
		MsgBoxAssert("존재하지 않는 메타 애니메이션을 찾으려고 했습니다.");
		return;
	}

	std::map<std::string, GameEngineMeta*>::iterator FideIter = Metafiles_.find(Name);

	return FideIter->second;
}

int GameEngineMeta::GetX()
{
	return 0;
}

int GameEngineMeta::GetY()
{
	return 0;
}

int GameEngineMeta::GetWidth()
{
	return 0;
}

int GameEngineMeta::GetHeight()
{
	return 0;
}

float4 GameEngineMeta::GetPivot()
{
	return float4();
}
