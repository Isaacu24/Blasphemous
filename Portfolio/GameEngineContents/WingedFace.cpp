#include "PreCompile.h"
#include "WingedFace.h"
#include "VioletProjectile.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

WingedFace::WingedFace()
    : IsShoot_(false)
{}

WingedFace::~WingedFace() {}


void WingedFace::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("bigpatrollinFlyingEnemy_idle");

        MetaRenderer_->CreateMetaAnimation(
            "bigpatrollinFlyingEnemy_idle",
            {"bigpatrollinFlyingEnemy_idle.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("bigpatrollinFlyingEnemy_death");

        MetaRenderer_->CreateMetaAnimation(
            "bigpatrollinFlyingEnemy_death",
            {"bigpatrollinFlyingEnemy_death.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindFrame("bigpatrollinFlyingEnemy_death",
                                          (
                                              [&](const FrameAnimation_DESC& _Info)
                                              {
                                                  if (5 >= _Info.CurFrame)
                                                  {
                                                      BodyCollider_->Off();
                                                  }
                                              }));

        MetaRenderer_->AnimationBindEnd("bigpatrollinFlyingEnemy_death",
                                        ([&](const FrameAnimation_DESC& _Info) { Death(); }));
    }

    MetaRenderer_->ChangeMetaAnimation("bigpatrollinFlyingEnemy_idle");
    MetaRenderer_->SetPivot(PIVOTMODE::CENTER);

    Gravity_ = CreateComponent<GravityComponent>();

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    DetectCollider_->GetTransform().SetWorldScale({300.0f, 300.0f, 1.0f});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::Monster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({30.0f, 30.0f, 1.0f});
    
    BloodEffect_ = GetLevel()->CreateActor<BloodSplatters>();
    BloodEffect_->GetRenderer()->Off();

    State_.CreateStateMember("Patrol",
                             std::bind(&WingedFace::PatrolUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&WingedFace::PatrolStart, this, std::placeholders::_1));
    State_.CreateStateMember("Shoot",
                             std::bind(&WingedFace::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&WingedFace::ShootStart, this, std::placeholders::_1));
    State_.CreateStateMember("Death",
                             std::bind(&WingedFace::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&WingedFace::DeathStart, this, std::placeholders::_1));

    State_.ChangeState("Patrol");

    SetSpeed(150.f);

    PatrolStart_ = true;
    PatrolEnd_   = false;
}

void WingedFace::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    DetectCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Player,
        CollisionType::CT_OBB2D,
        std::bind(&WingedFace::LookAtPlayer, this, std::placeholders::_1, std::placeholders::_2));

    if ("Death" != State_.GetCurStateStateName())
    {
        NormalMonster::DamageCheck(50.f, 5.f);
    }

    // GameEngineDebug::OutPutString("FaceY : " + std::to_string(GetTransform().GetWorldPosition().y));
}

void WingedFace::End() {}

void WingedFace::PatrolMoveY(float _DeltaTime)
{
    if (true == PatrolStart_)
    {
        if (GetTransform().GetWorldPosition().y < StartPos_)
        {
            GetTransform().SetWorldUpMove(Speed_, _DeltaTime);
        }

        else
        {
            State_.ChangeState("Shoot");

            PatrolStart_ = false;
            PatrolEnd_   = true;
        }
    }

    else if (true == PatrolEnd_)
    {
        if (GetTransform().GetWorldPosition().y > EndPos_)
        {
            GetTransform().SetWorldDownMove(Speed_, _DeltaTime);
        }

        else
        {
            State_.ChangeState("Shoot");

            PatrolStart_ = true;
            PatrolEnd_   = false;
        }
    }
}


void WingedFace::PatrolStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("bigpatrollinFlyingEnemy_idle");
}

void WingedFace::PatrolUpdate(float _DeltaTime, const StateInfo& _Info) { PatrolMoveY(_DeltaTime); }

void WingedFace::ShootStart(const StateInfo& _Info) {}

void WingedFace::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (0.5f < _Info.StateTime && false == IsShoot_)
    {
        IsShoot_ = true;

        VioletProjectile* LeftProjectile = GetLevel()->CreateActor<VioletProjectile>();
        LeftProjectile->SetGround(ColMap_);
        LeftProjectile->SetDirectionX(float4::LEFT);
        LeftProjectile->GetTransform().SetWorldPosition({GetTransform().GetWorldPosition().x - 55.f,
                                                         GetTransform().GetWorldPosition().y,
                                                         static_cast<int>(ACTORORDER::AfterParallax5)});
        LeftProjectile->GetTransform().SetWorldScale({2, 2, 1});

        VioletProjectile* RightProjectile = GetLevel()->CreateActor<VioletProjectile>();
        RightProjectile->SetGround(ColMap_);
        RightProjectile->SetDirectionX(float4::RIGHT);
        RightProjectile->GetTransform().SetWorldPosition({GetTransform().GetWorldPosition().x + 55.f,
                                                          GetTransform().GetWorldPosition().y,
                                                          static_cast<int>(ACTORORDER::AfterParallax5)});
        RightProjectile->GetTransform().SetWorldScale({2, 2, 1});
    }

    if (1.0f <= _Info.StateTime)
    {
        IsShoot_ = false;
        State_.ChangeState("Patrol");
    }
}

void WingedFace::DeathStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("bigpatrollinFlyingEnemy_death");
    DetectCollider_->Off();
}

void WingedFace::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}