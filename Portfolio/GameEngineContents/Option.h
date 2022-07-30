#pragma once
#include "GameEngineCore/GameEngineLevel.h"

class Option : public GameEngineLevel
{
public:
	Option();
	~Option();

	Option(const Option& _Other) = delete;
	Option(Option&& _Other) noexcept = delete;
	Option& operator=(const Option& _Other) = delete;
	Option& operator=(Option&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
};

