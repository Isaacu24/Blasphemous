#include "PreCompile.h"
#include "NormalMonster.h"
#include "BloodSplatters.h"
#include "MetaTextureRenderer.h"

NormalMonster::NormalMonster()
    : TrackDistance_(0.f)
{}

NormalMonster::~NormalMonster() {}

void NormalMonster::Start() {}

void NormalMonster::Update(float _DeltaTime) {}

void NormalMonster::End() {}

bool NormalMonster::LeftObstacleCheck(float _X, float _Y)
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

bool NormalMonster::RightObstacleCheck(float _X, float _Y)
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

    DetectPlayer(_This, _Other);

    return true;
}


bool NormalMonster::DetectPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    float Distance = abs(_This->GetTransform().GetWorldPosition().x - _Other->GetTransform().GetWorldPosition().x);

    if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
    {
        IsPlayerRight_ = true;
        IsPlayerLeft_  = false;
    }

    else
    {
        IsPlayerLeft_  = true;
        IsPlayerRight_ = false;
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


void NormalMonster::DamageCheck(float _Damage, float _Offset)
{
    //스킬 임시 제외
    if (false
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;

        if (nullptr != Renderer_)
        {
            Renderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
        }

        if (nullptr != MetaRenderer_)
        {
            MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
        }
    }

    if (true == IsHit_)
    {
        return;
    }

    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        MinusHP(_Damage);
        IsHit_ = true;

        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetTransform().SetWorldPosition(
            {BodyCollider_->GetTransform().GetWorldPosition().x + (-(Dir_.x) * _Offset),
             BodyCollider_->GetTransform().GetWorldPosition().y,
             BossMonsterEffectZ});
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

        if (nullptr != Renderer_)
        {
            Renderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
        }

        if (nullptr != MetaRenderer_)
        {
            MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
        }
    }

    if (0 >= GetHP())
    {
        State_.ChangeState("Death");
    }
}
