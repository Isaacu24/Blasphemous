#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

//두번째 교황
class Pontiff
    : public GameEngineActor
    , public BossMonster
{
public:
    Pontiff();
    ~Pontiff();

    Pontiff(const Pontiff& _Other)                = delete;
    Pontiff(Pontiff&& _Other) noexcept            = delete;
    Pontiff& operator=(const Pontiff& _Other)     = delete;
    Pontiff& operator=(Pontiff&& _Other) noexcept = delete;

    void AppearStart(const StateInfo& _Info);
    void AppearUpdate(float _DeltaTime, const StateInfo& _Info);
    void AppearEnd(const StateInfo& _Info);

    void OpeningStart(const StateInfo& _Info);
    void OpeningUpdate(float _DeltaTime, const StateInfo& _Info);
    void OpeningEnd(const StateInfo& _Info);

    void OpenIdleStart(const StateInfo& _Info);
    void OpenIdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void OpenIdleEnd(const StateInfo& _Info);

    void ClosingStart(const StateInfo& _Info);
    void ClosingUpdate(float _DeltaTime, const StateInfo& _Info);
    void ClosingEnd(const StateInfo& _Info);

    void CloseIdleStart(const StateInfo& _Info);
    void CloseIdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void CloseIdleEnd(const StateInfo& _Info);

    void DeathStart(const StateInfo& _Info);
    void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void DeathEnd(const StateInfo& _Info);

    const std::string GetState() 
    { 
        return State_.GetCurStateStateName(); 
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class GameEngineTextureRenderer* Helmet_;
    GameEngineTextureRenderer*       Body_;
    GameEngineTextureRenderer*       Face_;
    GameEngineTextureRenderer*       MainBody_;

    GameEngineCollision* Collider_;

    class GiantSword* GiantSword_;

    class SymbolEffect* Symbol_;

    class FireBallSpawner*       FireBallSpawner_;
    class ToxicCloudSpawner*     ToxicCloudSpawner_;
    class LightiningBoltSpawner* LightiningBoltSpawner_;
    class MagicMissileSpawner*   MagicMissileSpawner_;

    int AscensionSpeed_;

    float Time_;

    void OpenAnimationEnd(const FrameAnimation_DESC& _Info) { State_.ChangeState("OpenIdle"); }

    void OpenIdleAnimationEnd(const FrameAnimation_DESC& _Info) { State_.ChangeState("Closing"); }

    void CloseAnimationEnd(const FrameAnimation_DESC& _Info) { State_.ChangeState("CloseIdle"); }

    void CloseIdleAnimationEnd(const FrameAnimation_DESC& _Info) 
    { 
        State_.ChangeState("Opening"); 
    }
};


//플랫폼 생성기 클래스도 만들어야 함.
//그건 플랫폼스포너(혹은 스테이지. 근데 아마 따로 클래스를 만드는 편이 좋다.)가 할 일.
