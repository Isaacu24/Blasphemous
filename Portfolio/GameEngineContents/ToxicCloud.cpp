#include "PreCompile.h"
#include "ToxicCloud.h"

ToxicCloud::ToxicCloud() {}

ToxicCloud::~ToxicCloud() {}

void ToxicCloud::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_toxicOrb", {"pope_toxicOrb.png", 0, 35, 0.07f, false});
    Renderer_->GetTransform().SetWorldScale({300.f, 300.f, 1.f});
    Renderer_->SetPivot(PIVOTMODE::CENTER);

    ExplsionV1_ = CreateComponent<GameEngineTextureRenderer>();
    ExplsionV1_->CreateFrameAnimationCutTexture("Pope_toxicCloud", {"Pope_toxicCloud.png", 0, 25, 0.1f, false});
    ExplsionV1_->GetTransform().SetWorldScale({300.f, 300.f, 1.f});
    ExplsionV1_->SetPivot(PIVOTMODE::CENTER);
    ExplsionV1_->Off();

    ExplsionV2_ = CreateComponent<GameEngineTextureRenderer>();
    ExplsionV2_->CreateFrameAnimationCutTexture("pope_toxicCloudv2", {"pope_toxicCloudv2.png", 0, 15, 0.07f, false});
    ExplsionV2_->GetTransform().SetWorldScale({300.f, 300.f, 1.f});
    ExplsionV2_->SetPivot(PIVOTMODE::CENTER);
    ExplsionV2_->Off();

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::Projectile);
    Collider_->GetTransform().SetWorldScale({10.0f, 10.0f, 1.0f});

    State_.CreateStateMember("Shoot",
                             std::bind(&ToxicCloud::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&ToxicCloud::ShootStart, this, std::placeholders::_1));

    State_.CreateStateMember(
        "Explosion",
        std::bind(&ToxicCloud::ExplosionUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&ToxicCloud::ExplosionStart, this, std::placeholders::_1));

    State_.ChangeState("Shoot");    
}

void ToxicCloud::Update(float _DeltaTime)
{
    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                              -(GetTransform().GetWorldPosition().y));

    if (Color.CompareInt4D(float4::BLACK) 
        && "Explosion" != State_.GetCurStateStateName())
    {
        State_.ChangeState("Explosion");
    }

    if (false == IsExplosion_)
    {
        Collider_->IsCollision(CollisionType::CT_OBB2D,
                               COLLISIONORDER::Player,
                               CollisionType::CT_OBB2D,
                               std::bind(&ToxicCloud::Explosion, this, std::placeholders::_1, std::placeholders::_2));
    }

    State_.Update(_DeltaTime);
}

void ToxicCloud::End() {}

void ToxicCloud::ShootStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("pope_toxicOrb");
    Renderer_->AnimationBindEnd("pope_toxicOrb",
                                std::bind(&ToxicCloud::CloudEnd, this, std::placeholders::_1, Renderer_));
}

void ToxicCloud::ShootUpdate(float _DeltaTime, const StateInfo& _Info) { Shoot(_DeltaTime); }

void ToxicCloud::ExplosionStart(const StateInfo& _Info)
{
    Renderer_->Off();

    ExplsionV1_->On();
    ExplsionV2_->On();

    ExplsionV1_->ChangeFrameAnimation("Pope_toxicCloud");
    ExplsionV1_->AnimationBindEnd("Pope_toxicCloud", std::bind(&ToxicCloud::ExplosionEnd, this, std::placeholders::_1));

    ExplsionV2_->ChangeFrameAnimation("Pope_toxicCloudV2");
    ExplsionV2_->AnimationBindEnd("Pope_toxicCloudV2",
                                  std::bind(&ToxicCloud::CloudEnd, this, std::placeholders::_1, ExplsionV2_));
}

void ToxicCloud::ExplosionUpdate(float _DeltaTime, const StateInfo& _Info) {}
