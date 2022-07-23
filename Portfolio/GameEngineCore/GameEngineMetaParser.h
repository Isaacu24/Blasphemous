#pragma once

class GameEngineMetaParser
{
public:
	GameEngineMetaParser();
	~GameEngineMetaParser();

	GameEngineMetaParser(const GameEngineMetaParser& _Other) = delete;
	GameEngineMetaParser(GameEngineMetaParser&& _Other) noexcept = delete;
	GameEngineMetaParser& operator=(const GameEngineMetaParser& _Other) = delete;
	GameEngineMetaParser& operator=(GameEngineMetaParser&& _Other) noexcept = delete;

	static void AutoCompile(const std::string& _Path);

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

protected:

private:
};

