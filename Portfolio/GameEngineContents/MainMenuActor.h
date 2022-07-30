#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class MainMenuType
{
	Pilgrimage,
	Option_,
	Exit_
};

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
	GameEngineTextureRenderer* BigPetal_;
	GameEngineTextureRenderer* Petal_;
	GameEngineTextureRenderer* Crisanta_;

	GameEngineTextureRenderer* Pilgrimage_;
	GameEngineTextureRenderer* Option_;
	GameEngineTextureRenderer* Exit_;

	GameEngineTextureRenderer* Selecter_;

	MainMenuType CurrentType_;
	int MenuIndex_;

	float BackgroundTime_;
	float PetalTime_;
	float BigPetalTime_;
	float CrisantaTime_;

	int BackgroundFrame_;
	int PetalFrame_;
	int BigPetalFrame_;
	int CrisantaFrame_;

private:
	void BackgroundAnimation(float _DeltaTime);
	void PetalAnimation(float _DeltaTime);
	void BigPetalAnimation(float _DeltaTime);
	void CrisantaAnimation(float _DeltaTime);

	void ChangeMenuIndex();
	void ChangeMenuSelect();

	void SelectMenu();
};

