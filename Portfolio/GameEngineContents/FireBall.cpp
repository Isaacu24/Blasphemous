#include "PreCompile.h"
#include "FireBall.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

FireBall::FireBall() {}

FireBall::~FireBall() {}


void FireBall::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_fireBall", {"pope_fireBall.png", 0, 9, 0.07f, true});

    Renderer_->ChangeFrameAnimation("pope_fireBall");
    Renderer_->GetTransform().SetWorldScale({300.f, 350.f, 1.f});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("fireTrap_projectile_destroyed");

        MetaRenderer_->CreateMetaAnimation(
            "fireTrap_projectile_destroyed",
            {"fireTrap_projectile_destroyed.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("fireTrap_projectile_destroyed",
                                        [&](const FrameAnimation_DESC& _Info) { Death(); });
    }

    MetaRenderer_->Off();

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

void FireBall::Update(float _DeltaTime) { State_.Update(_DeltaTime); }

void FireBall::End() {}

void FireBall::ShootStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("FIREBALL_FLY.wav");
}

void FireBall::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
    Shoot(_DeltaTime);

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

    float4 Distance    = StartPos_ - GetTransform().GetWorldPosition();
    float4 ABSDistance = float4::ABS3DReturn(Distance);

    if (3000.f < ABSDistance.x || 3000.f < ABSDistance.y)
    {
        Death();
    }
}

void FireBall::ExplosionStart(const StateInfo& _Info)
{
    SoundPlayer_ = GameEngineSound::SoundPlayControl("FIRE_BALL_EXPLODE.wav");

    Renderer_->Off();
    Collider_->Off();

    GetTransform().SetWorldScale({2.5f, 2.5f, 1});
    GetTransform().SetWorldRotation({0.f, 0.f, 0});
    MetaRenderer_->On();

    MetaRenderer_->ChangeMetaAnimation("fireTrap_projectile_destroyed");
    MetaRenderer_->GetColorData().MulColor = float4{0.88f, 0.4f, 0.33f, 1.0f};
}

void FireBall::ExplosionUpdate(float _DeltaTime, const StateInfo& _Info) {}
