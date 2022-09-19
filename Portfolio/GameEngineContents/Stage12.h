#pragma once
#include "StageBase.h"

class Stage12 : public StageBase
{
public:
    Stage12();
    ~Stage12();

    Stage12(const Stage12& _Other)                = delete;
    Stage12(Stage12&& _Other) noexcept            = delete;
    Stage12& operator=(const Stage12& _Other)     = delete;
    Stage12& operator=(Stage12&& _Other) noexcept = delete;

protected:
    void SettingStage() override;

    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
};
