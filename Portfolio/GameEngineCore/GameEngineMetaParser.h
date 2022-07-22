#pragma once
#include <map>
#include <string>
#include "GameEngineMeta.h"

class GameEngineMetaParser
{

public:
	GameEngineMetaParser();
	~GameEngineMetaParser();

	GameEngineMetaParser(const GameEngineMetaParser& _Other) = delete;
	GameEngineMetaParser(GameEngineMetaParser&& _Other) noexcept = delete;
	GameEngineMetaParser& operator=(const GameEngineMetaParser& _Other) = delete;
	GameEngineMetaParser& operator=(GameEngineMetaParser&& _Other) noexcept = delete;

	void ReadMetafile(GameEngineMeta& _Meta);

	int ReadToX();

	int ReadToY();

	int ReadToHeight();

	int ReadToWidth();

	float4 ReadToPivot();

	const GameEngineMeta* Find(const std::string& _Name);



protected:

private:
	std::map<std::string, GameEngineMeta*> Metafiles_;
};

