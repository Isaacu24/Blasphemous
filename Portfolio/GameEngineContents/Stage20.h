#pragma once
#include "StageBase.h"

class Stage20 : public StageBase
{
public:
    Stage20();
    ~Stage20();

    Stage20(const Stage20& _Other)                = delete;
    Stage20(Stage20&& _Other) noexcept            = delete;
    Stage20& operator=(const Stage20& _Other)     = delete;
    Stage20& operator=(Stage20&& _Other) noexcept = delete;

protected:
    void SettingStage() override;
    void SettingMonster() override;

    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void LevelStartEvent() override;
    void LevelEndEvent() override;

    void NormallyStart(const StateInfo& _Info) override;
    void NormallyUpdate(float _DeltaTime, const StateInfo& _Info) override;
    void NormallyEnd(const StateInfo& _Info) override;

    void BossAppearStart(const StateInfo& _Info) override;
    void BossAppearUpdate(float _DeltaTime, const StateInfo& _Info) override;
    void BossAppearEnd(const StateInfo& _Info) override;

    void BossCombatStart(const StateInfo& _Info) override;
    void BossCombatUpdate(float _DeltaTime, const StateInfo& _Info) override;
    void BossCombatEnd(const StateInfo& _Info) override;

    void BossDeadStart(const StateInfo& _Info) override;
    void BossDeadUpdate(float _DeltaTime, const StateInfo& _Info) override;
    void BossDeadEnd(const StateInfo& _Info) override;

private:
    class Pope* Pope_;

    float ChangeTime_;

    float4 PlayerReturnPos_;

    class LineUIActor* LineUIActor_;

    GameEngineActor*           UIActor_;
    GameEngineTextureRenderer* ReturnKey_;

    void PlayerCameraMove(float _DeltaTime);

    float MassageTime_;

    bool IsBGMStop_;
};
