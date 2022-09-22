#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "PlayerUI.h"

enum class EXECUTIONTYPE
{
    None,
    Crosscrawler,
    ShieldMaiden
};

class SpectrumComponent;
class MetaTextureRenderer;
class Penitent : public GameEngineActor
{
private:
    static Penitent* MainPlayer_;

public:
    static Penitent* GetMainPlayer() { return MainPlayer_; }

public:
    Penitent();
    ~Penitent();

    Penitent(const Penitent& _Other)                = delete;
    Penitent(Penitent&& _Other) noexcept            = delete;
    Penitent& operator=(Penitent&& _Other) noexcept = delete;

    int PrevHp_ = 100;

    inline void SetHP(int _Value)
    {
        PrevHp_ = HP_;
        HP_     = _Value;

        if (0 > HP_)
        {
            HP_ = 0;
        }
    }

    inline void SetDamege(int _Damage)
    {
        PrevHp_ = HP_;
        HP_ -= _Damage;

        if (0 > HP_)
        {
            HP_ = 0;
            ChangeState("Death");
        }
    }

    inline int GetHP() { return HP_; }

    inline void PlusHP(int _Value)
    {
        HP_ += _Value;

        if (100 < HP_)
        {
            HP_ = 100;
        }
    }

    inline void SetMP(int _Value) { MP_ = _Value; }

    inline int GetMP() { return MP_; }

    inline void SetTear(int _Value)
    {
        Tear_ = _Value;
        PlayerUI_->SetTear(Tear_);
    }

    inline int GetTear()
    {
        return Tear_;
    }

    inline void PlusTear(int _Value) 
    {
        Tear_ += _Value; 
        PlayerUI_->SetTear(Tear_);
    }

    inline void MinusTear(int _Value) 
    { 
        Tear_ -= _Value; 
        PlayerUI_->SetTear(Tear_);
    }

    inline void SetGround(GameEngineTextureRenderer* _Ground) { ColMap_ = _Ground; }

    inline void ChangeState(const std::string& _State) { State_.ChangeState(_State); }

    inline void SetLastSavePoint(const std::string& _LevelName) { LastSaveLevel_ = _LevelName; }

    inline bool GetIsPlayerDeath() { return IsPlayerDeath_; }

    inline float4 GetLastJumpPosition() { return LastJumpPos_; }

    inline std::string GetPenitentState() { return State_.GetCurStateStateName(); }

    inline void SetReturnToPort(bool _Value) { IsReturnToPort_ = _Value; }

    inline void SetExecutionType(EXECUTIONTYPE _Type) { ExecutionType_ = _Type; }

    inline void ParrySuccess() { IsParrySuccess_ = true; }

    inline bool GetParryOn() { return ParryOn_; }

    void BossKillEventOn();

    void BossKillEventOff();

    void BossDeathUIOn(unsigned int _Key);

    void SetIsFreezeEnd(bool _Value) { IsFreezeEnd_ = _Value; }

    bool GetIsOutDoor() { return IsOutDoor_; }

    void SetIsOutDoor(bool _Value)
    {
        ChangeState("DoorExit");
        IsOutDoor_ = _Value;
    }

