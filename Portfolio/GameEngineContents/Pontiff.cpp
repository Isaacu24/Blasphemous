#include "PreCompile.h"
#include "Pontiff.h"
#include "GiantSword.h"

Pontiff::Pontiff() {}

Pontiff::~Pontiff() {}

void Pontiff::Start()
{
    Helmet_   = CreateComponent<GameEngineTextureRenderer>();
    Body_     = CreateComponent<GameEngineTextureRenderer>();
    Face_     = CreateComponent<GameEngineTextureRenderer>();
    MainBody_ = CreateComponent<GameEngineTextureRenderer>();

    Helmet_->CreateFrameAnimationCutTexture("pontiff_idle_helmet", {"pontiff_idle_helmet.png", 0, 30, 0.2f, true});
    Helmet_->CreateFrameAnimationCutTexture("pontiff_opening_helmet",
                                            {"pontiff_opening_helmet.png", 0, 0, 0.0f, false});
    Helmet_->CreateFrameAnimationCutTexture("pontiff_closing_helmet",
                                            {"pontiff_closing_helmet.png", 0, 0, 0.0f, false});
    Helmet_->ChangeFrameAnimation("pontiff_idle_helmet");
    Helmet_->GetTransform().SetLocalScale({900, 1300});
    Helmet_->GetTransform().SetLocalMove({0, 15});

    Body_->CreateFrameAnimationCutTexture("pontiff_idle_torso", {"pontiff_idle_torso.png", 0, 30, 0.2f, true});
    Body_->CreateFrameAnimationCutTexture("pontiff_opening_torso", {"pontiff_opening_torso.png", 0, 17, 0.1f, true});
    Body_->CreateFrameAnimationCutTexture("pontiff_closing_torso", {"pontiff_closing_torso.png", 0, 14, 0.1f, true});
    Body_->ChangeFrameAnimation("pontiff_idle_torso");
    Body_->GetTransform().SetLocalScale({900, 1100});

    Face_->CreateFrameAnimationCutTexture("pontiff_openIdle_face", {"pontiff_openIdle_face.png", 0, 30, 0.2f, true});

    Face_->CreateFrameAnimationCutTexture("pontiff_opening_face", {"pontiff_opening_face.png", 0, 19, 0.1f, true});

    Face_->CreateFrameAnimationCutTexture("pontiff_closing_face", {"pontiff_closing_face.png", 0, 14, 0.1f, true});

    Face_->CreateFrameAnimationCutTexture("pontiff_openedIdle_face_DEATH",
                                          {"pontiff_openedIdle_face_DEATH.png", 0, 64, 0.2f, true});

    Face_->ChangeFrameAnimation("pontiff_openIdle_face");
    Face_->GetTransform().SetLocalScale({900, 1300});
    Face_->GetTransform().SetLocalMove({0, 15, -1});

    State_.CreateStateMember("Idle",
                             std::bind(&Pontiff::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pontiff::IdleStart, this, std::placeholders::_1),
                             std::bind(&Pontiff::IdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("SpellCast",
                             std::bind(&Pontiff::SpellCastUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pontiff::SpellCastStart, this, std::placeholders::_1),
                             std::bind(&Pontiff::SpellCastEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Hit",
                             std::bind(&Pontiff::HitUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pontiff::HitStart, this, std::placeholders::_1),
                             std::bind(&Pontiff::HitEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&Pontiff::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pontiff::DeathStart, this, std::placeholders::_1),
                             std::bind(&Pontiff::DeathEnd, this, std::placeholders::_1));
    State_.ChangeState("Idle");

    MainBody_->SetTexture("pontiff-boss-fight-spritesheet_8.png");
    MainBody_->GetTransform().SetLocalScale({500, 520});
    MainBody_->Off();

    GiantSword_ = GetLevel()->CreateActor<GiantSword>();
    GiantSword_->GetTransform().SetWorldPosition({1400, -600, static_cast<int>(ACTORORDER::BossMonster)});
}

void Pontiff::Update(float _DeltaTime) { State_.Update(_DeltaTime); }

void Pontiff::End() {}

void Pontiff::IdleStart(const StateInfo& _Info) {}

void Pontiff::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    Time_ += _DeltaTime;

    if (3.f <= Time_)
    {
        State_.ChangeState("Death");
    }
}

void Pontiff::IdleEnd(const StateInfo& _Info) {}

void Pontiff::HitStart(const StateInfo& _Info) {}

void Pontiff::HitUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pontiff::HitEnd(const StateInfo& _Info) {}

void Pontiff::SpellCastStart(const StateInfo& _Info) {}

void Pontiff::SpellCastUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pontiff::SpellCastEnd(const StateInfo& _Info) {}

void Pontiff::DeathStart(const StateInfo& _Info)
{
    MainBody_->On();
    MainBody_->GetTransform().SetWorldPosition({GetTransform().GetWorldPosition().x,
                                                GetTransform().GetWorldPosition().y - 200,
                                                static_cast<int>(ACTORORDER::BossMonster)});
}

void Pontiff::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
    AscensionSpeed_ += _DeltaTime * 350.f;

    MainBody_->GetTransform().SetWorldMove(float4::UP * AscensionSpeed_ * _DeltaTime);
}

void Pontiff::DeathEnd(const StateInfo& _Info) { AscensionSpeed_ = 0; }
