#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Title : public GameEngineLevel
{
public:
	Title();
	~Title();

	Title(const Title& _Other) = delete;
	Title(Title&& _Other) noexcept = delete;
	Title& operator=(const Title& _Other) = delete;
	Title& operator=(Title&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

