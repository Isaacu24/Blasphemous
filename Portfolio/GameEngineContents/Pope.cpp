#include "PreCompile.h"
#include "Pope.h"
#include "SymbolEffect.h"
#include "FireBallSpawner.h"
#include "ToxicCloudSpawner.h"
#include "LightiningBoltSpawner.h"
#include "MagicMissileSpawner.h"

Pope::Pope()
    : SpellType_(SPELLTYPE::FIREBALL)
{
}

Pope::~Pope() {}

void Pope::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_idle", {"pope_idle.png", 0, 12, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("pope_appear", {"pope_appear.png", 0, 14, 0.1f, false});
    Renderer_->CreateFrameAnimationCutTexture("pope_hitReaction", {"pope_hitReaction.png", 0, 10, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("pope_spellCast", {"pope_spellCast.png", 0, 54, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("pope_vanishing", {"pope_vanishing.png", 0, 13, 0.1f, false});
    Renderer_->CreateFrameAnimationCutTexture("pope_death", {"pope_death.png", 0, 34, 0.1f, true});
    Renderer_->SetScaleModeImage();
    Renderer_->SetPivot(PIVOTMODE::BOT);

    FXSRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    FXSRenderer_->CreateFrameAnimationCutTexture("pope_spellCast_FXS",
                                                 {"pope_spellCast_FXS.png", 0, 54, 0.1f, true});  //이펙트

    FXSRenderer_->SetScaleModeImage();
    FXSRenderer_->SetPivot(PIVOTMODE::BOT);
    FXSRenderer_->GetTransform().SetLocalPosition({0, 0, static_cast<int>(ACTORORDER::BossMonster)});
    FXSRenderer_->ChangeFrameAnimation("pope_spellCast_FXS");
    FXSRenderer_->GetColorData().MulColor = float4{0.3f, 0.7f, 0.99f, 1.f};

    Symbol_ = GetLevel()->CreateActor<SymbolEffect>();
    Symbol_->GetTransform().SetWorldPosition({2500, -1760, static_cast<int>(ACTORORDER::BossMonster)});
    Symbol_->SetColor(COLORTYPE::PURPLE);

    State_.CreateStateMember("Idle",
                             std::bind(&Pope::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pope::IdleStart, this, std::placeholders::_1),
                             std::bind(&Pope::IdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Appear",
                             std::bind(&Pope::AppearUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pope::AppearStart, this, std::placeholders::_1),
                             std::bind(&Pope::AppearEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Vanishing",
                             std::bind(&Pope::VanishingUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pope::VanishingStart, this, std::placeholders::_1),
                             std::bind(&Pope::VanishingEnd, this, std::placeholders::_1));

    State_.CreateStateMember("SpellCast",
                             std::bind(&Pope::SpellCastUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pope::SpellCastStart, this, std::placeholders::_1),
                             std::bind(&Pope::SpellCastEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Hit",
                             std::bind(&Pope::HitUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pope::HitStart, this, std::placeholders::_1),
                             std::bind(&Pope::HitEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&Pope::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pope::DeathStart, this, std::placeholders::_1),
                             std::bind(&Pope::DeathEnd, this, std::placeholders::_1));

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
    DetectCollider_->GetTransform().SetWorldScale({500.0f, 500.0f, 1.0f});

    TeleportPos_[0] = float4{1800, -1760};
    TeleportPos_[1] = float4{2100, -1760};
    TeleportPos_[2] = float4{2500, -1760};
    TeleportPos_[3] = float4{2800, -1760};

    CreateSpawner();
}

void Pope::CreateSpawner()
{
    FireBallSpawner_ = GetLevel()->CreateActor<FireBallSpawner>();
    FireBallSpawner_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::BossMonster)});
    FireBallSpawner_->SetGround(ColMap_);
    FireBallSpawner_->Off();

    ToxicCloudSpawner_ = GetLevel()->CreateActor<ToxicCloudSpawner>();
    ToxicCloudSpawner_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::BossMonster)});
    ToxicCloudSpawner_->SetGround(ColMap_);
    ToxicCloudSpawner_->Off();

    LightiningBoltSpawner_ = GetLevel()->CreateActor<LightiningBoltSpawner>();
    LightiningBoltSpawner_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::BossMonster)});
    LightiningBoltSpawner_->Off();

    MagicMissileSpawner_ = GetLevel()->CreateActor<MagicMissileSpawner>();
    MagicMissileSpawner_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::BossMonster)});
    MagicMissileSpawner_->Off();
}

void Pope::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    if (true
        == DetectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Player,
            CollisionType::CT_OBB2D,
            std::bind(&Pope::DecideState, this, std::placeholders::_1, std::placeholders::_2)))
    {
        int a = 0;
    }
}

void Pope::End() {}

bool Pope::DecideState(GameEngineCollision* _This, GameEngineCollision* _Other) { return false; }

void Pope::IdleStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("pope_idle");
    Renderer_->AnimationBindEnd("pope_idle", std::bind(&Pope::ChangeSpellCast, this, std::placeholders::_1));
}

void Pope::IdleUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::IdleEnd(const StateInfo& _Info) { int a = 0; }

