#include "PreCompile.h"
#include "DaggerLady.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

DaggerLady::DaggerLady() {}

DaggerLady::~DaggerLady() {}


void DaggerLady::Start()
{
    SetObjectType(ObjectType::NPC);

    GetTransform().SetWorldScale({2, 2, 1});
    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("daggerLady_idle_anim");

        MetaRenderer_->CreateMetaAnimation(
            "daggerLady_idle_anim",
            {"daggerLady_idle_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.06f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("daggerchestlady_vanishing_animV2");

        MetaRenderer_->CreateMetaAnimation(
            "daggerchestlady_vanishing_animV2",
            {"daggerchestlady_vanishing_animV2.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.06f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("daggerchestlady_vanishing_animV2",
                                        [&](const FrameAnimation_DESC& _Info) { Death(); });
    }

    MetaRenderer_->ChangeMetaAnimation("daggerLady_idle_anim");

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
    UIRenderer_->GetTransform().SetWorldMove({0, 200});
    UIRenderer_->Off();

    MessageUI_ = GetLevel()->CreateActor<MessageUI>();
    MessageUI_->CreateLine("You have freed His Holiness from his afflicted torment, and now he walks by the old "
                           "processions\non ther other side of the Dream.");
    MessageUI_->CreateLine("And now your final communion with the Miracle awaits.");
    MessageUI_->CreateLine("Only you will be able to know how much of it has seeped into your gulity hearts.");
    MessageUI_->SetFontColor(float4{0.63f, 0.6f, 0.55f});
    MessageUI_->SetBackgroudAlpha(1.0f);
    MessageUI_->Off();

    MessageUI_->SetMassageEndEvent(3,
                                   [&]()
                                   {
                                       MetaRenderer_->ChangeMetaAnimation("daggerchestlady_vanishing_animV2");
                                       Penitent::GetMainPlayer()->SetIsFreezeEnd(true);
                                   });
}

void DaggerLady::Update(float _Update)
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

void DaggerLady::End() {}