#include "PreCompile.h"
#include "ToxicCloud.h"

ToxicCloud::ToxicCloud() {}

ToxicCloud::~ToxicCloud() {}


void ToxicCloud::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_toxicOrb_create", {"pope_toxicOrb.png", 0, 8, 0.07f, false});
    Renderer_->AnimationBindEnd("pope_toxicOrb_create",
                                [&](const FrameAnimation_DESC& _Info) { State_.ChangeState("Shoot"); });

    Renderer_->CreateFrameAnimationCutTexture("pope_toxicOrb_shoot", {"pope_toxicOrb.png", 9, 24, 0.07f, true});
    Renderer_->CreateFrameAnimationCutTexture("pope_toxicOrb_broken", {"pope_toxicOrb.png", 25, 35, 0.07f, false});
    Renderer_->AnimationBindEnd("pope_toxicOrb_broken", [&](const FrameAnimation_DESC& _Info) { Renderer_->Off(); });

    Renderer_->GetTransform().SetWorldScale({300.f, 300.f, 1.f});
    Renderer_->SetPivot(PIVOTMODE::CENTER);

    ExplsionV1_ = CreateComponent<GameEngineTextureRenderer>();
    ExplsionV1_->CreateFrameAnimationCutTexture("Pope_toxicCloud", {"Pope_toxicCloud.png", 0, 25, 0.07f, false});
    ExplsionV1_->AnimationBindEnd("Pope_toxicCloud",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      ExplsionV1_->Off();
                                      Death();
                                  });

    ExplsionV1_->GetTransform().SetWorldScale({200.f, 200.f, 1.f});
    ExplsionV1_->SetPivot(PIVOTMODE::CENTER);
    ExplsionV1_->Off();

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::Projectile);
    Collider_->GetTransform().SetWorldScale({10.0f, 10.0f, 1.0f});

    State_.CreateStateMember("Idle",
                             std::bind(&ToxicCloud::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ToxicCloud::IdleStart, this, std::placeholders::_1));

    State_.CreateStateMember("Shoot",
                             std::bind(&ToxicCloud::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ToxicCloud::ShootStart, this, std::placeholders::_1));

    State_.CreateStateMember(
        "Explosion",
        std::bind(&ToxicCloud::ExplosionUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&ToxicCloud::ExplosionStart, this, std::placeholders::_1));

    State_.ChangeState("Idle");

    Speed_ = 100.f;
}

void ToxicCloud::Update(float _DeltaTime)
{
    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                              -(GetTransform().GetWorldPosition().y));

    if (Color.CompareInt4D(float4::BLACK) && "Explosion" != State_.GetCurStateStateName())
    {
        State_.ChangeState("Explosion");
    }

    // if (false == IsExplosion_)
    //{
    //     Collider_->IsCollision(CollisionType::CT_OBB2D,
    //                            COLLISIONORDER::Player,
    //                            CollisionType::CT_OBB2D,
    //                            std::bind(&ToxicCloud::Explosion, this, std::placeholders::_1,
    //                            std::placeholders::_2));
    // }

    if (false == IsExplosion_)
    {
        Collider_->IsCollision(CollisionType::CT_OBB2D,
                               COLLISIONORDER::Platform,
                               CollisionType::CT_OBB2D,
                               std::bind(&ToxicCloud::Explosion, this, std::placeholders::_1, std::placeholders::_2));
    }


    State_.Update(_DeltaTime);
}

void ToxicCloud::End() {}

void ToxicCloud::IdleStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("pope_toxicOrb_create"); }

void ToxicCloud::IdleUpdate(float _DeltaTime, const StateInfo& _Info) { BackMove(_DeltaTime); }


void ToxicCloud::ShootStart(const StateInfo& _Info) { Renderer_->ChangeFrameAnimation("pope_toxicOrb_shoot"); }

void ToxicCloud::ShootUpdate(float _DeltaTime, const StateInfo& _Info) { Shoot(_DeltaTime); }

void ToxicCloud::ExplosionStart(const StateInfo& _Info)
{
    ExplsionV1_->On();
    // Collider_->ChangeOrder(COLLISIONORDER::Gas);
    Collider_->GetTransform().SetWorldScale({100.0f, 100.0f, 1.0f});

    Renderer_->ChangeFrameAnimation("pope_toxicOrb_broken");
    ExplsionV1_->ChangeFrameAnimation("Pope_toxicCloud");
}

void ToxicCloud::ExplosionUpdate(float _DeltaTime, const StateInfo& _Info) {}
