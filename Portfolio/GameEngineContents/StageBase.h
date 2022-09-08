#pragma once
#include "PenitentGuilt.h"

enum class STAGEFLOW
{
    NORMAL,
    BOSSAPPEAR,
    BOSSCOMBAT,
    BOSSDEAD,
    STAGECLEAR
};

class GameEngineCollision;
class StageBase
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

protected:
    STAGEFLOW CurrentFlow_;

    GameEngineActor* Stage_;

    float4 CurPos_;
    float4 PrevPos_;

    GameEngineTextureRenderer* ColMap_;

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

    class PenitentGuilt* Guilt_;

    float AfterParallaxZ;
    float AfterParallax1Z;
    float AfterParallax2Z;
    float AfterParallax3Z;
    float AfterParallax4Z;
    float AfterParallax5Z;

    float AfterLayerZ;
    float AfterLayer1Z;
    float AfterLayer2Z;
    float AfterLayer3Z;
    float AfterLayer4Z;
    float AfterLayer5Z;

    float DoorZ;

    float PlayerEffectZ;
    float PlayerZ;
    float PlayerBehindEffectZ;
    float NPCZ;
    float PlatformZ;
    float BossMonsterEffectZ;
    float BossMonsterZ;
    float MonsterZ;
    float ObjectZ;
    float TileZ;

    float BeforeLayerZ;
    float BeforeLayer1Z;
    float BeforeLayer2Z;
    float BeforeLayer3Z;
    float BeforeLayer4Z;
    float BeforeLayer5Z;

    float BeforeParallaxZ;
    float BeforeParallax1Z;
    float BeforeParallax2Z;
    float BeforeParallax3Z;
    float BeforeParallax4Z;
    float BeforeParallax5Z;

    float ColmapZ;


private:
};

