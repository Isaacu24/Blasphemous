#include "PreCompile.h"
#include "PreCompile.h"
#include "GlassSwitch.h"

GlassSwitch::GlassSwitch() {}

GlassSwitch::~GlassSwitch() {}

void GlassSwitch::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("glassSwitch", {"glassSwitch.png", 0, 0, 0.1f, false});
    Renderer_->CreateFrameAnimationCutTexture("glassSwitchBroken", {"glassSwitch.png", 0, 22, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("glassSwitchBrokenEnd", {"glassSwitch.png", 22, 22, 0.1f, false});
    Renderer_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Object)});
    Renderer_->GetTransform().SetWorldScale({180, 330});
    Renderer_->ChangeFrameAnimation("glassSwitchBrokenEnd");

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->GetTransform().SetWorldScale({50, 50});
}

void GlassSwitch::Update(float _DeltaTime) 
{

}

void GlassSwitch::End() {}
