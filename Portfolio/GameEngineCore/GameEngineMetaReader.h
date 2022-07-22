#pragma once
#include <map>
#include <string>

class GameEngineMeta
{
private:
	std::string Metafile_;

	int X_;
	int Y_;
	int Width_;
	int Height_;

	float4 Pivot_;

public:
	int GetX();

	int GetY();

	int GetWidth();

	int GetHeight();

	float4 GetPivot();
};

class GameEngineMetaReader
{
	friend GameEngineMeta;

public:
	GameEngineMetaReader();
	~GameEngineMetaReader();

	GameEngineMetaReader(const GameEngineMetaReader& _Other) = delete;
	GameEngineMetaReader(GameEngineMetaReader&& _Other) noexcept = delete;
	GameEngineMetaReader& operator=(const GameEngineMetaReader& _Other) = delete;
	GameEngineMetaReader& operator=(GameEngineMetaReader&& _Other) noexcept = delete;

	void ReadMetafile(const GameEngineMeta& _Meta);

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

