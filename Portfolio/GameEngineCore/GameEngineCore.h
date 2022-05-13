#pragma once
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

class GameEngineCore
{
public:
	template<typename CoreType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		CoreType Core;
		WindowCreate(Core.GetWindowTitle(), &Core);
	}


protected:
	virtual std::string GetWindowTitle() 
	{ 
		return "MainWindow"; 
	}

	virtual void UserGameStart() = 0;
	virtual void UserGameUpdate() = 0;
	virtual void UserGameEnd() = 0;

	GameEngineCore();
	~GameEngineCore();

	template<typename LevelType>
	void LevelCreate(const std::string& _Name) //레벨 생성
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	}

private:
	static void WindowCreate(const std::string& _Name, GameEngineCore* _UserCore); //윈도우 생성
	static void CoreStart(GameEngineCore* _UserCore); // 프로그램 시작
	static void CoreUpdate(GameEngineCore* _UserCore); // 프로그램 업데이트
	static void CoreEnd(GameEngineCore* _UserCore); // 프로그램 종료

	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;


};

