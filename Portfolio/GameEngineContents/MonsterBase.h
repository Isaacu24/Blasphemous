#pragma once
#include "PreCompile.h"

//������ �⺻���� Ŭ����
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

    inline void SetHP(int _Value) { HP_ = _Value; }

    inline int GetHP() { return HP_; }

    inline void SetTear(int _Value) { Tear_ = _Value; }

    inline int GetTear() { return Tear_; }

    inline void SetSpeed(float _Speed) { Speed_ = _Speed; }

    void SetGround(GameEngineTextureRenderer* _Ground);

    inline void ChangeMonsterState(const std::string& _State) { State_.ChangeState(_State); }

    inline void ChangeIdleState(const FrameAnimation_DESC& _Info) 
    {
        State_.ChangeState("Idle");
    }

protected:
    GameEngineStateManager State_;

    GameEngineTextureRenderer* Renderer_;
    GameEngineTextureRenderer* ColMap_;

    class GravityComponent* Gravity_;

    class GameEngineCollision* DetectCollider_; //����
    GameEngineCollision*       BodyCollider_;   //��ü
    GameEngineCollision*       AttackCollider_; //����

    int   HP_;
    int   Att_;
    float Speed_;

    int Tear_; //�÷��̾�� ������ ����

    bool IsGround_;

    bool GroundCheck(int _X, int _Y);
    bool UphillRoadCheck(int _X, int _Y);

private:
};