    inline PlayerUI* GetPlayerUI() { return PlayerUI_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void SetAnimation();
    void SetPlayerState();

    void GroundCheck();
    void LadderCheck();
    void UphillRoadCheck();

    bool LeftObstacleCheck();
    bool RightObstacleCheck();

    void DeadZoneCheck();

    bool ObjectCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

    void CollisionCheck();

    bool HitEffectCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

    //추락 시 거리 체크: 짧은 높이는 추락 상태가 되지 않음
    bool FallCollisionCheck();

    void FreezeStart(const StateInfo& _Info);
    void FreezeUpdate(float _DeltaTime, const StateInfo& _Info);
    void FreezeEnd(const StateInfo& _Info);

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void IdleEnd(const StateInfo& _Info);

    void MoveStart(const StateInfo& _Info);
    void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
    void MoveEnd(const StateInfo& _Info);

    void JumpStart(const StateInfo& _Info);
    void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
    void JumpEnd(const StateInfo& _Info);

    void FallStart(const StateInfo& _Info);
    void FallUpdate(float _DeltaTime, const StateInfo& _Info);
    void FallEnd(const StateInfo& _Info);

    void LandingStart(const StateInfo& _Info);
    void LandingUpdate(float _DeltaTime, const StateInfo& _Info);
    void LandingEnd(const StateInfo& _Info);

    void CrouchStart(const StateInfo& _Info);
    void CrouchUpdate(float _DeltaTime, const StateInfo& _Info);
    void CrouchEnd(const StateInfo& _Info);

    void SlideStart(const StateInfo& _Info);
    void SlideUpdate(float _DeltaTime, const StateInfo& _Info);
    void SlideEnd(const StateInfo& _Info);

    void DangleStart(const StateInfo& _Info);
    void DangleUpdate(float _DeltaTime, const StateInfo& _Info);
    void DangleEnd(const StateInfo& _Info);

    void LadderClimbStart(const StateInfo& _Info);
    void LadderClimbUpdate(float _DeltaTime, const StateInfo& _Info);
    void LadderClimbEnd(const StateInfo& _Info);

    void AttackStart(const StateInfo& _Info);
    void AttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void AttackEnd(const StateInfo& _Info);

    void JumpAttackStart(const StateInfo& _Info);
    void JumpAttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void JumpAttackEnd(const StateInfo& _Info);

    void SlideAttackStart(const StateInfo& _Info);
    void SlideAttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void SlideAttackEnd(const StateInfo& _Info);

    void VerticalAttackStart(const StateInfo& _Info);
    void VerticalAttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void VerticalAttackEnd(const StateInfo& _Info);

    void PrayAttackStart(const StateInfo& _Info);
    void PrayAttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void PrayAttackEnd(const StateInfo& _Info);

    void RangeAttackStart(const StateInfo& _Info);
    void RangeAttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void RangeAttackEnd(const StateInfo& _Info);

    void JumpRangeAttackStart(const StateInfo& _Info);
    void JumpRangeAttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void JumpRangeAttackEnd(const StateInfo& _Info);

    void ExecutionStart(const StateInfo& _Info);
    void ExecutionUpdate(float _DeltaTime, const StateInfo& _Info);
    void ExecutionEnd(const StateInfo& _Info);

    void KnockBackStart(const StateInfo& _Info);
    void KnockBackUpdate(float _DeltaTime, const StateInfo& _Info);
    void KnockBackEnd(const StateInfo& _Info);

    void KnockUpStart(const StateInfo& _Info);
    void KnockUpUpdate(float _DeltaTime, const StateInfo& _Info);
    void KnockUpEnd(const StateInfo& _Info);

    void ParryingStart(const StateInfo& _Info);
    void ParryingUpdate(float _DeltaTime, const StateInfo& _Info);
    void ParryingEnd(const StateInfo& _Info);

    void ParryingAttackStart(const StateInfo& _Info);
    void ParryingAttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void ParryingAttackEnd(const StateInfo& _Info);

    void RecoveryStart(const StateInfo& _Info);
    void RecoveryUpdate(float _DeltaTime, const StateInfo& _Info);
    void RecoveryEnd(const StateInfo& _Info);

    void ReturnToPortStart(const StateInfo& _Info);
    void ReturnToPortUpdate(float _DeltaTime, const StateInfo& _Info);
    void ReturnToPortEnd(const StateInfo& _Info);

    void DeathStart(const StateInfo& _Info);
    void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void DeathEnd(const StateInfo& _Info);

    void RespawnStart(const StateInfo& _Info);
    void RespawnUpdate(float _DeltaTime, const StateInfo& _Info);
    void RespawnEnd(const StateInfo& _Info);

    void PrayStart(const StateInfo& _Info);
    void PrayUpdate(float _DeltaTime, const StateInfo& _Info);
    void PrayEnd(const StateInfo& _Info);

    void RestPrayStart(const StateInfo& _Info);
    void RestPrayUpdate(float _DeltaTime, const StateInfo& _Info);
    void RestPrayEnd(const StateInfo& _Info);

    void DoorEntranceStart(const StateInfo& _Info);
    void DoorEntranceUpdate(float _DeltaTime, const StateInfo& _Info);
    void DoorEntranceEnd(const StateInfo& _Info);

    void DoorExitStart(const StateInfo& _Info);
    void DoorExitUpdate(float _DeltaTime, const StateInfo& _Info);
    void DoorExitEnd(const StateInfo& _Info);

    //피격 함수
    bool KnockBack(GameEngineCollision* _This, GameEngineCollision* _Other);
    bool KnockUp(GameEngineCollision* _This, GameEngineCollision* _Other);

    bool Dangle(GameEngineCollision* _This, GameEngineCollision* _Other);  //난간 상호작용

    void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
    GameEngineStateManager            State_;
    PlayerUI*                         PlayerUI_;
    class GravityComponent*           Gravity_;
    class GameEngineCollision*        BodyCollider_;
    GameEngineCollision*              AttackCollider_;  // 공격 범위
    GameEngineCollision*              PlatformCollider_;
    GameEngineCollision*              PlatformUpCollider_;
    std::vector<GameEngineCollision*> DebugColliders_;
    GameEngineTextureRenderer*        ColMap_;
    float4                            ColScale_;
    class GameEngineFontRederer*      Font_;

    SpectrumComponent* SlideSpectrum_;
    SpectrumComponent* SlideAttackSpectrum_;

    MetaTextureRenderer* MetaRenderer_;

    class MoveEffect*   MoveEffect_;
    class AttackEffect* AttackEffect_;
    class HitEffect*    HitEffect_;

    EXECUTIONTYPE ExecutionType_;

    std::string LastSaveLevel_;

    std::string OutDoorLevel_;

    int   HP_;
    int   MP_;
    float Speed_;
    float SlideForce_;

    float RealXDir_;
    float KnockBackXDir_;

    float RunTime_;  //달리기 시간 체크

    float4 JumpForce_;

    float FallTime_;

    float4 Dir_;

    float CilmbY_;

    int Tear_;

    int AttackStack_;
    int HitStack_;  //피격 이펙트 분기

    bool IsHit_;      //유효타
    bool IsBossHit_;  //유효타

    bool IsGround_;
    bool IsDangle_;
    bool IsLadder_;

    bool IsOnInventory_;
    bool IsClimbLedge_;

    bool ReadySkill_;  //스킬 준비 여부

    float JumpTime_;
    float SlideTime_;

    std::vector<bool> Flasks_;

    float4 LastJumpPos_;

    bool IsPlayerDeath_;

    class StageBase* CurStage_;

    bool IsShake_;
    bool IsReturnToPort_;
    bool IsParrySuccess_;

    bool ParryOn_;

    bool IsFreezeEnd_;

    bool IsOutDoor_;
};
