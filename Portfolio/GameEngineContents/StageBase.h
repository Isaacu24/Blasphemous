#pragma once
#include "PenitentGuilt.h"
#include <GameEngineCore/GameEngineLevel.h>

enum class STAGEFLOW
{
    NORMAL,
    BOSSAPPEAR,
    BOSSCOMBAT,
    BOSSDEAD
};

class Penitent;
class MonsterBase;
class BossMonster;
class LoadingActor;
class PenitentGuilt;
class CutScenePlayer;
class GameEngineCollision;
class StageBase : public GameEngineLevel
{
public:
    StageBase();
    ~StageBase() = 0;

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

    GameEngineActor*      Stage_;
    LoadingActor*         LoadingActor_;
    CutScenePlayer*       CutScenePlayer_;
    GameEngineSoundPlayer StageSoundPlayer_;

    Penitent*      Penitent_;
    PenitentGuilt* Guilt_;

    BossMonster*            BossMonster_;
    std::list<MonsterBase*> MonsterList_;

    GameEngineTextureRenderer*        ColMap_;
    std::vector<GameEngineCollision*> DangleColiders_;

    float4 CurPos_;
    float4 PrevPos_;

    float4 PlayerLeftPos_;
    float4 PlayerRightPos_;

    int ShakeCount_;
    int MaxShakeCount_;

    float CameraZPos_;
    float CameraOffset_;
    float ShakeTime_;

    float ForceX_;
    float ForceY_;

    bool IsLeftExit_;
    bool IsRightExit_;
    bool IsShaking_;
    bool IsChangeCameraPos_;
    bool IsOneWayShaking_;
    bool IsLoadingEnd_;

    virtual void SettingStage() = 0;
    virtual void SettingMonster(){};
    virtual void SettingLedge(){};
    virtual void StageFlowUpdate(float _DeltaTime){};

private:
};
