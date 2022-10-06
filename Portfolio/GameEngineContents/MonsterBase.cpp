#include "PreCompile.h"
#include "MonsterBase.h"
#include "MetaTextureRenderer.h"
#include "MonsterHitEffect.h"

MonsterBase::MonsterBase() 
    : State_{}
    , Renderer_(nullptr)
    , ColMap_(nullptr)
    , Gravity_(nullptr)
    , DetectCollider_(nullptr)
    , BodyCollider_(nullptr)
    , AttackCollider_(nullptr)
    , HP_(100)
    , Att_(100)
    , Speed_(100.f)
    , Tear_(100)
    , IsGround_(false)
{}

MonsterBase::~MonsterBase() {}

void MonsterBase::SetGround(GameEngineTextureRenderer* _Ground) { ColMap_ = _Ground; }

bool MonsterBase::GroundCheck(int _X, int _Y)
{
    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(_X, _Y);

    if (Color.CompareInt4D(float4::BLACK))
    {
        IsGround_ = true;
        return true;
    }

    else if (Color.CompareInt4D(float4::MAGENTA))
    {
        IsGround_ = true;
        return true;
    }

    IsGround_ = false;
    return false;
}

bool MonsterBase::UphillRoadCheck(int _X, int _Y)
{
    while (true)
    {
        float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(_X, _Y);

        if (true == Color.CompareInt4D(float4::BLACK))
        {
            return true;
        }

        else
        {
            return false;
        }
    }
}

bool MonsterBase::GroundCheck(float _X, float _Y) 
{
    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(_X, _Y);

    if (Color.CompareInt4D(float4::BLACK))
    {
        IsGround_ = true;
        return true;
    }

    else if (Color.CompareInt4D(float4::MAGENTA))
    {
        IsGround_ = true;
        return true;
    }

    IsGround_ = false;
    return false;
}

bool MonsterBase::UphillRoadCheck(float _X, float _Y) 
{
    while (true)
    {
        float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(_X, _Y);

        if (true == Color.CompareInt4D(float4::BLACK))
        {
            return true;
        }

        else
        {
            return false;
        }
    }
}



void MonsterBase::DamageCheck()
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

void MonsterBase::DamageCheck(float _Damage)
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
        MinusHP(_Damage);
        IsHit_ = true;
    }

    if (0 >= GetHP())
    {
        State_.ChangeState("Death");
    }
}

void MonsterBase::DamageCheck(float _Damage, const std::string& _State)
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
        MinusHP(_Damage);
        IsHit_ = true;
    }

    if (0 >= GetHP())
    {
        State_.ChangeState(_State);
    }
}


void MonsterBase::PlayerRangeAttackHit()
{
    IsHit_ = true;

    if (nullptr != MetaRenderer_)
    {
        MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
    }

    else if (nullptr != Renderer_)
    {
        Renderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
    }

    float4 HitPos = BodyCollider_->GetTransform().GetWorldPosition();

    BloodEffect_->GetRenderer()->On();
    BloodEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
    BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

    HitEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
    HitEffect_->ShowRangeHitEffect();
}
