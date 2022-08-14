#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

enum class PontiffState
{
    Opening,
    OpenIdle,
    Closing,
    CloseIdle,
    Death
};

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

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void IdleEnd(const StateInfo& _Info);

    void HitStart(const StateInfo& _Info);
    void HitUpdate(float _DeltaTime, const StateInfo& _Info);
    void HitEnd(const StateInfo& _Info);

    void SpellCastStart(const StateInfo& _Info);
    void SpellCastUpdate(float _DeltaTime, const StateInfo& _Info);
    void SpellCastEnd(const StateInfo& _Info);

    void DeathStart(const StateInfo& _Info);
    void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void DeathEnd(const StateInfo& _Info);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class GameEngineTextureRenderer* Helmet_;
    GameEngineTextureRenderer* Body_;
    GameEngineTextureRenderer* Face_;
    GameEngineTextureRenderer* MainBody_;

    class GiantSword* GiantSword_;

    int AscensionSpeed_;

    float Time_;
};


//플랫폼 생성기 클래스도 만들어야 함.
//그건 플랫폼스포너(혹은 스테이지. 근데 아마 따로 클래스를 만드는 편이 좋다.)가 할 일.
//교황은 몰라도 된다.