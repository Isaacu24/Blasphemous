#include "PreCompile.h"
#include "Pontiff.h"
#include "GiantSword.h"
#include "PlatformSpawner.h"
#include "PontiffMainBody.h"
#include "AnguishBeamSpawner.h"
#include "MagicMissileSpawner.h"
#include "LightiningBoltSpawner.h"
#include "ToxicCloudSpawner.h"
#include "FireBallSpawner.h"
#include "SymbolEffect.h"

Pontiff::Pontiff()
    : CurType_(SPELLTYPE::NONE)
    , PervType_(SPELLTYPE::NONE)
{}

Pontiff::~Pontiff() {}

void Pontiff::Start()
{
    Helmet_ = CreateComponent<GameEngineTextureRenderer>();
    Body_   = CreateComponent<GameEngineTextureRenderer>();
    Face_   = CreateComponent<GameEngineTextureRenderer>();

    MainBody_ = GetLevel()->CreateActor<PontiffMainBody>();
    MainBody_->Off();

    Helmet_->CreateFrameAnimationCutTexture("pontiff_idle_helmet", {"pontiff_idle_helmet.png", 0, 30, 0.2f, true});

    Helmet_->CreateFrameAnimationCutTexture("pontiff_opening_helmet",
                                            {"pontiff_opening_helmet.png", 0, 0, 0.0f, false});

    Helmet_->CreateFrameAnimationCutTexture("pontiff_closing_helmet",
                                            {"pontiff_closing_helmet.png", 0, 0, 0.0f, false});

    Helmet_->GetTransform().SetLocalScale({900, 1300});
    Helmet_->GetTransform().SetLocalMove({0, 50});

    Body_->CreateFrameAnimationCutTexture("pontiff_idle_torso", {"pontiff_idle_torso.png", 0, 30, 0.2f, true});
    Body_->CreateFrameAnimationCutTexture("pontiff_opening_torso", {"pontiff_opening_torso.png", 0, 17, 0.1f, true});
    Body_->CreateFrameAnimationCutTexture("pontiff_closing_torso", {"pontiff_closing_torso.png", 0, 14, 0.1f, true});
    Body_->GetTransform().SetLocalScale({900, 1100});
    Body_->GetTransform().SetLocalMove({0, 35});

    Face_->CreateFrameAnimationCutTexture("pontiff_openIdle_face", {"pontiff_openIdle_face.png", 0, 30, 0.2f, true});

    Face_->CreateFrameAnimationCutTexture("pontiff_opening_face", {"pontiff_opening_face.png", 0, 17, 0.1f, false});

    Face_->AnimationBindEnd("pontiff_opening_face",
                            [&](const FrameAnimation_DESC& _Info) { State_.ChangeState("OpenIdle"); });

    Face_->CreateFrameAnimationCutTexture("pontiff_closing_face", {"pontiff_closing_face.png", 0, 14, 0.1f, false});

    Face_->AnimationBindEnd("pontiff_closing_face",
                            [&](const FrameAnimation_DESC& _Info) { State_.ChangeState("CloseIdle"); });

    Face_->CreateFrameAnimationCutTexture("pontiff_openedIdle_face_DEATH",
                                          {"pontiff_openedIdle_face_DEATH.png", 0, 64, 0.1f, false});

    Face_->AnimationBindFrame(
        "pontiff_openedIdle_face_DEATH",
        [&](const FrameAnimation_DESC& _Info)
        {
            if (35 == _Info.CurFrame)
            {
                MainBody_->On();
                MainBody_->GetTransform().SetWorldPosition({GetTransform().GetWorldPosition().x,
                                                            GetTransform().GetWorldPosition().y - 200,
                                                            static_cast<int>(ACTORORDER::BeforeLayer5)});

                IsAscension_ = true;
            }
        });

    Face_->AnimationBindEnd("pontiff_openedIdle_face_DEATH", [&](const FrameAnimation_DESC& _Info) { IsLose_ = true; });

    Face_->GetTransform().SetLocalScale({950, 1300});
    Face_->GetTransform().SetLocalMove({0, 50, -1});

    PlatformSpawner_ = GetLevel()->CreateActor<PlatformSpawner>();

    State_.CreateStateMember("Appear",
                             std::bind(&Pontiff::AppearUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pontiff::AppearStart, this, std::placeholders::_1),
                             std::bind(&Pontiff::AppearEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Opening",
                             std::bind(&Pontiff::OpeningUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pontiff::OpeningStart, this, std::placeholders::_1),
                             std::bind(&Pontiff::OpeningEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Closing",
                             std::bind(&Pontiff::ClosingUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pontiff::ClosingStart, this, std::placeholders::_1),
                             std::bind(&Pontiff::ClosingEnd, this, std::placeholders::_1));

    State_.CreateStateMember("OpenIdle",
                             std::bind(&Pontiff::OpenIdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pontiff::OpenIdleStart, this, std::placeholders::_1),
                             std::bind(&Pontiff::OpenIdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("CloseIdle",
                             std::bind(&Pontiff::CloseIdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pontiff::CloseIdleStart, this, std::placeholders::_1),
                             std::bind(&Pontiff::CloseIdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&Pontiff::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pontiff::DeathStart, this, std::placeholders::_1),
                             std::bind(&Pontiff::DeathEnd, this, std::placeholders::_1));
    State_.ChangeState("Appear");

    GiantSword_ = GetLevel()->CreateActor<GiantSword>();
    GiantSword_->GetTransform().SetWorldPosition({1400, -600, static_cast<int>(ACTORORDER::BossMonster)});
    GiantSword_->SetPontiff(this);

    BossUI_ = GetLevel()->CreateActor<BossUI>();
    BossUI_->SetBossMonster(this);
    BossUI_->SetBossUI();
    BossUI_->AllOff();

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.0f, 1.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({150.f, 150.f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({-30, 70});
    BodyCollider_->Off();

    BloodEffect_ = GetLevel()->CreateActor<BloodSplatters>();
    BloodEffect_->GetRenderer()->Off();

    Symbol_[0] = GetLevel()->CreateActor<SymbolEffect>();
    Symbol_[0]->GetTransform().SetWorldScale({2, 2, 1});
    Symbol_[0]->GetTransform().SetWorldPosition({860, -600, static_cast<int>(ACTORORDER::BossMonsterEffect)});
    Symbol_[0]->Renderer_->Off();

    Symbol_[1] = GetLevel()->CreateActor<SymbolEffect>();
    Symbol_[1]->GetTransform().SetWorldScale({2, 2, 1});
    Symbol_[1]->GetTransform().SetWorldPosition({1660, -600, static_cast<int>(ACTORORDER::BossMonsterEffect)});
    Symbol_[1]->Renderer_->Off();
}

void Pontiff::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);
    SpellCast(_DeltaTime);

    if ("Death" != State_.GetCurStateStateName())
    {
        BossMonster::DamageCheck(10.f);
    }

    GameEngineDebug::OutPutString("Pontiff : " + State_.GetCurStateStateName());
}

void Pontiff::End() {}


void Pontiff::SpellCast(float _DeltaTime)
{
    switch (PervType_)
    {
        case SPELLTYPE::NONE:
            break;
        case SPELLTYPE::FIREBALL:
            if (true == FireBallSpawner_[5]->GetSpawnerEnd())
            {
                IsSpellCastStart_ = true;
            }
            break;
        case SPELLTYPE::TOXICCLOUD:
            if (true == ToxicCloudSpawner_->GetSpawnerEnd())
            {
                IsSpellCastStart_ = true;
            }
            break;
        case SPELLTYPE::LIGHTININGBOLT:
            if (true == LightiningBoltSpawner_->GetSpawnerEnd())
            {
                IsSpellCastStart_ = true;
            }
            break;
        case SPELLTYPE::MAGICMISSILE:
            if (true == MagicMissileSpawner_->GetSpawnerEnd())
            {
                IsSpellCastStart_ = true;
            }
            break;
        case SPELLTYPE::ANGUISHBEAM:
            if (true == AnguishBeamSpawner_->GetSpawnerEnd())
            {
                IsSpellCastStart_ = true;
            }
            break;
    }

    if (false == IsSpellCastStart_)
    {
        return;
    }

    int Num = Random_.RandomInt(0, static_cast<int>(SPELLTYPE::ANGUISHBEAM));

    CurType_ = static_cast<SPELLTYPE>(Num);

    Symbol_[0]->Renderer_->On();
    Symbol_[1]->Renderer_->On();

    switch (CurType_)
    {
        case SPELLTYPE::FIREBALL:
            FireBall(_DeltaTime);
            PervType_ = SPELLTYPE::FIREBALL;
            break;

        case SPELLTYPE::TOXICCLOUD:
            ToxicCloud();
            PervType_ = SPELLTYPE::TOXICCLOUD;
            break;

        case SPELLTYPE::LIGHTININGBOLT:
            LightiningBolt();
            PervType_ = SPELLTYPE::LIGHTININGBOLT;
            break;

        case SPELLTYPE::MAGICMISSILE:
            Magicmissile();
            PervType_ = SPELLTYPE::MAGICMISSILE;
            break;

        case SPELLTYPE::ANGUISHBEAM:
            AnguishBeam();
            PervType_ = SPELLTYPE::ANGUISHBEAM;
            break;
    }

    IsSpellCastStart_ = false;
}


void Pontiff::FireBall(float _DeltaTime)
{
    Symbol_[0]->SetColor(COLORTYPE::RED);
    Symbol_[1]->SetColor(COLORTYPE::RED);

    SpellTime_ += _DeltaTime;

    if (0.1f > SpellTime_)
    {
        SpellTime_ = 0.f;
        return;
    }

    ++SpellCount_;

    FireBallSpawner_[SpellCount_]->On();
    FireBallSpawner_[SpellCount_]->SetGround(ColMap_);
    FireBallSpawner_[SpellCount_]->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x + (50 * SpellCount_), GetTransform().GetWorldPosition().y + 500});
    FireBallSpawner_[SpellCount_]->SetDirection(Target_->GetTransform().GetWorldPosition()
                                                -FireBallSpawner_[SpellCount_]->GetTransform().GetWorldPosition());

    FireBallSpawner_[SpellCount_]->SetSpawnerEnd(false);

    if (5 >= SpellCount_)
    {
        return;
    }

    SpellCount_ = 0;
    CurType_ = SPELLTYPE::NONE;
}

void Pontiff::ToxicCloud()
{
    Symbol_[0]->SetColor(COLORTYPE::GREEN);
    Symbol_[1]->SetColor(COLORTYPE::GREEN);

    ToxicCloudSpawner_->On();
    ToxicCloudSpawner_->SetGround(ColMap_);
    ToxicCloudSpawner_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 500});

    ToxicCloudSpawner_->SetSpawnerEnd(false);

     CurType_ = SPELLTYPE::NONE;
}

