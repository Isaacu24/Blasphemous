#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "StageBase.h"

class Stage21
    : public GameEngineLevel
    , public StageBase
{
public:
    Stage21();
    ~Stage21();

    Stage21(const Stage21& _Other)                = delete;
    Stage21(Stage21&& _Other) noexcept            = delete;
    Stage21& operator=(const Stage21& _Other)     = delete;
    Stage21& operator=(Stage21&& _Other) noexcept = delete;

protected:
    void SettingStage() override;
    void SettingMonster() override;

    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

	void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
    class Pontiff* Pontiff_;

    void PlayerCameraMove();
};
