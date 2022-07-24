#pragma once
#include <vector>
#include <GameEngineBase/GameEngineNameObject.h>

class GameEngineMetaData : public GameEngineNameObject
{
	friend class GameEngineMetaParser;

public:
	GameEngineMetaData() 
		: X_(0)
		, Y_(0)
		, Width_(0)
		, Height_(0)
		, Pivot_(float4::ZERO)
	{

	}

	~GameEngineMetaData() {}

	GameEngineMetaData(const GameEngineMetaData& _Other) = delete;
	GameEngineMetaData(GameEngineMetaData&& _Other) noexcept = delete;
	GameEngineMetaData& operator=(const GameEngineMetaData& _Other) = delete;
	GameEngineMetaData& operator=(GameEngineMetaData&& _Other) noexcept = delete;

	inline void SetX(int _X)
	{
		X_ = _X;
	}

	inline void SetY(int _Y)
	{
		Y_ = _Y;
	}

	inline void SetWidth(int _Width)
	{
		Width_ = _Width;
	}

	inline void SetHeight(int _Height)
	{
		Height_ = _Height;
	}

	inline void SetPivot(const float4& _Pivot)
	{
		Pivot_ = _Pivot;
	}


private:
	int X_;
	int Y_;

	int Width_;
	int Height_;

	float4 Pivot_;
};


class GameEngineMetaParser
{
private:
	static GameEngineMetaParser* Inst_;

public:
	static GameEngineMetaParser* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	GameEngineMetaParser();
	~GameEngineMetaParser();

	GameEngineMetaParser(const GameEngineMetaParser& _Other) = delete;
	GameEngineMetaParser(GameEngineMetaParser&& _Other) noexcept = delete;
	GameEngineMetaParser& operator=(const GameEngineMetaParser& _Other) = delete;
	GameEngineMetaParser& operator=(GameEngineMetaParser&& _Other) noexcept = delete;

	void AutoCompile(const std::string& _Path);

	static std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
	{
		s.erase(0, s.find_first_not_of(t));
		return s;
	}

	static std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
	{
		s.erase(s.find_last_not_of(t) + 1);
		return s;
	}

	static std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
	{
		return ltrim(rtrim(s, t), t);
	}

	//std::vector<GameEngineMetaData*>& Find(const std::string& _Key);

protected:

private:
	std::map<std::string, std::vector<GameEngineMetaData*>> MetaDatas_;

	std::vector<GameEngineMetaData*> MetaVec_;

	std::vector<std::string> NameVec_;
	std::vector<int> XVec_;
	std::vector<int> YVec_;
	std::vector<int> WidthVec_;
	std::vector<int> HeightVec_;
	std::vector<float4> PivotVec_;

	void Reset();
};


