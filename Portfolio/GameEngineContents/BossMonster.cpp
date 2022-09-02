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
                                                       static_cast<int>(ACTORORDER::PlayerEffect)});
        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplatters");

        MinusHP(10.f);
    }

    if (0 >= GetHP())
    {
        State_.ChangeState("Death");
    }
}
