#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/CoreMinimal.h>
#include "Inventory.h"

class LeftTopUI;
class PlayerUI : public GameEngineActor
{
    friend class Penitent;

public:
    PlayerUI();
    ~PlayerUI();

    PlayerUI(const PlayerUI& _Other)                = delete;
    PlayerUI(PlayerUI&& _Other) noexcept            = delete;
    PlayerUI& operator=(const PlayerUI& _Other)     = delete;
    PlayerUI& operator=(PlayerUI&& _Other) noexcept = delete;

    void SetTear(int Value);

    void UseFlask(int _Index);

    void FillFlask(int _Index);

    void Damage();

    void PlayerDeathStart(const StateInfo& _Info);
    void PlayerDeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void PlayerDeathEnd(const StateInfo& _Info);

    void BossDeathStart(const StateInfo& _Info);
    void BossDeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void BossDeathEnd(const StateInfo& _Info);

    void FinalBossDeathStart(const StateInfo& _Info);
    void FinalBossDeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void FinalBossDeathEnd(const StateInfo& _Info);

    void BehindScreenStart(const StateInfo& _Info);
    void BehindScreenUpdate(float _DeltaTime, const StateInfo& _Info);
    void BehindScreenEnd(const StateInfo& _Info);

    inline void SetRespawnLevelName(const std::string& _Name) { RespawnLevelName_ = _Name; }

    void UIAllOn();

    void UIAllOff();

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
    GameEngineStateManager ScreenState_;

    LeftTopUI* BarFrame_;

    Inventory* Inventory_;

    std::vector<GameEngineUIRenderer*> Flasks_;

    GameEngineUIRenderer* TearFrame_;

    GameEngineUIRenderer* ScreenRenderer_;
    GameEngineUIRenderer* BackRenderer_;

    std::vector<GameEngineUIRenderer*> TearRenderers_;

    std::string RespawnLevelName_;

    LeftTopUI* HPBar_;
    LeftTopUI* MPBar_;

    bool IsReverse_;

    float Alpha_;
    float BackAlpha_;

    float ScreenTime_;
};
