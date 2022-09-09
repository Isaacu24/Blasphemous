#include "PreCompile.h"
#include "PrieDieu.h"

PrieDieu::PrieDieu() 
{
}

PrieDieu::~PrieDieu() 
{
}

void PrieDieu::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationCutTexture("priedieu_stand_and_liton_anim", { "priedieu_stand_and_liton_anim.png", 1, 6, 0.1f, true });
	Renderer_->ChangeFrameAnimation("priedieu_stand_and_liton_anim");
	Renderer_->GetTransform().SetWorldScale({ 150, 300 });

    UICollider_ = CreateComponent<GameEngineCollision>();
    UICollider_->GetTransform().SetWorldScale({100.f, 200.f, 1.f});
    UICollider_->ChangeOrder(COLLISIONORDER::Object);
    UICollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});
    UICollider_->GetTransform().SetWorldMove({0, -50});

    UIRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    UIRenderer_->SetTexture("CT_Y.png");
    UIRenderer_->GetTransform().SetWorldScale({30, 30, 1});
    UIRenderer_->GetTransform().SetWorldMove({-7, 150});
    UIRenderer_->Off();
}

void PrieDieu::Update(float _DeltaTime)
{
    if (true == UICollider_->IsCollision(CollisionType::CT_OBB2D,
                               COLLISIONORDER::Player,
                               CollisionType::CT_OBB2D,
                               nullptr))
    {
        UIRenderer_->On();
    }

    else
    {
        UIRenderer_->Off();
    }
}

void PrieDieu::End()
{
}
