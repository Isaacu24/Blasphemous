#include "PreCompile.h"
#include "Penitent.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"
#include "MoveEffect.h"
#include "HitEffect.h"
#include "AttackEffect.h"
#include "StageBase.h"
#include "Door.h"
#include "Deogracias.h"
#include "PreCompile.h"
#include "Projectile.h"

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

        if (true == GameEngineInput::GetInst()->IsPressKey("PenitentAnimation")
            || true == GameEngineInput::GetInst()->IsPressButton("PenitentA") && -30000 > ThumbLY_)
        {
            IsGround_ = false;
        }
    }

    else
    {
        std::string Name = State_.GetCurStateStateName();
        IsGround_        = false;
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

    if ("Fall" == State_.GetCurStateStateName())
    {
        if (true == MiddleColor.CompareInt4D(float4::GREEN))
        {
            State_.ChangeState("LadderClimb");
            MetaRenderer_->SetCurAnimationPause(true);
            return;
        }
    }

    if (true == MiddleColor.CompareInt4D(float4::GREEN))
    {
        if (GameEngineInput::GetInst()->IsDownKey("PenitentUp") || 30000 < ThumbLY_)
        {
            CilmbY_ = 30.f;
            State_.ChangeState("LadderClimb");
        }
    }

    if (true == LowColor.CompareInt4D(float4::GREEN))
    {
        if (GameEngineInput::GetInst()->IsDownKey("PenitentDown") || -30000 > ThumbLY_)
        {
            CilmbY_ = -50;
            MetaRenderer_->ChangeMetaAnimation("penitent_ladder_down_from_ground_anim");
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
    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::DeadZone, CollisionType::CT_OBB2D, nullptr))
    {
        State_.ChangeState("Death");
    };
}

bool Penitent::ObjectCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if ("Freeze" == State_.GetCurStateStateName())
    {
        return false;
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("Interaction") && "Idle" == State_.GetCurStateStateName()
        || true == GameEngineInput::GetInst()->IsDownButton("PenitentY") && "Idle" == State_.GetCurStateStateName())
    {
        ObjectBase* Obj = dynamic_cast<ObjectBase*>(_Other->GetActor());

        if (nullptr == Obj)
        {
            return false;
        }

        switch (Obj->GetObjectType())
        {
            case ObjectType::NPC:
                {
                    NPCBase* NPC = dynamic_cast<NPCBase*>(_Other->GetActor());

                    if (nullptr == NPC)
                    {
                        return false;
                    }

                    NPC->SetIsSpeech(true);

                    ChangeState("Freeze");
                    IsFreezeEnd_ = false;
                }
                break;

            case ObjectType::Door:
                break;

            case ObjectType::OpenDoor:
                {
                    GetTransform().SetWorldPosition({Obj->GetTransform().GetWorldPosition().x,
                                                     GetTransform().GetWorldPosition().y,
                                                     GetTransform().GetWorldPosition().z});

                    Door* DoorObj = dynamic_cast<Door*>(_Other->GetActor());

                    if (nullptr != DoorObj)
                    {
                        OutDoorLevel_ = DoorObj->GetLinkLevel();
                    }

                    IsOutDoor_ = true;
                    ChangeState("DoorEntrance");
                }
                break;

            case ObjectType::PrieDieu:
                ChangeState("RestPray");

                if (nullptr != dynamic_cast<StageBase*>(GetLevel()))
                {
                    LastSaveLevel_ = dynamic_cast<StageBase*>(GetLevel())->GetNameConstRef();
                }
                break;

            case ObjectType::Guilt:
                {
                    PenitentGuilt* Guilt = dynamic_cast<PenitentGuilt*>(_Other->GetActor());

                    if (nullptr != Guilt)
                    {
                        Guilt->DestroyGuilt();

                        AttackEffect_->Renderer_->On();
                        ChangeState("CollectSoul");
                    }
                }
                break;

            default:
                break;
        }

        return true;
    }

    return false;
}


