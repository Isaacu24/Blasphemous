#include "PreCompile.h"
#include "Penitent.h"


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


void Penitent::CollisionCheck()
{
    if ("KnockBack" == State_.GetCurStateStateName())
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
    }

    BodyCollider_->IsCollision(CollisionType::CT_OBB2D,
                               COLLISIONORDER::LeftLedge,
                               CollisionType::CT_OBB2D,
                               std::bind(&Penitent::Dangle, this, std::placeholders::_1, std::placeholders::_2));

    BodyCollider_->IsCollision(CollisionType::CT_OBB2D,
                               COLLISIONORDER::RightLedge,
                               CollisionType::CT_OBB2D,
                               std::bind(&Penitent::Dangle, this, std::placeholders::_1, std::placeholders::_2));
}


//피격 함수
bool Penitent::KnockBack(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if (false == IsGround_)
    {
        SetDamege(10.f);
        return false;
    }

    float Dir = _This->GetTransform().GetWorldPosition().x - _Other->GetTransform().GetWorldPosition().x;

    if (0 >= Dir)  //몬스터가 오른쪽에 있다.
    {
        RealXDir_ = -1;
    }

    else if (0 < Dir)  //몬스터가 왼쪽에 있다.
    {
        RealXDir_ = 1;
    }

    State_.ChangeState("KnockBack");

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

    GetTransform().SetWorldPosition({DanglePos.x, DanglePos.y, static_cast<int>(ACTORORDER::Player)});
    ChangeState("Dangle");

    return true;
}