void Pontiff::LightiningBolt()
{
    Symbol_[0]->SetColor(COLORTYPE::BLUE);
    Symbol_[1]->SetColor(COLORTYPE::BLUE);

    LightiningBoltSpawner_->On();
    LightiningBoltSpawner_->SetTarget(Target_);

    LightiningBoltSpawner_->SetSpawnerEnd(false);

    CurType_ = SPELLTYPE::NONE;
}

void Pontiff::Magicmissile()
{
    Symbol_[0]->SetColor(COLORTYPE::PURPLE);
    Symbol_[1]->SetColor(COLORTYPE::PURPLE);

    MagicMissileSpawner_->On();
    MagicMissileSpawner_->SetDirection(float4::LEFT);
    MagicMissileSpawner_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 100.f});

    MagicMissileSpawner_->SetSpawnerEnd(false);

    CurType_ = SPELLTYPE::NONE;
}

void Pontiff::AnguishBeam()
{
    Symbol_[0]->SetColor(COLORTYPE::PURPLE);
    Symbol_[1]->SetColor(COLORTYPE::PURPLE);

    AnguishBeamSpawner_->On();

    int Num = Random_.RandomInt(0, 1);

    if (1 == Num)
    {
        AnguishBeamSpawner_->CreateOnce();
    }

    else
    {
        AnguishBeamSpawner_->CreateTwice();
    }

    AnguishBeamSpawner_->SetSpawnerEnd(false);

    CurType_ = SPELLTYPE::NONE;
}


