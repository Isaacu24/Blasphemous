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

	inline void SetX(const std::string& _X)
	{
		X_ = _X;
	}

	inline void SetY(const std::string& _Y)
	{
		Y_ = _Y;
	}

	inline void SetWidth(const std::string& _Width)
	{
		Width_ = _Width;
	}

	inline void SetHeight(const std::string& _Height)
	{
		Height_ = _Height;
	}

	inline void SetPivotX(const std::string& _PivotX)
	{
		PivotX_ = _PivotX;
	}

	inline void SetPivotY(const std::string& _PivotY)
	{
		PivotY_ = _PivotY;
	}

private:
	std::string X_;
	std::string Y_;

	std::string Width_;
	std::string Height_;

	std::string PivotX_;
	std::string PivotY_;
};
