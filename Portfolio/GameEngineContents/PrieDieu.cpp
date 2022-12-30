#include "PreCompile.h"
#include "PrieDieu.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

PrieDieu::PrieDieu() {}

PrieDieu::~PrieDieu() {}

void PrieDieu::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    SetObjectType(ObjectType::PrieDieu);

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("priedieu_stand_and_liton_anim");

        MetaRenderer_->CreateMetaAnimation(
            "priedieu_stand_and_liton_anim",
            {"priedieu_stand_and_liton_anim.png", 1, static_cast<unsigned int>(Data.size() - 1), 0.06f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::GetInst()->Find("priedieu_upgrade2_stand_and_liton_anim");

        MetaRenderer_->CreateMetaAnimation(
            "priedieu_upgrade2_stand_and_liton_anim",
            {"priedieu_upgrade2_stand_and_liton_anim.png", 1, static_cast<unsigned int>(Data.size() - 1), 0.06f, true},
            Data);
    }

    MetaRenderer_->ChangeMetaAnimation("priedieu_stand_and_liton_anim");

    UICollider_ = CreateComponent<GameEngineCollision>();
    UICollider_->GetTransform().SetWorldScale({100.f, 200.f, 1.f});
    UICollider_->ChangeOrder(COLLISIONORDER::Object);
    UICollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});
    UICollider_->GetTransform().SetWorldMove({0, -50});

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
    UIRenderer_->GetTransform().SetWorldMove({-7, 150});
    UIRenderer_->Off();
}

void PrieDieu::Update(float _DeltaTime)
{
    if (true
        == UICollider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, nullptr))
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
    }

    else
    {
        UIRenderer_->Off();
    }
}

void PrieDieu::End() {}
