#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Stage04 : public GameEngineLevel
{
public:
	Stage04();
	~Stage04();

	Stage04(const Stage04& _Other) = delete;
	Stage04(Stage04&& _Other) noexcept = delete;
	Stage04& operator=(const Stage04& _Other) = delete;
	Stage04& operator=(Stage04&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

