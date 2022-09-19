#pragma once
#include "StageBase.h"

class Stage11 : public StageBase
{
public:
    Stage11();
    ~Stage11();

    Stage11(const Stage11& _Other)                = delete;
    Stage11(Stage11&& _Other) noexcept            = delete;
    Stage11& operator=(const Stage11& _Other)     = delete;
    Stage11& operator=(Stage11&& _Other) noexcept = delete;

protected:
    void SettingStage() override;

    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
    class Door* IronDoor_;
};
