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
    Helmet_->GetTransform().SetLocalScale({950, 1300});
    Helmet_->GetTransform().SetLocalMove({0, 15});

    Body_->CreateFrameAnimationCutTexture("pontiff_idle_torso", {"pontiff_idle_torso.png", 0, 30, 0.2f, true});
    Body_->CreateFrameAnimationCutTexture("pontiff_opening_torso", {"pontiff_opening_torso.png", 0, 17, 0.1f, true});
    Body_->CreateFrameAnimationCutTexture("pontiff_closing_torso", {"pontiff_closing_torso.png", 0, 14, 0.1f, true});
    Body_->GetTransform().SetLocalScale({950, 1100});

    Face_->CreateFrameAnimationCutTexture("pontiff_openIdle_face", {"pontiff_openIdle_face.png", 0, 30, 0.2f, true});

    Face_->CreateFrameAnimationCutTexture("pontiff_opening_face", {"pontiff_opening_face.png", 0, 17, 0.1f, false});

    Face_->CreateFrameAnimationCutTexture("pontiff_closing_face", {"pontiff_closing_face.png", 0, 14, 0.1f, false});

    Face_->CreateFrameAnimationCutTexture("pontiff_openedIdle_face_DEATH",
                                          {"pontiff_openedIdle_face_DEATH.png", 0, 64, 0.2f, true});

    Face_->GetTransform().SetLocalScale({950, 1300});
    Face_->GetTransform().SetLocalMove({0, 15, -1});

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

    MainBody_->SetTexture("pontiff-boss-fight-spritesheet_8.png");
    MainBody_->GetTransform().SetLocalScale({500, 520});
    MainBody_->Off();

    GiantSword_ = GetLevel()->CreateActor<GiantSword>();
    GiantSword_->GetTransform().SetWorldPosition({1400, -600, static_cast<int>(ACTORORDER::BossMonster)});
}

void Pontiff::Update(float _DeltaTime) { State_.Update(_DeltaTime); }

void Pontiff::End() {}


void Pontiff::AppearStart(const StateInfo& _Info)
{
    Helmet_->ChangeFrameAnimation("pontiff_opening_helmet");
    Body_->ChangeFrameAnimation("pontiff_idle_torso");
    Face_->Off();
}

float Time_ = 0.f;
void  Pontiff::AppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
    Time_ += _DeltaTime;

    if (3.f <= Time_)
    {
        Time_ = 0.f;
        State_.ChangeState("Opening");
    }
}

void Pontiff::AppearEnd(const StateInfo& _Info) { Face_->On(); }

void Pontiff::OpeningStart(const StateInfo& _Info)
{
    Helmet_->ChangeFrameAnimation("pontiff_opening_helmet");
    Body_->ChangeFrameAnimation("pontiff_opening_torso");
    Face_->ChangeFrameAnimation("pontiff_opening_face");

    Face_->AnimationBindEnd("pontiff_opening_face", std::bind(&Pontiff::OpenAnimationEnd, this, std::placeholders::_1));
}

void Pontiff::OpeningUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pontiff::OpeningEnd(const StateInfo& _Info) {}

void Pontiff::OpenIdleStart(const StateInfo& _Info) 
{
    Helmet_->ChangeFrameAnimation("pontiff_idle_helmet");
    Body_->ChangeFrameAnimation("pontiff_idle_torso");
    Face_->ChangeFrameAnimation("pontiff_openIdle_face");

    Face_->AnimationBindEnd("pontiff_openIdle_face",
                            std::bind(&Pontiff::OpenIdleAnimationEnd, this, std::placeholders::_1));
}

void Pontiff::OpenIdleUpdate(float _DeltaTime, const StateInfo& _Info) {}
void Pontiff::OpenIdleEnd(const StateInfo& _Info) {}

void Pontiff::ClosingStart(const StateInfo& _Info) 
{
    Helmet_->ChangeFrameAnimation("pontiff_closing_helmet");
    Body_->ChangeFrameAnimation("pontiff_closing_torso");
    Face_->ChangeFrameAnimation("pontiff_closing_face");

    Face_->AnimationBindEnd("pontiff_closing_face",
                            std::bind(&Pontiff::CloseAnimationEnd, this, std::placeholders::_1));
}

void Pontiff::ClosingUpdate(float _DeltaTime, const StateInfo& _Info) {}
void Pontiff::ClosingEnd(const StateInfo& _Info) {}

void Pontiff::CloseIdleStart(const StateInfo& _Info) 
{
    Face_->Off();
    Helmet_->ChangeFrameAnimation("pontiff_idle_helmet");
    Body_->ChangeFrameAnimation("pontiff_idle_torso");

    Body_->AnimationBindEnd("pontiff_idle_torso",
                            std::bind(&Pontiff::CloseIdleAnimationEnd, this, std::placeholders::_1));
}

void Pontiff::CloseIdleUpdate(float _DeltaTime, const StateInfo& _Info) 
{

}
void Pontiff::CloseIdleEnd(const StateInfo& _Info) 
{ Face_->On(); }


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
