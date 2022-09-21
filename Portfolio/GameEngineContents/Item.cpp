#include "PreCompile.h"
#include "Item.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

Item::Item() {}

Item::~Item() {}


void Item::Start()
{
    GetTransform().SetWorldScale({2.f, 2.f, 1});

    ItemRenderer_ = CreateComponent<GameEngineTextureRenderer>();

    ItemCollider_ = CreateComponent<GameEngineCollision>();
    ItemCollider_->GetTransform().SetWorldScale({30.f, 50.f, 1.f});
    ItemCollider_->ChangeOrder(COLLISIONORDER::Item);
    ItemCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});
    ItemCollider_->GetTransform().SetWorldMove({0, 0});

    UIRenderer_ = CreateComponent<GameEngineTextureRenderer>();

    if (0 < GameEngineInput::GetInst()->GetInputState().dwPacketNumber)
    {
        UIRenderer_->SetTexture("CT_Y.png");
    }

    else
    {
        UIRenderer_->SetTexture("KB_E.png");
    }

    UIRenderer_->GetTransform().SetWorldScale({30, 30, 1});
    UIRenderer_->GetTransform().SetWorldMove({0, 70});
    UIRenderer_->Off();
}

void Item::Update(float _DeltaTime) { PlayerCheck(); }

void Item::PlayerCheck()
{
    if (true
        == ItemCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, nullptr))
    {
        UIRenderer_->On();
        
        if (0 < GameEngineInput::GetInst()->GetInputState().dwPacketNumber)
        {
            UIRenderer_->SetTexture("CT_Y.png");
        }

        else
        {
            UIRenderer_->SetTexture("KB_E.png");
        }

        IsPlayerCollide_ = true;
    }

    else
    {
        UIRenderer_->Off();
        IsPlayerCollide_ = false;
    }
}

void Item::End() {}
