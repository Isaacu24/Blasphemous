#include "PreCompile.h"
#include "ElderBrother.h"
#include "GravityActor.h"

namespace
{
    const char*                ELDER_ATTACK_NAME = "elderBrother_attack";
    constexpr std::string_view TEST              = "TEST";
}  // namespace

ElderBrother::ElderBrother()
    : JumpForce_(500.f)
{}

ElderBrother::~ElderBrother() {}

void ElderBrother::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("elderBrother_idle", {"elderBrother_idle.png", 0, 9, 0.15f, true});
    Renderer_->CreateFrameAnimationCutTexture("elderBrother_jump", {"elderBrother_jump.png", 0, 24, 0.15f, true});
    Renderer_->CreateFrameAnimationCutTexture("elderBrother_attack", {"elderBrother_attack.png", 0, 23, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("elderBrother_death", {"elderBrother_death.png", 0, 48, 0.1f, false});
    Renderer_->GetTransform().SetWorldScale({1200, 700});
    Renderer_->SetPivot(PIVOTMODE::BOT);
    Renderer_->GetTransform().PixLocalNegativeX();

    AttackEffecter_ = GetLevel()->CreateActor<AttackCorpseEffecter>();
    JumpEffecter_   = GetLevel()->CreateActor<JumpCorpseEffecter>();
    AffectChecker   = GetLevel()->CreateActor<GravityActor>(ACTORORDER::BossMonster);
    AffectChecker->Off();

    State_.CreateStateMember("Freeze",
                             std::bind(&ElderBrother::FreezeUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::FreezeStart, this, std::placeholders::_1));
    State_.CreateStateMember("Appear",
                             std::bind(&ElderBrother::AppearUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::AppearStart, this, std::placeholders::_1));
    State_.CreateStateMember("Idle",
                             std::bind(&ElderBrother::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::IdleStart, this, std::placeholders::_1));
    State_.CreateStateMember("Jump",
                             std::bind(&ElderBrother::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::JumpStart, this, std::placeholders::_1),
                             std::bind(&ElderBrother::JumpEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Attack",
                             std::bind(&ElderBrother::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::AttackStart, this, std::placeholders::_1),
                             std::bind(&ElderBrother::AttackEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Death",
                             std::bind(&ElderBrother::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ElderBrother::DeathStart, this, std::placeholders::_1));

    State_.ChangeState("Freeze");

    Gravity_ = CreateComponent<GravityComponent>();

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
    DetectCollider_->GetTransform().SetWorldScale({2000.0f, 1500.0f});
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB, float4{1.0f, 1.0f, 1.0f, 0.5f});

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->GetTransform().SetWorldScale({500.0f, 100.0f});
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB, float4{1.0f, 0.0f, 0.0f, 1.0f});
    AttackCollider_->Off();

    JumpCollider_ = CreateComponent<GameEngineCollision>();
    JumpCollider_->GetTransform().SetWorldScale({500.0f, 500.0f});
    JumpCollider_->SetDebugSetting(CollisionType::CT_OBB, float4{1.0f, 0.0f, 0.0f, 1.0f});
    JumpCollider_->Off();
}

void ElderBrother::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    if (true == GroundCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 89.f)))
    {
        if (true == UphillRoadCheck(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 90.f)))
        {
            GetTransform().SetWorldMove(float4::UP);
        }
    }

    Gravity_->SetActive(!IsGround_);
}

void ElderBrother::End() {}

void ElderBrother::FreezeStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("elderBrother_idle"); }

void ElderBrother::FreezeUpdate(float _DeltaTime, const StateInfo& _Info) {}

void ElderBrother::AppearStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("elderBrother_idle"); }

