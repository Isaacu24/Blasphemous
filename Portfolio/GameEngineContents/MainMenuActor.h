#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class MainMenuActor : public GameEngineActor
{
public:
	MainMenuActor();
	~MainMenuActor();

	MainMenuActor(const MainMenuActor& _Other) = delete;
	MainMenuActor(MainMenuActor&& _Other) noexcept = delete;
	MainMenuActor& operator=(const MainMenuActor& _Other) = delete;
	MainMenuActor& operator=(MainMenuActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Background_;
		;

};

