#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "StageBase.h"

class Stage20 : public GameEngineLevel, public StageBase
{
public:
	Stage20();
	~Stage20();

	Stage20(const Stage20& _Other) = delete;
	Stage20(Stage20&& _Other) noexcept = delete;
	Stage20& operator=(const Stage20& _Other) = delete;
	Stage20& operator=(Stage20&& _Other) noexcept = delete;

protected:
	void SettingStage() override;
	void SettingMonster() override;

	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

    void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
    class Pope* Pope_;

	float ChangeTime_;

	void PlayerCameraMove();
};

