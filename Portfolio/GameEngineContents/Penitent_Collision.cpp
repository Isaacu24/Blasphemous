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
        LeftColor = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x - 30,
                                                               -(GetTransform().GetWorldPosition().y));

        DebugColliders_[3]->On();
        DebugColliders_[3]->GetTransform().SetWorldPosition(
            {GetTransform().GetWorldPosition().x - 30, GetTransform().GetWorldPosition().y});
        DebugColliders_[3]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});
    }

    else
    {
        LeftColor = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x - 30,
                                                               -(GetTransform().GetWorldPosition().y + 70));

        DebugColliders_[3]->On();
        DebugColliders_[3]->GetTransform().SetWorldPosition(
            {GetTransform().GetWorldPosition().x - 30, GetTransform().GetWorldPosition().y + 50.f});
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
        RightColor = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x + 30,
                                                                -(GetTransform().GetWorldPosition().y));

        DebugColliders_[3]->On();
        DebugColliders_[3]->GetTransform().SetWorldPosition(
            {GetTransform().GetWorldPosition().x + 30, GetTransform().GetWorldPosition().y});
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
    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::Monster,
                           CollisionType::CT_OBB2D,
                           std::bind(&Penitent::HitMonster, this, std::placeholders::_1, std::placeholders::_2));

    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::Projectile,
                           CollisionType::CT_OBB2D,
                           std::bind(&Penitent::HitProjectile, this, std::placeholders::_1, std::placeholders::_2));

    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::BossMonster,
                           CollisionType::CT_OBB2D,
                           std::bind(&Penitent::HitMonster, this, std::placeholders::_1, std::placeholders::_2));

    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::Handrail,
                           CollisionType::CT_OBB2D,
                           std::bind(&Penitent::Dangle, this, std::placeholders::_1, std::placeholders::_2));
}


void Penitent::HitStart(const StateInfo& _Info)
{
    if ("LadderClimb" == _Info.PrevState)
    {
        State_.ChangeState("LadderClimb");
        return;
    }

    State_.ChangeState("Idle");
}

void Penitent::HitUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Penitent::HitEnd(const StateInfo& _Info) {}


//피격 함수
bool Penitent::HitMonster(GameEngineCollision* _This, GameEngineCollision* _Other) { return false; }

bool Penitent::HitProjectile(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if ("Hit" != State_.GetCurStateStateName())
    {
        // State_.ChangeState("Hit");
        return true;
    }

    return false;
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

    if (true == IsGround_)
    {
        return false;
    }

    float4 DanglePos = _Other->GetTransform().GetWorldPosition() + float4{0, -100};

    GetTransform().SetWorldPosition({DanglePos.x, DanglePos.y, static_cast<int>(ACTORORDER::Player)});
    ChangeState("Dangle");

    return true;
}
