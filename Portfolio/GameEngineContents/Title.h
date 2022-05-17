#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Title : public GameEngineLevel
{
public:
	// constrcuter destructer
	Title();
	~Title();

	// delete Function
	Title(const Title& _Other) = delete;
	Title(Title&& _Other) noexcept = delete;
	Title& operator=(const Title& _Other) = delete;
	Title& operator=(Title&& _Other) noexcept = delete;

protected:
	void UserStart() override;
	void UserUpdate(float _DeltaTime) override;
	void UserEnd() override;


private:

};

