#pragma once
#include <GameEngineCore/CoreMinimal.h>

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

    inline void SetHP(int _Value)
    {
        HP_ = _Value;

        if (0 > HP_)
        {
            HP_ = 0;
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

    inline void SetMP(int _Value) { HP_ = _Value; }

    inline int GetMP() { return HP_; }

    inline void SerTear(int _Value) { Tear_ = _Value; }

    inline void SetGround(GameEngineTextureRenderer* _Ground) { ColMap_ = _Ground; }

    inline void ChangeState(const std::string& _State) { State_.ChangeState(_State); }

    inline void SetDamege(int _Damage)
    {
        HP_ -= _Damage;

        if (0 > HP_)
        {
            HP_ = 0;
        }
    }

    inline void SetLastSavePoint(const std::string& _LevelName) { LastSavePoint_ = _LevelName; }

    inline bool GetIsFallDeath() { return IsFallDeath_; }

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

    void DodgeAttackStart(const StateInfo& _Info);
    void DodgeAttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void DodgeAttackEnd(const StateInfo& _Info);

    void VerticalAttackStart(const StateInfo& _Info);
    void VerticalAttackUpdate(float _DeltaTime, const StateInfo& _Info);
    void VerticalAttackEnd(const StateInfo& _Info);

    void KnockBackStart(const StateInfo& _Info);
    void KnockBackUpdate(float _DeltaTime, const StateInfo& _Info);
    void KnockBackEnd(const StateInfo& _Info);

    void KnockUpStart(const StateInfo& _Info);
    void KnockUpUpdate(float _DeltaTime, const StateInfo& _Info);
    void KnockUpEnd(const StateInfo& _Info);

    void ParryingStart(const StateInfo& _Info);
    void ParryingUpdate(float _DeltaTime, const StateInfo& _Info);
    void ParryingEnd(const StateInfo& _Info);

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

    //피격 함수
    bool KnockBack(GameEngineCollision* _This, GameEngineCollision* _Other);
    bool KnockUp(GameEngineCollision* _This, GameEngineCollision* _Other);

    bool Dangle(GameEngineCollision* _This, GameEngineCollision* _Other);  //난간 상호작용

private:
    GameEngineStateManager            State_;
    class PlayerUI*                   PlayerUI_;
    class GravityComponent*           Gravity_;
    class GameEngineCollision*        BodyCollider_;
    GameEngineCollision*              AttackCollider_;  // 공격 범위
    GameEngineCollision*              PlatformCollider_;
    GameEngineCollision*              PlatformUpCollider_;
    std::vector<GameEngineCollision*> DebugColliders_;
    GameEngineTextureRenderer*        ColMap_;
    float4                            ColScale_;
    class GameEngineFontRederer*      Font_;

    SpectrumComponent* Spectrum_;

    MetaTextureRenderer* MetaRenderer_;

    class MoveEffect*   MoveEffect_;
    class AttackEffect* AttackEffect_;
    class HitEffect*    HitEffect_;

    std::string LastSavePoint_;

    int   HP_;
    int   MP_;
    float Speed_;
    float SlideForce_;

    float RealXDir_;

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

    bool IsFallDeath_;
};
