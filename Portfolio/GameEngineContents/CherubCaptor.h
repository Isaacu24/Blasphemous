#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineStateManager.h>

class CherubCaptor : public GameEngineActor
{
public:
    static int Count_;

public:
    CherubCaptor();
    ~CherubCaptor();

    CherubCaptor(const CherubCaptor& _Other)                = delete;
    CherubCaptor(CherubCaptor&& _Other) noexcept            = delete;
    CherubCaptor& operator=(const CherubCaptor& _Other)     = delete;
    CherubCaptor& operator=(CherubCaptor&& _Other) noexcept = delete;

    void SetPatrolPosX(float _StartPosX, float _EndPosX)
    {
        IsPatrolX_  = true;
        PatrolStart_ = true;

        StartPos_.x = _StartPosX;
        EndPos_.x   = _EndPosX;
    }

    void SetPatrolPosY(float _StartPosY, float _EndPosY)
    {
        IsPatrolY_  = true;
        PatrolStart_ = true;

        StartPos_.y = _StartPosY;
        EndPos_.y   = _EndPosY;
    }

    void PatrolXMove(float _DeltaTime);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void IdleEnd(const StateInfo& _Info);

    void DeathStart(const StateInfo& _Info);
    void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void DeathEnd(const StateInfo& _Info);

private:
    GameEngineStateManager State_;

    class MetaTextureRenderer* MetaRenderer_;
    class GameEngineCollision* Collider_;

    float4 StartPos_;
    float4 EndPos_;

    bool IsPatrolX_;
    bool IsPatrolY_;

    bool PatrolStart_;
    bool PatrolEnd_;

    float Alpha_;
};