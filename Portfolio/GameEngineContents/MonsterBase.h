#pragma once
#include "PreCompile.h"
#include "BloodSplatters.h"

//몬스터의 기본적인 클래스
class MetaTextureRenderer;
class GameEngineTextureRenderer;
class MonsterBase
{
public:
    MonsterBase();
    ~MonsterBase();

    MonsterBase(const MonsterBase& _Other)                = delete;
    MonsterBase(MonsterBase&& _Other) noexcept            = delete;
    MonsterBase& operator=(const MonsterBase& _Other)     = delete;
    MonsterBase& operator=(MonsterBase&& _Other) noexcept = delete;

    inline void SetHP(float _Value) { HP_ = _Value; }

    inline void MinusHP(float _Value)
    {
        PrevHP_ = HP_;
        HP_ -= _Value;

        if (0 > HP_)
        {
            HP_ = 0;
        }
    }

    inline float PlusHP(float _Value)
    {
        HP_ += _Value;

        if (100 < HP_)
        {
            HP_ = 100;
        }
    }

    inline float GetHP() { return HP_; }

    inline float GetPrevHP() { return PrevHP_; }

    inline void SetTear(int _Value) { Tear_ = _Value; }

    inline int GetTear() { return Tear_; }

    inline void SetSpeed(float _Speed) 
    {
        Speed_ = _Speed; 
    }

    void SetGround(GameEngineTextureRenderer* _Ground);

    inline void ChangeMonsterState(const std::string& _State) { State_.ChangeState(_State); }

    inline void ChangeIdleState(const FrameAnimation_DESC& _Info) { State_.ChangeState("Idle"); }

    //inline MetaTextureRenderer* GetMetaRenderer() { return MetaRenderer_; }

    //inline GameEngineTextureRenderer* GetRenderer() { return Renderer_; }

protected:
    GameEngineStateManager State_;

    BloodSplatters* BloodEffect_;

    MetaTextureRenderer*       MetaRenderer_;
    GameEngineTextureRenderer* Renderer_;
    GameEngineTextureRenderer* ColMap_;

    class GravityComponent* Gravity_;

    class GameEngineCollision* DetectCollider_;  //범위
    GameEngineCollision*       BodyCollider_;    //몸체
    GameEngineCollision*       AttackCollider_;  //공격

    float HP_;
    float PrevHP_;
    int   Att_;
    float Speed_;

    int Tear_;  //플레이어에게 전달한 눈물

    bool IsHit_;

    bool IsGround_;

    bool GroundCheck(int _X, int _Y);
    bool UphillRoadCheck(int _X, int _Y);

    virtual void DamageCheck();

    virtual void DamageCheck(float _Damage);

    virtual void DamageCheck(float _Damage, const std::string& _State);

    virtual void DamageCheck(float _Damage, float _Offset){};

    virtual void DamageCheck(float _Damage, std::function<void>()){};

private:
};