void Penitent::CollisionCheck()
{
    //데스존 체크는 어떤 상태는 상관없이 무조건 실행
    DeadZoneCheck();

    if (false
            == AttackCollider_->IsCollision(
                CollisionType::CT_OBB2D, COLLISIONORDER::Monster, CollisionType::CT_OBB2D, nullptr)
        || false
               == AttackCollider_->IsCollision(
                   CollisionType::CT_OBB2D, COLLISIONORDER::MonsterBody, CollisionType::CT_OBB2D, nullptr))
    {
        if ("Parrying" == State_.GetCurStateStateName())
        {
            IsParryCollide_ = true;
        }

        IsHit_ = true;
    }

    if (false
            == AttackCollider_->IsCollision(
                CollisionType::CT_OBB2D, COLLISIONORDER::Monster, CollisionType::CT_OBB2D, nullptr)
        && false
               == AttackCollider_->IsCollision(
                   CollisionType::CT_OBB2D, COLLISIONORDER::MonsterBody, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;
    }

    if (false
            == AttackCollider_->IsCollision(
                CollisionType::CT_OBB2D, COLLISIONORDER::BossMonster, CollisionType::CT_OBB2D, nullptr)
        || false
               == AttackCollider_->IsCollision(
                   CollisionType::CT_OBB2D, COLLISIONORDER::BossMonsterBody, CollisionType::CT_OBB2D, nullptr))
    {
        IsBossHit_ = true;
    }

    if (false
            == AttackCollider_->IsCollision(
                CollisionType::CT_OBB2D, COLLISIONORDER::BossMonster, CollisionType::CT_OBB2D, nullptr)
        && false
               == AttackCollider_->IsCollision(
                   CollisionType::CT_OBB2D, COLLISIONORDER::BossMonsterBody, CollisionType::CT_OBB2D, nullptr))
    {
        IsBossHit_ = false;
    }

    //몬스터와의 상호작용을 위해 콜라이더를 끄기보단 충돌을 무시하는 편이 좋음
    if ("KnockBack" == State_.GetCurStateStateName() || "KnockUp" == State_.GetCurStateStateName()
        || "Death" == State_.GetCurStateStateName() || true == IsParrySuccess_ || true == IsParrySlide_
        || "ParryingAttack" == State_.GetCurStateStateName() || "Execution" == State_.GetCurStateStateName()
        || "Slide" == State_.GetCurStateStateName() || "SlideAttack" == State_.GetCurStateStateName()
        || "VerticalAttack" == State_.GetCurStateStateName() || "VerticalAttackLanding" == State_.GetCurStateStateName()
        || "Respawn" == State_.GetCurStateStateName() || true == IsKnockBackFall_ || true == IsBossKill_)
    {
        return;
    }

    //몬스터 피격
    //공중에서 피격 판정은 하지 않는다.
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
                                   COLLISIONORDER::MonsterAttack,
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

    BodyCollider_->IsCollision(CollisionType::CT_OBB2D,
                               COLLISIONORDER::Object,
                               CollisionType::CT_OBB2D,
                               std::bind(&Penitent::ObjectCheck, this, std::placeholders::_1, std::placeholders::_2));
}

//피격 함수
bool Penitent::KnockBack(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    Projectile* NewProjectile = dynamic_cast<Projectile*>(_Other->GetActor());

    if (nullptr != NewProjectile)
    {
        NewProjectile->GetState().ChangeState("Explosion");
    }

    float4 Dir = _This->GetTransform().GetWorldPosition() - _Other->GetActor()->GetTransform().GetWorldPosition();
    Dir.Normalize();

    if (0.f > Dir.x)
    {
        MoveDir_ = float4::RIGHT;
    }

    else
    {
        MoveDir_ = float4::LEFT;
    }

    if (false == IsGround_)
    {
        return true;
    }

    SetDamege(7);

    if (0 < GetHP())
    {
        State_.ChangeState("KnockBack");
    }

    return true;
}

bool Penitent::KnockUp(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    float4 Dir = _This->GetTransform().GetWorldPosition() - _Other->GetActor()->GetTransform().GetWorldPosition();
    Dir.Normalize();

    if (0.f > Dir.x)
    {
        MoveDir_ = float4::RIGHT;
    }

    else
    {
        MoveDir_ = float4::LEFT;
    }

    if (false == IsGround_)
    {
        return true;
    }

    SetDamege(10);

    if (0 < GetHP())
    {
        State_.ChangeState("KnockUp");
    }

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
        if (0.f >= MoveDir_.x || 0.f > GetTransform().GetWorldScale().x)  //왼쪽이라면
        {
            return false;
        }
    }

    if (static_cast<int>(COLLISIONORDER::RightLedge) == _Other->GetCollsionOrder())
    {
        if (0.f <= MoveDir_.x || 0.f < GetTransform().GetWorldScale().x)  //오른쪽이라면
        {
            return false;
        }
    }

    float4 DanglePos = _Other->GetTransform().GetWorldPosition() + float4{0, -100};

    float PlayerZ = AO_PLAYER;

    GetTransform().SetWorldPosition({DanglePos.x, DanglePos.y, PlayerZ});
    ChangeState("Dangle");

    SoundPlayer_ = GameEngineSound::SoundPlayControl("Penitent_EdgeGrab.wav");
    SoundPlayer_.Volume(0.5f);

    return true;
}


bool Penitent::FallCollisionCheck()
{
    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                              -(GetTransform().GetWorldPosition().y - 15.f));

    if (true == Color.CompareInt4D(float4::BLACK) || true == Color.CompareInt4D(float4::MAGENTA))
    {
        return true;
    }

    return false;
}
