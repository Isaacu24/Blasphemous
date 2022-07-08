#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class MainMenu : public GameEngineLevel
{
public:
	MainMenu();
	~MainMenu();

	MainMenu(const MainMenu& _Other) = delete;
	MainMenu(MainMenu&& _Other) noexcept = delete;
	MainMenu& operator=(const MainMenu& _Other) = delete;
	MainMenu& operator=(MainMenu&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