void Pontiff::CreateSpawner()
{
    for (size_t i = 0; i < 6; i++)
    {
        FireBallSpawner_[i] = GetLevel()->CreateActor<FireBallSpawner>();
        FireBallSpawner_[i]->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::BossMonster)});
        FireBallSpawner_[i]->SetGround(ColMap_);
        FireBallSpawner_[i]->Off();
    }

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

    AnguishBeamSpawner_ = GetLevel()->CreateActor<AnguishBeamSpawner>();
    AnguishBeamSpawner_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::BossMonster)});
    AnguishBeamSpawner_->Off();
}


void Pontiff::AppearStart(const StateInfo& _Info)
{
    Helmet_->ChangeFrameAnimation("pontiff_opening_helmet");
    Body_->ChangeFrameAnimation("pontiff_idle_torso");
    Face_->Off();
}

void Pontiff::AppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
    Time_ += _DeltaTime;

    if (3.f <= Time_)
    {
        Time_ = 0.f;
        State_.ChangeState("CloseIdle");
    }
}

void Pontiff::AppearEnd(const StateInfo& _Info)
{
    Face_->On();
    BossUI_->AllOn();
    BossUI_->SetBossName("마지막 기적의 아들");
    BossUI_->SetFontPosition({480, 590, -100.f});
    BossUI_->SetFontSize(35);

    PlatformSpawner_->CreateFristPattern();

    IsSpellCastStart_ = true;
}


