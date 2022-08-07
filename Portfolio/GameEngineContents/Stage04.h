#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "StageBase.h"

class Stage04 : public GameEngineLevel, public StageBase
{
public:
	Stage04();
	~Stage04();

	Stage04(const Stage04& _Other) = delete;
	Stage04(Stage04&& _Other) noexcept = delete;
	Stage04& operator=(const Stage04& _Other) = delete;
	Stage04& operator=(Stage04&& _Other) noexcept = delete;

	void BossStateCheck();

protected:
	void SettingStage() override;
	void SettingMonster() override;

	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void OnEvent() override;
	void OffEvent() override;

private:
	class ElderBrother* ElderBrother_;
	class BossUI* BossUI_;

	bool IsEvent_;

	void PlayerCameraMove();
};

