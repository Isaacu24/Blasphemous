#pragma once
#include "StageBase.h"

class Stage30 : public StageBase
{
public:
	Stage30();
	~Stage30();

	Stage30(const Stage30& _Other) = delete;
	Stage30(Stage30&& _Other) noexcept = delete;
	Stage30& operator=(const Stage30& _Other) = delete;
	Stage30& operator=(Stage30&& _Other) noexcept = delete;

protected:
	void SettingStage() override;

	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

    void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
};

