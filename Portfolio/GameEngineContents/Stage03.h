#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "StageBase.h"

class Stage03 : public GameEngineLevel, public StageBase
{
public:
	Stage03();
	~Stage03();

	Stage03(const Stage03& _Other) = delete;
	Stage03(Stage03&& _Other) noexcept = delete;
	Stage03& operator=(const Stage03& _Other) = delete;
	Stage03& operator=(Stage03&& _Other) noexcept = delete;

protected:
	void SettingStage() override;

	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
	class PrieDieu* PrieDieu_;
};