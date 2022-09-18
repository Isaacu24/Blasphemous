#include "PreCompile.h"
#include "Deogracias.h"

Deogracias::Deogracias() {}

Deogracias::~Deogracias() {}

void Deogracias::ChangeFrontAnimation()
{
    Renderer_->ChangeFrameAnimation("Deosgracias_front");

    SetObjectType(ObjectType::NPC);
}

void Deogracias::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->GetTransform().SetWorldScale({200, 400});
    Renderer_->CreateFrameAnimationCutTexture("Deosgracias_idle", {"Deosgracias_idle.png", 0, 18, 0.1f, true});
    Renderer_->CreateFrameAnimationCutTexture("Deosgracias_front", {"Deosgracias_front.png", 0, 78, 0.1f, true});
    Renderer_->ChangeFrameAnimation("Deosgracias_idle");

    UICollider_ = CreateComponent<GameEngineCollision>();
    UICollider_->GetTransform().SetWorldScale({100.f, 300.f, 1.f});
    UICollider_->ChangeOrder(COLLISIONORDER::Object);
    UICollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});
    UICollider_->GetTransform().SetWorldMove({0, -100});

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
    UIRenderer_->GetTransform().SetWorldPosition({0, 0, AfterParallaxZ});
    UIRenderer_->GetTransform().SetWorldMove({0, 150});
    UIRenderer_->Off();

    MessageUI_ = GetLevel()->CreateActor<MessageUI>();
    MessageUI_->CreateLine("You have freed His Holiness from his afflicted torment, and now he walks by the old "
                           "processions\non ther other side of the Dream.");
    MessageUI_->CreateLine("And now your final communion with the Miracle awaits.");
    MessageUI_->CreateLine("Only you will be able to know how much of it has seeped into your gulity hearts.");
    MessageUI_->SetFontColor(float4{0.63f, 0.6f, 0.55f});
    MessageUI_->Off();

    MessageUI_->SetMassageEndEvent(3,
                                   [&]()
                                   {
                                       Penitent::GetMainPlayer()->SetIsFreezeEnd(true);
                                       MessageUI_->Off();
                                   });
}

void Deogracias::Update(float _DeltaTime)
{
    if (true == IsSpeech_ && false == Interaction_)
    {
        MessageUI_->On();
        MessageUI_->SpeechStart();
        Interaction_ = true;

        UIRenderer_->Off();
    }

    if (true == Interaction_)
    {
        return;
    }

    if (true
        == UICollider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, nullptr))
    {
        UIRenderer_->On();
        UIRenderer_->GetTransform().PixWorldPositiveX();

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

void Deogracias::End() {}
