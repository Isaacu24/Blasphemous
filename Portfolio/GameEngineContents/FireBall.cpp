#include "PreCompile.h"
#include "FireBall.h"

FireBall::FireBall() {}

FireBall::~FireBall() {}


void FireBall::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_fireBall", {"pope_fireBall.png", 0, 9, 0.1f, true});
    Renderer_->CreateFrameAnimationFolder("FireBallExplosion", FrameAnimation_DESC{"FireBallExplosion", 0.1f, false});
    Renderer_->ChangeFrameAnimation("pope_fireBall");
    Renderer_->GetTransform().SetWorldScale({300.f, 300.f});
    Renderer_->SetPivot(PIVOTMODE::CENTER);

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::Projectile);
    Collider_->GetTransform().SetWorldScale({10.0f, 10.0f, 1.0f});

    State_.CreateStateMember("Shoot",
                             std::bind(&FireBall::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&FireBall::ShootStart, this, std::placeholders::_1));

    State_.CreateStateMember("Explosion",
                             std::bind(&FireBall::ExplosionUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&FireBall::ExplosionStart, this, std::placeholders::_1));

    State_.ChangeState("Shoot");
}

void FireBall::Update(float _DeltaTime)
{
    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                              -(GetTransform().GetWorldPosition().y));

    if (Color.CompareInt4D(float4::BLACK))
    {
        State_.ChangeState("Explosion");
    }

    if (false == IsExplosion_)
    {
        Collider_->IsCollision(CollisionType::CT_OBB2D,
                               COLLISIONORDER::Player,
                               CollisionType::CT_OBB2D,
                               std::bind(&FireBall::Explosion, this, std::placeholders::_1, std::placeholders::_2));
    }

    State_.Update(_DeltaTime);
}

void FireBall::End() {}

void FireBall::ShootStart(const StateInfo& _Info) {}

void FireBall::ShootUpdate(float _DeltaTime, const StateInfo& _Info) { Shoot(_DeltaTime); }

void FireBall::ExplosionStart(const StateInfo& _Info)
{
    Renderer_->ChangeFrameAnimation("FireBallExplosion");

    Renderer_->ChangeFrameAnimation("FireBallExplosion");
    Renderer_->AnimationBindEnd("FireBallExplosion", std::bind(&FireBall::ExplosionEnd, this, std::placeholders::_1));

    Renderer_->GetColorData().MulColor = float4{0.88f, 0.4f, 0.33f, 1.0f};

    Renderer_->GetTransform().SetWorldScale({100.f, 100.f});
}

void FireBall::ExplosionUpdate(float _DeltaTime, const StateInfo& _Info) {}
