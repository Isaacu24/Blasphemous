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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	class GameEngineTextureRenderer* Option_;

	GameEngineTextureRenderer* Game_;
	GameEngineTextureRenderer* Sound_;
	GameEngineTextureRenderer* Acces_;

	int OptionIndex_;

};

