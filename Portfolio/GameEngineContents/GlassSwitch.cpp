#include "PreCompile.h"
#include "GlassSwitch.h"
#include "SideFence.h"

GlassSwitch::GlassSwitch() {}

GlassSwitch::~GlassSwitch() {}

void GlassSwitch::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("glassSwitch", {"glassSwitch.png", 0, 0, 0.1f, false});
    Renderer_->CreateFrameAnimationCutTexture("glassSwitchBroken", {"glassSwitch.png", 0, 22, 0.1f, false});
    Renderer_->AnimationBindFrame("glassSwitchBroken",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      if (1 == _Info.CurFrame)
                                      {
                                          SoundPlayer_
                                              = GameEngineSound::SoundPlayControl("GLASS_PLATFORM_COLLAPSE.wav");
                                          SoundPlayer_.Volume(0.3f);
                                      }
                                  });
    Renderer_->AnimationBindEnd("glassSwitchBroken", [&](const FrameAnimation_DESC& _Info) { Collider_->Off(); });

    Renderer_->GetTransform().SetWorldScale({180, 330});
    Renderer_->ChangeFrameAnimation("glassSwitch");

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::GlassSwitch);
    Collider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});
    Collider_->GetTransform().SetWorldScale({50, 50});
    Collider_->GetTransform().SetWorldMove({0, 100.f});
}

void GlassSwitch::Update(float _DeltaTime)
{
    if (false == Collider_->IsUpdate())
    {
        return;
    }

    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::PlayerAttack,
                           CollisionType::CT_OBB2D,
                           std::bind(&GlassSwitch::On, this, std::placeholders::_1, std::placeholders::_2));
}

void GlassSwitch::End() {}

bool GlassSwitch::On(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    Collider_->Off();
    Renderer_->ChangeFrameAnimation("glassSwitchBroken");

    if (nullptr != Fence_)
    {
        Fence_->SetFenceState("Descending");
    }

    return true;
}
