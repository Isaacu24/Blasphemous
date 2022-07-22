#include "GameEngineRes.h"

class GameEngineMeta : public GameEngineRes<GameEngineMeta>
{
	friend class GameEngineMetaParser;

public:
	GameEngineMeta();
	~GameEngineMeta();

	GameEngineMeta(const GameEngineMeta& _Other) = delete;
	GameEngineMeta(GameEngineMeta&& _Other) noexcept = delete;
	GameEngineMeta& operator=(const GameEngineMeta& _Other) = delete;
	GameEngineMeta& operator=(GameEngineMeta&& _Other) noexcept = delete;

private:
	std::filesystem::directory_iterator Metafile_;

	int X_;
	int Y_;
	int Width_;
	int Height_;

	float4 Pivot_;

public:
	static GameEngineMeta* Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static GameEngineMeta* Load(const std::string& _Path, const std::string& _Name);

	void MetaFileLoad(const std::string& _Path);
	
private:
	int GetX()
	{
		return X_;
	}

	int GetY()
	{
		return Y_;
	}

	int GetWidth()
	{
		return Width_;
	}

	int GetHeight()
	{
		return Height_;
	}

	const float4& GetPivot()
	{
		return Pivot_;
	}

};
