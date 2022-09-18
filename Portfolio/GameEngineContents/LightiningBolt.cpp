    #include "PreCompile.h"
#include "LightiningBolt.h"

LightiningBolt::LightiningBolt()
    : IsStrike_(false)
{}

LightiningBolt::~LightiningBolt() {}

void LightiningBolt::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("lightningBolt_Tileable_fxs",
                                              {"lightningBolt_Tileable_fxs.png", 0, 76, 0.055f, false});
    Renderer_->ChangeFrameAnimation("lightningBolt_Tileable_fxs");
    Renderer_->AnimationBindFrame("lightningBolt_Tileable_fxs",
                                std::bind(&LightiningBolt::Strike, this, std::placeholders::_1));
    Renderer_->AnimationBindEnd("lightningBolt_Tileable_fxs",
                                std::bind(&LightiningBolt::StrikeEnd, this, std::placeholders::_1));
    Renderer_->GetTransform().SetLocalScale({270, 570});
    Renderer_->SetPivot(PIVOTMODE::CENTER);

    // FXSRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    // FXSRenderer_->CreateFrameAnimationCutTexture("lightningBolt_Tileable_fxs", {"lightningBolt_Tileable_fxs.png", 0,
    // 76, 0.05f, false}); FXSRenderer_->ChangeFrameAnimation("lightningBolt_Tileable_fxs");
    // FXSRenderer_->AnimationBindEnd("lightningBolt_fxs",lightningBolt_fxs
    //                             std::bind(&LightiningBolt::StrikeEnd, this, std::placeholders::_1));
    // FXSRenderer_->GetTransform().SetLocalScale({300, 1000});
    // FXSRenderer_->SetPivot(PIVOTMODE::CENTER);

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->ChangeOrder(COLLISIONORDER::BossMonsterAttack1);
    Collider_->GetTransform().SetWorldScale({30.0f, 700.0f, 1.0f});
    Collider_->Off();
}

void LightiningBolt::Update(float _DeltaTime)
{
    //if (false == IsStrike_)
    //{
    //    Collider_->IsCollision(
    //        CollisionType::CT_OBB2D,
    //        COLLISIONORDER::Player,
    //        CollisionType::CT_OBB2D,
    //        std::bind(&LightiningBolt::Explosion, this, std::placeholders::_1, std::placeholders::_2));
    //}
    /* Collider_->IsCollision(CollisionType::CT_OBB2D,
                            COLLISIONORDER::Player,
                            CollisionType::CT_OBB2D,
                            std::bind(&LightiningBolt::Explosion, this, std::placeholders::_1,
       std::placeholders::_2));*/
}

void LightiningBolt::End() {}
