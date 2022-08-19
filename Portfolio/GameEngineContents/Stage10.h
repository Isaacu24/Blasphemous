#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "StageBase.h"

class Stage10 : public GameEngineLevel, public StageBase
{
public:
	Stage10();
	~Stage10();

	Stage10(const Stage10& _Other) = delete;
	Stage10(Stage10&& _Other) noexcept = delete;
	Stage10& operator=(const Stage10& _Other) = delete;
	Stage10& operator=(Stage10&& _Other) noexcept = delete;

protected:
	void SettingStage() override;
    void SettingLedge() override;

	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void OnEvent() override;
	void OffEvent() override;

private:
};

