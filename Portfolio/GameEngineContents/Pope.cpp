#include "PreCompile.h"
#include "Pope.h"
#include "SymbolEffect.h"
#include "FireBallSpawner.h"
#include "ToxicCloudSpawner.h"
#include "LightiningBoltSpawner.h"
#include "MagicMissileSpawner.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

Pope::Pope()
    : SpellType_(SPELLTYPE::FIREBALL)
{}

Pope::~Pope() {}

void Pope::Start()
{
    GetTransform().SetWorldScale({2.f, 2.f, 1.f});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("pope_idle");

        MetaRenderer_->CreateMetaAnimation(
            "pope_idle", {"pope_idle.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true}, Data);

        MetaRenderer_->AnimationBindEnd("pope_idle",
                                        [&](const FrameAnimation_DESC& _Info) { State_.ChangeState("SpellCast"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("pope_appear");

        MetaRenderer_->CreateMetaAnimation(
            "pope_appear", {"pope_appear.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true}, Data);

        MetaRenderer_->AnimationBindEnd("pope_appear",
                                        [&](const FrameAnimation_DESC& _Info) { State_.ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("pope_hitReaction");

        MetaRenderer_->CreateMetaAnimation(
            "pope_hitReaction",
            {"pope_hitReaction.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("pope_hitReaction",
                                        [&](const FrameAnimation_DESC& _Info) { State_.ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("pope_spellCast");

        MetaRenderer_->CreateMetaAnimation(
            "pope_spellCast", {"pope_spellCast.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true}, Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("pope_vanishing");

        MetaRenderer_->CreateMetaAnimation(
            "pope_vanishing", {"pope_vanishing.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true}, Data);

        MetaRenderer_->AnimationBindEnd("pope_vanishing",
                                        [&](const FrameAnimation_DESC& _Info) { State_.ChangeState("Appear"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("pope_death");

        MetaRenderer_->CreateMetaAnimation(
            "pope_death", {"pope_death.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, false}, Data);

        MetaRenderer_->AnimationBindEnd("pope_death", [&](const FrameAnimation_DESC& _Info) { Death(); });
    }

    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);

    MetaFXSRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("pope_spellCast_FXS");

        MetaFXSRenderer_->CreateMetaAnimation(
            "pope_spellCast_FXS",
            {"pope_spellCast_FXS.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    MetaFXSRenderer_->ChangeMetaAnimation("pope_spellCast_FXS");
    MetaFXSRenderer_->SetPivot(PIVOTMODE::METABOT);
    MetaFXSRenderer_->Off();

    Symbol_ = GetLevel()->CreateActor<SymbolEffect>();
    Symbol_->GetTransform().SetWorldScale({2.f, 2.f, 1.f});
    Symbol_->SetColor(COLORTYPE::PURPLE);
    Symbol_->Renderer_->Off();

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

    // DetectCollider_ = CreateComponent<GameEngineCollision>();
    // DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    // DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.1f, 0.1f, 0.1f, 0.25f});
    // DetectCollider_->GetTransform().SetWorldScale({50.0f, 100.0f, 1.0f});
    // DetectCollider_->GetTransform().SetWorldMove({0, 100});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.1f, 0.1f, 0.1f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({50.0f, 100.0f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({0, 100});

    TeleportPos_[0] = float4{1800, -1760, static_cast<int>(ACTORORDER::BossMonster)};
    TeleportPos_[1] = float4{2100, -1760, static_cast<int>(ACTORORDER::BossMonster)};
    TeleportPos_[2] = float4{2500, -1760, static_cast<int>(ACTORORDER::BossMonster)};
    TeleportPos_[3] = float4{2800, -1760, static_cast<int>(ACTORORDER::BossMonster)};

    CreateSpawner();

    BossUI_ = GetLevel()->CreateActor<BossUI>();
    BossUI_->SetBossMonster(this);
    BossUI_->SetBossUI();
    BossUI_->AllOff();
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
    LightiningBoltSpawner_->GetTransform().SetWorldPosition({0, -1460, static_cast<int>(ACTORORDER::BossMonster)});
    LightiningBoltSpawner_->Off();

    MagicMissileSpawner_ = GetLevel()->CreateActor<MagicMissileSpawner>();
    MagicMissileSpawner_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::BossMonster)});
    MagicMissileSpawner_->Off();
}

void Pope::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    DamageCheck();
}

void Pope::DamageCheck()
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
        MinusHP(10.f);
    }

    if (0 >= GetHP())
    {
        State_.ChangeState("Death");
    }
}

void Pope::End() {}

void Pope::IdleStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("pope_idle"); }

void Pope::IdleUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::IdleEnd(const StateInfo& _Info) {}

void Pope::AppearStart(const StateInfo& _Info)
{
    IsVanishing_   = false;
    VanishingTime_ = 0.f;

    Symbol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{-100, 0});
}

void Pope::AppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
    VanishingTime_ += _DeltaTime;

    if (2.f <= VanishingTime_ && false == IsVanishing_)
    {
        IsVanishing_ = true;
        MetaRenderer_->On();
        BodyCollider_->On();
        MetaRenderer_->ChangeMetaAnimation("pope_appear");
    }
}

void Pope::AppearEnd(const StateInfo& _Info)
{
    BossUI_->AllOn();
    BossUI_->SetBossName("에스크리바르 교황 성하");
    BossUI_->SetFontPosition({470, 590, -100.f});
}

void Pope::VanishingStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("pope_vanishing"); }

void Pope::VanishingUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::VanishingEnd(const StateInfo& _Info)
{
    MetaRenderer_->Off();
    BodyCollider_->Off();

    int AppearPos_ = Random_.RandomInt(0, 3);

    switch (AppearPos_)
    {
        case 0:
            GetTransform().PixLocalPositiveX();
            GetTransform().SetWorldPosition(TeleportPos_[0]);

            Symbol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{100, 0});
            break;

        case 1:
            GetTransform().PixLocalPositiveX();
            GetTransform().SetWorldPosition(TeleportPos_[1]);

            Symbol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{100, 0});
            break;

        case 2:
            GetTransform().PixLocalNegativeX();
            GetTransform().SetWorldPosition(TeleportPos_[2]);

            Symbol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{-100, 0});
            break;

        case 3:
            GetTransform().PixLocalNegativeX();
            GetTransform().SetWorldPosition(TeleportPos_[3]);

            Symbol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{-100, 0});
            break;
    }
}

void Pope::SpellCastStart(const StateInfo& _Info)
{
    Symbol_->Renderer_->On();
    Symbol_->Renderer_->ChangeFrameAnimation("pope_twistedOne_symbol_appear");

    MetaFXSRenderer_->On();
    MetaRenderer_->ChangeMetaAnimation("pope_spellCast");
    MetaRenderer_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());

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

            MetaFXSRenderer_->GetColorData().MulColor = float4::ONE;
            Symbol_->SetColor(COLORTYPE::RED);

            FireBallSpawner_->On();
            FireBallSpawner_->SetGround(ColMap_);
            FireBallSpawner_->GetTransform().SetWorldPosition(
                {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 500});
            break;

        case 1:  //독안개
            SpellType_ = SPELLTYPE::TOXICCLOUD;

            MetaFXSRenderer_->GetColorData().MulColor = float4{0.0f, 0.6f, 0.0f, 1.f};
            Symbol_->SetColor(COLORTYPE::GREEN);

            ToxicCloudSpawner_->On();
            ToxicCloudSpawner_->SetGround(ColMap_);
            ToxicCloudSpawner_->GetTransform().SetWorldPosition(
                {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 500});
            break;

        case 2:  //번개
            SpellType_ = SPELLTYPE::LIGHTININGBOLT;

            MetaFXSRenderer_->GetColorData().MulColor = float4{0.0f, 0.35f, 0.6f, 1.f};
            Symbol_->SetColor(COLORTYPE::BLUE);

            LightiningBoltSpawner_->On();
            break;

        case 3:  //매직 미사일
            SpellType_ = SPELLTYPE::MAGICMISSILE;

            MetaFXSRenderer_->GetColorData().MulColor = float4{0.51f, 0.0f, 1.0f, 1.f};
            Symbol_->SetColor(COLORTYPE::PURPLE);

            MagicMissileSpawner_->On();
            MagicMissileSpawner_->SetDirection(float4::LEFT);
            MagicMissileSpawner_->GetTransform().SetWorldPosition(
                {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 100.f});
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
                                               - FireBallSpawner_->GetTransform().GetWorldPosition());

                if (false == FireBallSpawner_->IsUpdate())
                {
                    State_.ChangeState("Vanishing");
                }
            }
            break;

        case SPELLTYPE::TOXICCLOUD:

            ToxicCloudSpawner_->SetDirection(Target_->GetTransform().GetWorldPosition()
                                             - ToxicCloudSpawner_->GetTransform().GetWorldPosition());

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
    }
}

void Pope::SpellCastEnd(const StateInfo& _Info)
{
    MetaFXSRenderer_->Off();
    Symbol_->Renderer_->ChangeFrameAnimation("pope_twistedOne_symbol_disappear");
}

void Pope::HitStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("pope_hitReaction"); }

void Pope::HitUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::HitEnd(const StateInfo& _Info) {}

void Pope::DeathStart(const StateInfo& _Info)
{
    BodyCollider_->Death();

    Symbol_->Death();
    MetaFXSRenderer_->Death();

    FireBallSpawner_->Death();
    ToxicCloudSpawner_->Death();
    LightiningBoltSpawner_->Death();
    MagicMissileSpawner_->Death();

    BossUI_->AllOff();

    MetaRenderer_->ChangeMetaAnimation("pope_death");
}

void Pope::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::DeathEnd(const StateInfo& _Info) {}
