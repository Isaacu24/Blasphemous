#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class OptionType
{
	Game,
	Sound,
	Acces
};

class OptionActor : public GameEngineActor
{
public:
	OptionActor();
	~OptionActor();

	OptionActor(const OptionActor& _Other) = delete;
	OptionActor(OptionActor&& _Other) noexcept = delete;
	OptionActor& operator=(const OptionActor& _Other) = delete;
	OptionActor& operator=(OptionActor&& _Other) noexcept = delete;

	void UpdateOptionMenu();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	OptionType CurrentState_;

	class GameEngineTextureRenderer* Option_;

	GameEngineTextureRenderer* Selecter_;

	GameEngineTextureRenderer* Game_;
	GameEngineTextureRenderer* Sound_;
	GameEngineTextureRenderer* Acces_;

	int OptionIndex_;

private:
	void ChangeIndex();
};

