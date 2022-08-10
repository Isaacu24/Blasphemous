#include "PreCompile.h"
#include "Pope.h"

Pope::Pope() {}

Pope::~Pope() {}

void Pope::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_idle", {"pope_idle.png", 0, 12, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("pope_appear", {"pope_appear.png", 0, 14, 0.1f, false});
    Renderer_->CreateFrameAnimationCutTexture("pope_hitReaction", {"pope_hitReaction.png", 0, 10, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("pope_spellCast", {"pope_spellCast.png", 0, 53, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("pope_spellCast_FXS",
                                              {"pope_spellCast_FXS.png", 0, 53, 0.1f, true});  //ÀÌÆåÆ®
    Renderer_->CreateFrameAnimationCutTexture("pope_vanishing", {"pope_vanishing.png", 0, 13, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("pope_death", {"pope_death.png", 0, 35, 0.1f, true});
    Renderer_->GetTransform().SetWorldScale({250, 250});
    Renderer_->SetPivot(PIVOTMODE::BOT);

    State_.CreateStateMember("Idle",
                             std::bind(&Pope::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pope::IdleStart, this, std::placeholders::_1),
                             std::bind(&Pope::IdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Appear",
                             std::bind(&Pope::AppearUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Pope::AppearStart, this, std::placeholders::_1),
                             std::bind(&Pope::AppearEnd, this, std::placeholders::_1));

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
    DetectCollider_->GetTransform().SetWorldScale({500.0f, 500.0f, 1.0f});
}

void Pope::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    if (true == DetectCollider_->IsCollision(
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

void Pope::IdleStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("pope_idle"); }

void Pope::IdleUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::IdleEnd(const StateInfo& _Info) 
{
    int a = 0; 
}

void Pope::AppearStart(const StateInfo& _Info) 
{ 
    Renderer_->ChangeFrameAnimation("pope_appear"); 

    Renderer_->ChangeFrameAnimation("pope_appear");
    Renderer_->AnimationBindEnd("pope_appear", std::bind(&Pope::ChangeIdle, this, std::placeholders::_1));
}

void Pope::AppearUpdate(float _DeltaTime, const StateInfo& _Info) 
{
}

void Pope::AppearEnd(const StateInfo& _Info) 
{ 
}

void Pope::VanishingStart(const StateInfo& _Info) {}

void Pope::VanishingUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::VanishingEnd(const StateInfo& _Info) {}

void Pope::SpellCastStart(const StateInfo& _Info) {}

void Pope::SpellCastUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::SpellCastEnd(const StateInfo& _Info) {}

void Pope::HitStart(const StateInfo& _Info) {}

void Pope::HitUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::HitEnd(const StateInfo& _Info) {}

void Pope::DeathStart(const StateInfo& _Info) {}

void Pope::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Pope::DeathEnd(const StateInfo& _Info) {}
