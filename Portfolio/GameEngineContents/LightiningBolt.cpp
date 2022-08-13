#include "PreCompile.h"
#include "LightiningBolt.h"

LightiningBolt::LightiningBolt() 
{
}

LightiningBolt::~LightiningBolt() 
{
}

void LightiningBolt::Start() 
{ 
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("lightningBolt_Tileable_fxs", {"lightningBolt_Tileable_fxs.png", 0, 76, 0.05f, false});
    Renderer_->ChangeFrameAnimation("lightningBolt_Tileable_fxs");
    Renderer_->AnimationBindEnd("lightningBolt_Tileable_fxs", std::bind(&LightiningBolt::StrikeEnd, this, std::placeholders::_1));
    Renderer_->GetTransform().SetLocalScale({200, 700});
    Renderer_->SetPivot(PIVOTMODE::CENTER);

    //FXSRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    //FXSRenderer_->CreateFrameAnimationCutTexture("lightningBolt_Tileable_fxs", {"lightningBolt_Tileable_fxs.png", 0, 76, 0.05f, false});
    //FXSRenderer_->ChangeFrameAnimation("lightningBolt_Tileable_fxs");
    //FXSRenderer_->AnimationBindEnd("lightningBolt_fxs",lightningBolt_fxs
    //                            std::bind(&LightiningBolt::StrikeEnd, this, std::placeholders::_1));
    //FXSRenderer_->GetTransform().SetLocalScale({300, 1000});
    //FXSRenderer_->SetPivot(PIVOTMODE::CENTER);

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::Projectile);
    Collider_->GetTransform().SetWorldScale({10.0f, 100.0f, 1.0f});
}

void LightiningBolt::Update(float _DeltaTime) 
{
   /* Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::Player,
                           CollisionType::CT_OBB2D,
                           std::bind(&LightiningBolt::Explosion, this, std::placeholders::_1, std::placeholders::_2));*/
}

void LightiningBolt::End() {}
