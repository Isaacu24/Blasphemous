#pragma once
#include "StageBase.h"

class Stage04 : public StageBase
{
public:
    Stage04();
    ~Stage04();

    Stage04(const Stage04& _Other)                = delete;
    Stage04(Stage04&& _Other) noexcept            = delete;
    Stage04& operator=(const Stage04& _Other)     = delete;
    Stage04& operator=(Stage04&& _Other) noexcept = delete;

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
    class ElderBrother*   ElderBrother_;

    void PlayerCameraMove(float _DeltaTime);
};