void Pontiff::OpeningStart(const StateInfo& _Info)
{
    BodyCollider_->On();

    Helmet_->ChangeFrameAnimation("pontiff_opening_helmet");
    Body_->ChangeFrameAnimation("pontiff_opening_torso");
    Face_->ChangeFrameAnimation("pontiff_opening_face");
}

void Pontiff::OpeningUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pontiff::OpeningEnd(const StateInfo& _Info) {}


void Pontiff::OpenIdleStart(const StateInfo& _Info)
{
    Helmet_->ChangeFrameAnimation("pontiff_idle_helmet");
    Body_->ChangeFrameAnimation("pontiff_idle_torso");
    Face_->ChangeFrameAnimation("pontiff_openIdle_face");
}

void Pontiff::OpenIdleUpdate(float _DeltaTime, const StateInfo& _Info) {}
void Pontiff::OpenIdleEnd(const StateInfo& _Info) {}


void Pontiff::ClosingStart(const StateInfo& _Info)
{
    BodyCollider_->Off();

    Helmet_->ChangeFrameAnimation("pontiff_closing_helmet");
    Body_->ChangeFrameAnimation("pontiff_closing_torso");
    Face_->ChangeFrameAnimation("pontiff_closing_face");
}

void Pontiff::ClosingUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pontiff::ClosingEnd(const StateInfo& _Info) {}


void Pontiff::CloseIdleStart(const StateInfo& _Info)
{
    Face_->Off();
    Helmet_->ChangeFrameAnimation("pontiff_idle_helmet");
    Body_->ChangeFrameAnimation("pontiff_idle_torso");
}

void Pontiff::CloseIdleUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pontiff::CloseIdleEnd(const StateInfo& _Info) { Face_->On(); }


void Pontiff::DeathStart(const StateInfo& _Info)
{
    AscensionSpeed_ = 100;

    Face_->ChangeFrameAnimation("pontiff_openedIdle_face_DEATH");

    Body_->CurAnimationPauseOn();
    Helmet_->CurAnimationPauseOn();

    BossUI_->AllOff();
    BodyCollider_->Off();
    GiantSword_->Off();

    PlatformSpawner_->SetSpawnerOrder(SpawnerOrder::Death);
}

void Pontiff::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true == IsAscension_)
    {
        AscensionSpeed_ += 300.f * _DeltaTime;
        MainBody_->GetTransform().SetWorldMove(float4::UP * AscensionSpeed_ * _DeltaTime);
    }
}

void Pontiff::DeathEnd(const StateInfo& _Info) {}
