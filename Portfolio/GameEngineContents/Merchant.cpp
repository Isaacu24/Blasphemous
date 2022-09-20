#include "PreCompile.h"
#include "Merchant.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

Merchant::Merchant()
    : HP_(100)
{}

Merchant::~Merchant() {}

void Merchant::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ladrona_idle_anim");

        MetaRenderer_->CreateMetaAnimation(
            "ladrona_idle_anim",
            {"ladrona_idle_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ladrona_death_anim_0");

        MetaRenderer_->CreateMetaAnimation(
            "ladrona_death_anim_0",
            {"ladrona_death_anim_0.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, false},
            Data);

    }


    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ladrona_hit_reaction_anim");

        MetaRenderer_->CreateMetaAnimation(
            "ladrona_hit_reaction_anim",
            {"ladrona_hit_reaction_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, false},
            Data);
        
        MetaRenderer_->AnimationBindEnd("ladrona_hit_reaction_anim",
                                        [&](const FrameAnimation_DESC& _Info) { State_.ChangeState("Idle"); });
    }
    
    MetaRenderer_->ChangeMetaAnimation("ladrona_idle_anim");
    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->GetTransform().SetWorldScale({40.f, 80.f, 1.f});
    BodyCollider_->ChangeOrder(COLLISIONORDER::MonsterBody);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldMove({0, 30});

    State_.CreateStateMember("Idle",
                             std::bind(&Merchant::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Merchant::IdleStart, this, std::placeholders::_1),
                             std::bind(&Merchant::IdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Hit",
                             std::bind(&Merchant::HitUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Merchant::HitStart, this, std::placeholders::_1),
                             std::bind(&Merchant::HitEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&Merchant::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Merchant::DeathStart, this, std::placeholders::_1),
                             std::bind(&Merchant::DeathEnd, this, std::placeholders::_1));

    State_.ChangeState("Idle");
}

void Merchant::Update(float _Update)
{
    if (false
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;

        MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
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
        State_.ChangeState("Hit");

        HP_ -= 50.f;

        MetaRenderer_->GetColorData().PlusColor = float4{1.5f, 1.5f, 1.5f, 0.0f};
    }

    if (0 >= HP_)
    {
        State_.ChangeState("Death");
    }
}

void Merchant::End() {}


void Merchant::IdleStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("ladrona_idle_anim"); }

void Merchant::IdleUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Merchant::IdleEnd(const StateInfo& _Info) {}


void Merchant::HitStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("ladrona_hit_reaction_anim"); }

void Merchant::HitUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Merchant::HitEnd(const StateInfo& _Info) {}


void Merchant::DeathStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("ladrona_death_anim_0"); }

void Merchant::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Merchant::DeathEnd(const StateInfo& _Info) {}
