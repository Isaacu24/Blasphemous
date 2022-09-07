#include "PreCompile.h"
#include "Penitent.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"
#include "MoveEffect.h"
#include "HitEffect.h"
#include "AttackEffect.h"

void Penitent::GroundCheck()
{
    float4 Color;

    if ("LadderClimb" == State_.GetCurStateStateName())
    {
        Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                           -(GetTransform().GetWorldPosition().y + CilmbY_));
    }

    else
    {
        Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                           -(GetTransform().GetWorldPosition().y - 5));
    }

    if (true == Color.CompareInt4D(float4::BLACK))  //땅이라면
    {
        IsDangle_ = false;
        IsGround_ = true;

        UphillRoadCheck();  //오르막길 체크
    }

    else if (true == Color.CompareInt4D(float4::MAGENTA))
    {
        IsDangle_ = false;
        IsGround_ = true;

        if (true == GameEngineInput::GetInst()->IsPressKey("PenitentAnimation"))
        {
            IsGround_ = false;
        }
    }

    else
    {
        IsGround_ = false;
    }

    if (true
        == PlatformCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::Platform, CollisionType::CT_OBB2D, nullptr))
    {
        IsGround_ = true;
    }
}

void Penitent::LadderCheck()
{
    if ("LadderClimb" == State_.GetCurStateStateName())
    {
        return;
    }

    float4 LowColor = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                                 -(GetTransform().GetWorldPosition().y - 50));

    float4 MiddleColor = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                                    -(GetTransform().GetWorldPosition().y + 50));

    if (true == MiddleColor.CompareInt4D(float4::GREEN))
    {
        if (GameEngineInput::GetInst()->IsDownKey("PenitentUp"))
        {
            CilmbY_ = 30.f;
            State_.ChangeState("LadderClimb");
        }
    }

    if (true == LowColor.CompareInt4D(float4::GREEN))
    {
        if (GameEngineInput::GetInst()->IsDownKey("PenitentDown"))
        {
            CilmbY_ = -50;
            State_.ChangeState("LadderClimb");
        }
    }
}

void Penitent::UphillRoadCheck()
{
    while (true)
    {
        float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                                  -(GetTransform().GetWorldPosition().y - 4));

        if (true == Color.CompareInt4D(float4::BLACK) || true == Color.CompareInt4D(float4::MAGENTA))
        {
            GetTransform().SetWorldMove(float4::UP);
            continue;
        }

        else
        {
            break;
        }
    }

    while (true)
    {
        bool IsPlatform = PlatformUpCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::Platform, CollisionType::CT_OBB2D, nullptr);

        if (true == IsPlatform)
        {
            GetTransform().SetWorldMove(float4::UP);
            continue;
        }

        else
        {
            break;
        }
    }
}

bool Penitent::LeftObstacleCheck()
{
    float4 LeftColor;

    if ("Slide" == State_.GetCurStateStateName())
    {
        LeftColor = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x - 10,
                                                               -(GetTransform().GetWorldPosition().y + 30));

        DebugColliders_[3]->On();
        DebugColliders_[3]->GetTransform().SetWorldPosition(
            {GetTransform().GetWorldPosition().x - 10, GetTransform().GetWorldPosition().y + 30});
        DebugColliders_[3]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});
    }

    else
    {
        LeftColor = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x - 30,
                                                               -(GetTransform().GetWorldPosition().y + 70));

        DebugColliders_[3]->On();
        DebugColliders_[3]->GetTransform().SetWorldPosition(
            {GetTransform().GetWorldPosition().x - 30, GetTransform().GetWorldPosition().y + 70.f});
        DebugColliders_[3]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});
    }

    if (true == LeftColor.CompareInt4D(float4::BLACK))
    {
        return true;
    }

    return false;
}

bool Penitent::RightObstacleCheck()
{
    float4 RightColor;

    if ("Slide" == State_.GetCurStateStateName())
    {
        RightColor = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x + 10,
                                                                -(GetTransform().GetWorldPosition().y + 30));

        DebugColliders_[3]->On();
        DebugColliders_[3]->GetTransform().SetWorldPosition(
            {GetTransform().GetWorldPosition().x + 10, GetTransform().GetWorldPosition().y + 30});
        DebugColliders_[3]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});
    }

    else
    {
        RightColor = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x + 30,
                                                                -(GetTransform().GetWorldPosition().y + 70));

        DebugColliders_[3]->On();
        DebugColliders_[3]->GetTransform().SetWorldPosition(
            {GetTransform().GetWorldPosition().x + 30, GetTransform().GetWorldPosition().y + 70});
        DebugColliders_[3]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});
    }

    if (true == RightColor.CompareInt4D(float4::BLACK))
    {
        return true;
    }

    return false;
}

void Penitent::DeadZoneCheck()
{
    IsFallDeath_ = BodyCollider_->IsCollision(
        CollisionType::CT_OBB2D, COLLISIONORDER::DeadZone, CollisionType::CT_OBB2D, nullptr);

    if (true == IsFallDeath_)
    {
        State_.ChangeState("Death");
    }
}