void ElderBrother::AppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
    AppearTime_ += _DeltaTime;

    if (1.f <= AppearTime_)
    {
        AppearTime_ = 0.f;
        State_.ChangeState("Idle");
        IsEventEnd_ = true;

        GetTransform().SetWorldPosition({GetTransform().GetWorldPosition().x,
                                         GetTransform().GetWorldPosition().y,
                                         static_cast<int>(ACTORORDER::BossMonster)});
    }
}

void ElderBrother::IdleStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("elderBrother_idle");

    Alpha_ = 0.f;
}

void ElderBrother::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    DetectCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Player,
        CollisionType::CT_OBB2D,
        std::bind(&ElderBrother::DecideState, this, std::placeholders::_1, std::placeholders::_2));
}

void ElderBrother::JumpStart(const StateInfo& _Info) { Speed_ = 600.f; }

void ElderBrother::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
    Speed_ -= 1.f;
    DecideTime_ += _DeltaTime;

    if (1.5f > DecideTime_)
    {
        return;
    }

    if (false == IsDecide_)
    {
        IsDecide_ = true;

        Renderer_->ChangeFrameAnimation("elderBrother_jump");
        Renderer_->AnimationBindFrame("elderBrother_jump",
                                      std::bind(&ElderBrother::JumpFrame, this, std::placeholders::_1, _DeltaTime));
        Renderer_->AnimationBindEnd("elderBrother_jump",
                                    std::bind(&ElderBrother::ChangeIdle, this, std::placeholders::_1));
    }

    if (true == IsJump_)
    {
        GetTransform().SetWorldMove(GetTransform().GetUpVector() * _DeltaTime);

        Alpha_ += _DeltaTime * 0.05f;
        GetTransform().SetWorldPosition(float4::LerpLimit(GetTransform().GetWorldPosition(), Target_, Alpha_));
    }
}

void ElderBrother::JumpEnd(const StateInfo& _Info)
{ 
    JumpCollider_->Off(); 
}

void ElderBrother::AttackStart(const StateInfo& _Info) {}

void ElderBrother::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    DecideTime_ += _DeltaTime;

    if (1.f < DecideTime_ && false == IsDecide_)
    {
        IsDecide_ = true;

        AffectChecker->Off();
        AffectChecker->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
        AffectChecker->SetGround(ColMap_);
        AffectChecker->SetDirection(Dir_);

        Renderer_->ChangeFrameAnimation("elderBrother_attack");
        Renderer_->AnimationBindFrame("elderBrother_attack",
                                      std::bind(&ElderBrother::AttackFrame, this, std::placeholders::_1));
        Renderer_->AnimationBindEnd("elderBrother_attack",
                                    std::bind(&ElderBrother::ChangeIdle, this, std::placeholders::_1));
    }
}

void ElderBrother::AttackEnd(const StateInfo& _Info) 
{
    AttackCollider_->Off(); 
}

void ElderBrother::DeathStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("elderBrother_death"); }

void ElderBrother::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}


bool ElderBrother::DecideState(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    DecideTime_ = 0.f;
    IsDecide_   = false;

    if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
    {
        Dir_ = float4::RIGHT;
        Renderer_->GetTransform().PixLocalPositiveX();
    }

    else
    {
        Dir_ = float4::LEFT;
        Renderer_->GetTransform().PixLocalNegativeX();
    }

    float Distance = abs(_This->GetTransform().GetWorldPosition().x - _Other->GetTransform().GetWorldPosition().x);

    if (500 >= Distance)
    {
        State_.ChangeState("Attack");
    }

    else
    {
        Target_ = _Other->GetTransform().GetWorldPosition();
        State_.ChangeState("Jump");
    }

    return true;
}

bool ElderBrother::AttackToPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    Penitent* Player = dynamic_cast<Penitent*>(_Other->GetRoot());

    if (nullptr == Player)
    {
        return false;
    }

    else
    {
        Player->SetDamege(10);
    }

    return false;
}

bool ElderBrother::JumpToPlayer(GameEngineCollision* _This, GameEngineCollision* _Other) { return false; }
