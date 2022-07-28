#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "StageBase.h"

//�÷��̾ ������ �����ϴ� ��������
class Stage01 : public GameEngineLevel, public StageBase
{
public:
	Stage01();
	~Stage01();

	Stage01(const Stage01& _Other) = delete;
	Stage01(Stage01&& _Other) noexcept = delete;
	Stage01& operator=(const Stage01& _Other) = delete;
	Stage01& operator=(Stage01&& _Other) noexcept = delete;

protected:
	void SettingStage() override;

	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void OnEvent() override;
	void OffEvent() override;

private:
};

