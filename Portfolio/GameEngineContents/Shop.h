#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "StageBase.h"

class Shop
    : public GameEngineLevel
    , public StageBase
{
public:
    Shop();
    ~Shop();

    Shop(const Shop& _Other)                = delete;
    Shop(Shop&& _Other) noexcept            = delete;
    Shop& operator=(const Shop& _Other)     = delete;
    Shop& operator=(Shop&& _Other) noexcept = delete;

protected:
    void SettingStage() override;

    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
};
