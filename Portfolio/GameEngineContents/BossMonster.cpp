#include "BossMonster.h"


BossMonster::BossMonster()
    : BossEvent_(false)
{}

BossMonster::~BossMonster() {}

void BossMonster::DamageCheck(float _Damage)
{
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
        IsHit_ = true;

        BloodEffect_->GetTransform().SetWorldPosition({BodyCollider_->GetTransform().GetWorldPosition().x,
                                                       BodyCollider_->GetTransform().GetWorldPosition().y,
                                                       PlayerEffectZ});
        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplatters");

        MinusHP(_Damage);
    }

    if (0 >= GetHP())
    {
        State_.ChangeState("Death");
    }
}

void BossMonster::DamageCheck(float _Damage, std::function<void>()) 
{

}