void Penitent::CollisionCheck()
{
    if ("KnockBack" == State_.GetCurStateStateName() || "KnockUp" == State_.GetCurStateStateName())
    {
        return;
    }

    //몬스터 피격
    {
        BodyCollider_->IsCollision(CollisionType::CT_OBB2D,
                                   COLLISIONORDER::Monster,
                                   CollisionType::CT_OBB2D,
                                   std::bind(&Penitent::KnockBack, this, std::placeholders::_1, std::placeholders::_2));

        BodyCollider_->IsCollision(CollisionType::CT_OBB2D,
                                   COLLISIONORDER::Projectile,
                                   CollisionType::CT_OBB2D,
                                   std::bind(&Penitent::KnockBack, this, std::placeholders::_1, std::placeholders::_2));

        BodyCollider_->IsCollision(CollisionType::CT_OBB2D,
                                   COLLISIONORDER::BossMonster,
                                   CollisionType::CT_OBB2D,
                                   std::bind(&Penitent::KnockBack, this, std::placeholders::_1, std::placeholders::_2));

        BodyCollider_->IsCollision(CollisionType::CT_OBB2D,
                                   COLLISIONORDER::BossMonsterAttack,
                                   CollisionType::CT_OBB2D,
                                   std::bind(&Penitent::KnockBack, this, std::placeholders::_1, std::placeholders::_2));

        BodyCollider_->IsCollision(CollisionType::CT_OBB2D,
                                   COLLISIONORDER::BossMonsterAttack1,
                                   CollisionType::CT_OBB2D,
                                   std::bind(&Penitent::KnockUp, this, std::placeholders::_1, std::placeholders::_2));
    }

    BodyCollider_->IsCollision(CollisionType::CT_OBB2D,
                               COLLISIONORDER::LeftLedge,
                               CollisionType::CT_OBB2D,
                               std::bind(&Penitent::Dangle, this, std::placeholders::_1, std::placeholders::_2));

    BodyCollider_->IsCollision(CollisionType::CT_OBB2D,
                               COLLISIONORDER::RightLedge,
                               CollisionType::CT_OBB2D,
                               std::bind(&Penitent::Dangle, this, std::placeholders::_1, std::placeholders::_2));

    IsHit_ = AttackCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Monster,
        CollisionType::CT_OBB2D,
        std::bind(&Penitent::HitEffectCheck, this, std::placeholders::_1, std::placeholders::_2));

    if (false
        == AttackCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::Monster, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;
    }

    IsBossHit_ = AttackCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::BossMonster,
        CollisionType::CT_OBB2D,
        std::bind(&Penitent::HitEffectCheck, this, std::placeholders::_1, std::placeholders::_2));

    if (false
        == AttackCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::BossMonster, CollisionType::CT_OBB2D, nullptr))
    {
        IsBossHit_ = false;
    }

    DeadZoneCheck();
}


//피격 함수
bool Penitent::KnockBack(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if (false == IsGround_)
    {
        SetDamege(10.f);
        return true;
    }

    State_.ChangeState("KnockBack");

    return true;
}

bool Penitent::KnockUp(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if (false == IsGround_)
    {
        SetDamege(15.f);
        return true;
    }

    State_.ChangeState("KnockUp");

    return true;
}

bool Penitent::Dangle(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if ("Fall" != State_.GetCurStateStateName())
    {
        return false;
    }

    if (true == IsDangle_)
    {
        return false;
    }

    if (static_cast<int>(COLLISIONORDER::LeftLedge) == _Other->GetCollsionOrder())
    {
        if (0 > RealXDir_)  //왼쪽이라면
        {
            return false;
        }
    }

    if (static_cast<int>(COLLISIONORDER::RightLedge) == _Other->GetCollsionOrder())
    {
        if (0 < RealXDir_)  //오른쪽이라면
        {
            return false;
        }
    }

    float4 DanglePos = _Other->GetTransform().GetWorldPosition() + float4{0, -100};

    float PlayerZ = AO_PLAYER;

    GetTransform().SetWorldPosition({DanglePos.x, DanglePos.y, PlayerZ});
    ChangeState("Dangle");

    return true;
}

bool Penitent::FallCollisionCheck()
{
    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                              -(GetTransform().GetWorldPosition().y - 15));

    if (true == Color.CompareInt4D(float4::BLACK) || true == Color.CompareInt4D(float4::MAGENTA))
    {
        return true;
    }

    return false;
}


bool Penitent::HitEffectCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    float4 MonsterPos = _Other->GetTransform().GetWorldPosition();
    HitEffect_->GetTransform().SetWorldPosition(
        {MonsterPos.x, MonsterPos.y, HitEffect_->GetTransform().GetWorldPosition().z});

    if (0 < RealXDir_)  //오른쪽
    {
        HitEffect_->GetTransform().PixLocalNegativeX();
    }

    else if (0 > RealXDir_)  //왼쪽
    {
        HitEffect_->GetTransform().PixLocalPositiveX();
    }

    switch (HitStack_)
    {
        case 0:
            HitEffect_->Renderer_->ChangeMetaAnimation("penitent_attack_spark_1_revision_anim");
            break;

        case 1:
            HitEffect_->Renderer_->ChangeMetaAnimation("penitent_attack_spark_2_revision_anim");
            break;

        case 2:
            HitEffect_->Renderer_->ChangeMetaAnimation("penitent_attack_spark_3_revision_anim");
            break;

        default:
            HitEffect_->Renderer_->ChangeMetaAnimation("penitent_attack_spark_1_anim");
            HitStack_ = 0;
            break;
    }

    return true;
}