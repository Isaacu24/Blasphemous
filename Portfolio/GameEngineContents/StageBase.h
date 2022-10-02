#pragma once
#include "PenitentGuilt.h"
#include <GameEngineCore/GameEngineLevel.h>

enum class STAGEFLOW
{
    NORMAL,
    BOSSAPPEAR,
    BOSSCOMBAT,
    BOSSDEAD,
    STAGECLEAR
};

class GameEngineCollision;
class StageBase : public GameEngineLevel
{
public:
    StageBase();
    ~StageBase();

    StageBase(const StageBase& _Other)                = delete;
    StageBase(StageBase&& _Other) noexcept            = delete;
    StageBase& operator=(const StageBase& _Other)     = delete;
    StageBase& operator=(StageBase&& _Other) noexcept = delete;

    inline void SetFlow(STAGEFLOW _State) { CurrentFlow_ = _State; }

    inline STAGEFLOW GetFlow() { return CurrentFlow_; }

    void CameraShaking(float _DeltaTime);

    void CameraShakingOneWay(float _DeltaTime);

    inline void SetShake(bool _Value) { IsShaking_ = _Value; }

    inline void SetOneWayShake(bool _Value) { IsOneWayShaking_ = _Value; }

    inline void SetForceX(float _Value) { ForceX_ = _Value; }

    inline void SetForceY(float _Value) { ForceY_ = _Value; }

    inline void SetShakeCount(int _Value) { ShakeCount_ = _Value; }

    inline void SetMaxShakeCount(int _Value) { MaxShakeCount_ = _Value; }

    inline void DestroyGuilt() { Guilt_ = nullptr; }

    inline void SetLoadingEnd(bool _Value) { IsLoadingEnd_ = _Value; }

    inline bool GetLoadingEnd() { return IsLoadingEnd_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void LevelStartEvent() override;
    void LevelEndEvent() override;

    STAGEFLOW CurrentFlow_;

    GameEngineActor* Stage_;

    float4 CurPos_;
    float4 PrevPos_;

    int ShakeCount_;
    int MaxShakeCount_;

    GameEngineTextureRenderer* ColMap_;

    GameEngineSoundPlayer StageSoundPlayer_;

    std::vector<GameEngineCollision*> DangleColiders_;

    class Penitent* Penitent_;

    class BossMonster*            BossMonster_;
    std::list<class MonsterBase*> MonsterList_;

    class LoadingActor* LoadingActor_;

    virtual void SettingStage() = 0;

    virtual void SettingMonster(){};

    virtual void SettingLedge(){};

    virtual void StageFlowUpdate(float _DeltaTime){};

    float4 PlayerLeftPos_;
    float4 PlayerRightPos_;

    bool IsLeftExit_;
    bool IsRightExit_;

    float CameraZPos_;

    bool IsChangeCameraPos_;

    float CameraOffset_;

    float ForceX_;
    float ForceY_;

    class PenitentGuilt* Guilt_;

    float ShakeTime_;

    bool IsShaking_;
    bool IsOneWayShaking_;

    bool IsLoadingEnd_;

private:
};
