#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "BossMonster.h"

enum class SPELLTYPE
{
    FIREBALL,
    TOXICCLOUD,
    LIGHTININGBOLT,
    MAGICMISSILE,
    ANGUISHBEAM,
    NONE
};

//두번째 교황
class Pontiff
    : public GameEngineActor
    , public BossMonster
{
    friend class GiantSword;

public:
    Pontiff();
    ~Pontiff();

    Pontiff(const Pontiff& _Other)                = delete;
    Pontiff(Pontiff&& _Other) noexcept            = delete;
    Pontiff& operator=(const Pontiff& _Other)     = delete;
    Pontiff& operator=(Pontiff&& _Other) noexcept = delete;

    inline bool GetLose() { return IsLose_; }

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

    const std::string GetState() { return State_.GetCurStateStateName(); }

    void SpellCast(float _DeltaTime);

    void FireBall(float _DeltaTime);
    void ToxicCloud();
    void LightiningBolt();
    void Magicmissile();
    void AnguishBeam();

    void CreateSpawner();
        
    
    void SetTarget(GameEngineActor* _Target) { Target_ = _Target; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    SPELLTYPE CurType_;
    SPELLTYPE PervType_;

    class GameEngineTextureRenderer* Helmet_;
    GameEngineTextureRenderer*       Body_;
    GameEngineTextureRenderer*       Face_;

    class PontiffMainBody* MainBody_;

    class GiantSword* GiantSword_;

    class SymbolEffect* Symbol_[2];

    class FireBallSpawner*       FireBallSpawner_[6];
    class ToxicCloudSpawner*     ToxicCloudSpawner_;
    class LightiningBoltSpawner* LightiningBoltSpawner_;
    class MagicMissileSpawner*   MagicMissileSpawner_;
    class AnguishBeamSpawner*    AnguishBeamSpawner_;

    class PlatformSpawner* PlatformSpawner_;

    GameEngineRandom Random_;

    GameEngineActor* Target_;

    bool IsLose_;

    bool IsAscension_;

    float AscensionSpeed_;

    float Time_;
    float SpellTime_;

    int SpellCount_;
    
    bool IsSpellCastStart_;
};


//플랫폼 생성기 클래스도 만들어야 함.
//그건 플랫폼스포너(혹은 스테이지. 근데 아마 따로 클래스를 만드는 편이 좋다.)가 할 일.
