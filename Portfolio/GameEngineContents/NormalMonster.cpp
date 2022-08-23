#include "PreCompile.h"
#include "NormalMonster.h"

NormalMonster::NormalMonster()
    : TrackDistance_(0.f)
{}

NormalMonster::~NormalMonster() {}

void NormalMonster::Start() {

}

void NormalMonster::Update(float _DeltaTime) 
{

}

void NormalMonster::End() {
}

bool NormalMonster::LeftObstacleCheck(int _X, int _Y)
{
    float4 LeftColor = ColMap_->GetCurTexture()->GetPixelToFloat4(_X, _Y);

    if (true == LeftColor.CompareInt4D(float4::BLACK))
    {
        return true;
    }

    if (true == LeftColor.CompareInt4D(float4::MAGENTA))
    {
        return true;
    }

    return false;
}

bool NormalMonster::RightObstacleCheck(int _X, int _Y)
{
    float4 RightColor = ColMap_->GetCurTexture()->GetPixelToFloat4(_X, _Y);

    if (true == RightColor.CompareInt4D(float4::BLACK))
    {
        return true;
    }

    if (true == RightColor.CompareInt4D(float4::MAGENTA))
    {
        return true;
    }

    return false;
}

bool NormalMonster::LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
    {
        GetTransform().PixLocalPositiveX();
    }

    else
    {
        GetTransform().PixLocalNegativeX();
    }

    return true;
}

bool NormalMonster::TrackPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    LookAtPlayer(_This, _Other);

    float Distance = abs(_This->GetTransform().GetWorldPosition().x - _Other->GetTransform().GetWorldPosition().x);

    //추격 사정거리 이탈
    if (TrackDistance_ > Distance)
    {
        IsPlayerLeft_  = false;
        IsPlayerRight_ = false;

        return false;
    }

    if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
    {
        IsPlayerLeft_  = true;
        IsPlayerRight_ = false;
    }

    else
    {
        IsPlayerRight_ = true;
        IsPlayerLeft_  = false;
    }

    return true;
}

bool NormalMonster::CrossroadCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    float Distance = _This->GetTransform().GetWorldPosition().x - _Other->GetTransform().GetWorldPosition().x;

    Distance = abs(Distance);

    if (Crossroad_ >= Distance)
    {
        return true;
    }

    return false;
}


void NormalMonster::DamageCheck()
{
    //스킬 임시 제외
    if (false
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;
    }

    if (true == IsHit_)
    {
        return;
    }

    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        MinusHP(10.f);
        IsHit_ = true;
    }

    if (0 >= GetHP())
    {
        State_.ChangeState("Death");
    }
}
