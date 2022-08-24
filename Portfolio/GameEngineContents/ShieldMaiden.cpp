#include "PreCompile.h"
#include "ShieldMaiden.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

namespace SHIELD_MAIDEN
{
    inline const char* IDLE = "TEST";
}

ShieldMaiden::ShieldMaiden() {}

ShieldMaiden::~ShieldMaiden() {}

void ShieldMaiden::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldMaiden_walking_anim");

        MetaRenderer_->CreateMetaAnimation(
            "shieldMaiden_walking_anim",
            {"shieldMaiden_walking_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("shieldMaiden_attack");

        MetaRenderer_->CreateMetaAnimation(
            "shieldMaiden_attack",
            {"shieldMaiden_attack.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("shieldMaiden_attack",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeMonsterState("Track"); });
    }

    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_walking_anim");

    //해당 몬스터는 피벗을 맞추면 틀어진다
    // MetaRenderer_->SetPivot(PIVOTMODE::BOT);

    Gravity_ = CreateComponent<GravityComponent>();

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.25f});
    DetectCollider_->GetTransform().SetWorldScale({400.0f, 200.0f, 1.0f});
    DetectCollider_->GetTransform().SetWorldMove({0, 100.f});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::Monster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({30.0f, 100.0f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({-20, 50.f});

    ShieldCollider_ = CreateComponent<GameEngineCollision>();
    ShieldCollider_->ChangeOrder(COLLISIONORDER::MonsterShield);
    ShieldCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 1.0f, 1.0f, 0.5f});
    ShieldCollider_->GetTransform().SetWorldScale({30.0f, 100.0f, 1.0f});
    ShieldCollider_->GetTransform().SetWorldMove({10, 50.f});

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->ChangeOrder(COLLISIONORDER::MonsterAttack);
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.2f, 0.34f, 0.2f, 0.5f});
    AttackCollider_->GetTransform().SetWorldScale({100.0f, 200.0f, 1.0f});
    AttackCollider_->GetTransform().SetWorldMove({70, 50.f});
    AttackCollider_->Off();

    State_.CreateStateMember("Patrol",
                             std::bind(&ShieldMaiden::PatrolUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ShieldMaiden::PatrolStart, this, std::placeholders::_1),
                             std::bind(&ShieldMaiden::PatrolEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Track",
                             std::bind(&ShieldMaiden::TrackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ShieldMaiden::TrackStart, this, std::placeholders::_1),
                             std::bind(&ShieldMaiden::TrackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Attack",
                             std::bind(&ShieldMaiden::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ShieldMaiden::AttackStart, this, std::placeholders::_1),
                             std::bind(&ShieldMaiden::AttackEnd, this, std::placeholders::_1));

    State_.ChangeState("Patrol");

    SetSpeed(50.f);
    SetTear(15);

    SetCrossroad(100.f);

    PatrolStart_ = true;
    PatrolEnd_   = false;
}

void ShieldMaiden::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    IsGround_ = GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
    Gravity_->SetActive(!IsGround_);

    DamageCheck();
}

void ShieldMaiden::End() {}


void ShieldMaiden::DamageCheck() 
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
        == ShieldCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsBlock_ = true;
    }

    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        if (true == IsBlock_)
        {
            return;
        }

        IsHit_ = true;
        MinusHP(10.f);
    }
}



void ShieldMaiden::PatrolMoveX(float _DeltaTime)
{
    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        if (true
            == RightObstacleCheck(GetTransform().GetWorldPosition().x + 70, -(GetTransform().GetWorldPosition().y)))
        {
            GetTransform().SetWorldMove(float4::RIGHT * Speed_ * _DeltaTime);
        }

        else
        {
            GetTransform().PixLocalNegativeX();

            PatrolEnd_   = true;
            PatrolStart_ = false;
        }
    }

    else if (false == PatrolStart_ && true == PatrolEnd_)
    {
        if (true == LeftObstacleCheck(GetTransform().GetWorldPosition().x - 70, -(GetTransform().GetWorldPosition().y)))
        {
            GetTransform().SetWorldMove(float4::LEFT * Speed_ * _DeltaTime);
        }

        else
        {
            GetTransform().PixLocalPositiveX();

            PatrolStart_ = true;
            PatrolEnd_   = false;
        }
    }
}


void ShieldMaiden::PatrolStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_walking_anim");

    if (true == PatrolStart_ && false == PatrolEnd_)
    {
        GetTransform().PixLocalPositiveX();
    }

    else if (false == PatrolStart_ && true == PatrolEnd_)
    {
        GetTransform().PixLocalNegativeX();
    }
}

void ShieldMaiden::PatrolUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, nullptr))
    {
        State_.ChangeState("Track");
        return;
    }

    PatrolMoveX(_DeltaTime);
}

void ShieldMaiden::PatrolEnd(const StateInfo& _Info) {}

void ShieldMaiden::TrackStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_walking_anim");
}

void ShieldMaiden::TrackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (false
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&ShieldMaiden::TrackPlayer, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Patrol");
        return;
    }

    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&ShieldMaiden::CrossroadCheck, this, std::placeholders::_1, std::placeholders::_2)))
    {
        State_.ChangeState("Attack");
        return;
    }

    if (true == IsPlayerLeft_)
    {
        GetTransform().SetWorldMove(float4::RIGHT * Speed_ * _DeltaTime);
    }

    else if (true == IsPlayerRight_)
    {
        GetTransform().SetWorldMove(float4::LEFT * Speed_ * _DeltaTime);
    }
}

void ShieldMaiden::TrackEnd(const StateInfo& _Info) {}

void ShieldMaiden::AttackStart(const StateInfo& _Info)
{
    if (true == IsPlayerRight_)
    {
        GetTransform().PixLocalNegativeX();
    }

    else if (true == IsPlayerLeft_)
    {
        GetTransform().PixLocalPositiveX();
    }

    MetaRenderer_->ChangeMetaAnimation("shieldMaiden_attack");
    AttackCollider_->On();
}

void ShieldMaiden::AttackUpdate(float _DeltaTime, const StateInfo& _Info) {}

void ShieldMaiden::AttackEnd(const StateInfo& _Info) 
{
    AttackCollider_->Off(); 
}

void ShieldMaiden::ParryReactionStart(const StateInfo& _Info) 
{
}

void ShieldMaiden::ParryReactionUpdate(float _DeltaTime, const StateInfo& _Info) 
{

}

void ShieldMaiden::ParryReactionEnd(const StateInfo& _Info) {}