void Pope::AppearStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("pope_appear");
    Renderer_->AnimationBindEnd("pope_appear", std::bind(&Pope::ChangeIdleState, this, std::placeholders::_1));
}

void Pope::AppearUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::AppearEnd(const StateInfo& _Info) {}

void Pope::VanishingStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("pope_vanishing"); }

void Pope::VanishingUpdate(float _DeltaTime, const StateInfo& _Info)
{
    VanishingTime_ += _DeltaTime;

    if (3.f <= VanishingTime_)
    {
        VanishingTime_ = 0.f;
        State_.ChangeState("Appear");
    }
}

void Pope::VanishingEnd(const StateInfo& _Info)
{
    int AppearPos_ = Random_.RandomInt(0, 3);

    switch (AppearPos_)
    {
        case 0:
            GetTransform().SetWorldPosition(TeleportPos_[0]);
            break;

        case 1:
            GetTransform().SetWorldPosition(TeleportPos_[1]);
            break;

        case 2:
            GetTransform().SetWorldPosition(TeleportPos_[2]);
            break;

        case 3:
            GetTransform().SetWorldPosition(TeleportPos_[3]);
            break;

        default:
            break;
    }
}

void Pope::SpellCastStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("pope_spellCast");
    // Renderer_->AnimationBindEnd("pope_spellCast", std::bind(&Pope::ChangeIdleState, this, std::placeholders::_1));

    FXSRenderer_->On();
    FXSRenderer_->ChangeFrameAnimation("pope_spellCast_FXS");
    /*FXSRenderer_->AnimationBindEnd("pope_spellCast_FXS",
                                   std::bind(&Pope::AnimationOff, this, std::placeholders::_1));*/

    int Spell = Random_.RandomInt(0, 3);

    if (Spell == static_cast<int>(SpellType_))
    {
        Spell++;

        if (3 < Spell)
        {
            Spell = 0;
        }
    }

    switch (Spell)
    {
        case 0:  //파이어볼
            SpellType_ = SPELLTYPE::FIREBALL;

            FireBallSpawner_->On();
            FireBallSpawner_->SetGround(ColMap_);
            FireBallSpawner_->GetTransform().SetWorldPosition(
                {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 500});
            break;

        case 1:  //독안개
            SpellType_ = SPELLTYPE::TOXICCLOUD;

            ToxicCloudSpawner_->On();
            ToxicCloudSpawner_->SetGround(ColMap_);
            ToxicCloudSpawner_->GetTransform().SetWorldPosition(
                {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 500});
            break;

        case 2:  //번개
            SpellType_ = SPELLTYPE::LIGHTININGBOLT;

            LightiningBoltSpawner_->On();
            break;

        case 3:  //매직 미사일
            SpellType_ = SPELLTYPE::MAGICMISSILE;

            MagicMissileSpawner_->On();
            MagicMissileSpawner_->SetDirection(float4::LEFT);
            MagicMissileSpawner_->GetTransform().SetWorldPosition(
                {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 100.f});
            break;

        default:
            break;
    }
}

void Pope::SpellCastUpdate(float _DeltaTime, const StateInfo& _Info)
{
    switch (SpellType_)
    {
        case SPELLTYPE::FIREBALL:
            {
                FireBallSpawner_->SetDirection(Target_->GetTransform().GetWorldPosition()
                                               - GetTransform().GetWorldPosition());

                float Angle = float4::VectorXYtoRadian(FireBallSpawner_->GetTransform().GetWorldPosition(),
                                                       Target_->GetTransform().GetWorldPosition());

                // FireBallSpawner_->GetTransform().SetLocalRotate(
                //     float4::VectorRotationToRadianXAxis(FireBallSpawner_->GetTransform().GetLocalRotation(), Angle));

                if (false == FireBallSpawner_->IsUpdate())
                {
                    State_.ChangeState("Vanishing");
                }
            }
            break;
        case SPELLTYPE::TOXICCLOUD:
            ToxicCloudSpawner_->SetDirection(Target_->GetTransform().GetWorldPosition()
                                             - GetTransform().GetWorldPosition());

            if (false == ToxicCloudSpawner_->IsUpdate())
            {
                State_.ChangeState("Vanishing");
            }
            break;
        case SPELLTYPE::LIGHTININGBOLT:
            LightiningBoltSpawner_->SetTarget(Target_);

            if (false == LightiningBoltSpawner_->IsUpdate())
            {
                State_.ChangeState("Vanishing");
            }
            break;
        case SPELLTYPE::MAGICMISSILE:
            if (false == MagicMissileSpawner_->IsUpdate())
            {
                State_.ChangeState("Vanishing");
            }
            break;
        default:
            break;
    }
}

void Pope::SpellCastEnd(const StateInfo& _Info) {}

void Pope::HitStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("pope_hitReaction");
    Renderer_->AnimationBindEnd("pope_hitReaction", std::bind(&Pope::ChangeIdleState, this, std::placeholders::_1));
}

void Pope::HitUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::HitEnd(const StateInfo& _Info) {}

void Pope::DeathStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("pope_death");
    Renderer_->AnimationBindEnd("pope_death", std::bind(&Pope::ChangeIdleState, this, std::placeholders::_1));
}

void Pope::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::DeathEnd(const StateInfo& _Info) {}
