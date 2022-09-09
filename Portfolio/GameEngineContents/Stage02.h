#pragma once
#include "StageBase.h"

class Stage02 : public StageBase
{
public:
	Stage02();
	~Stage02();

	Stage02(const Stage02& _Other) = delete;
	Stage02(Stage02&& _Other) noexcept = delete;
	Stage02& operator=(const Stage02& _Other) = delete;
	Stage02& operator=(Stage02&& _Other) noexcept = delete;

protected:
	void SettingStage() override;
	void SettingMonster() override;
    void SettingLedge() override;

	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

    void LevelStartEvent() override;
    void LevelEndEvent() override;


private:
};

