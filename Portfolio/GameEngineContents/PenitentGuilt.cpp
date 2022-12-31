#include "PreCompile.h"
#include "PenitentGuilt.h"
#include "LineUIActor.h"

PenitentGuilt::PenitentGuilt() {}

PenitentGuilt::~PenitentGuilt() {}

// GameEngineTexture::Cut("guiltSystem_blinkFxs.png", 7, 5);
// GameEngineTexture::Cut("guiltDropVanish.png", 5, 2);

void PenitentGuilt::Start()
{
    SetObjectType(ObjectType::Guilt);

    Renderer_ = CreateComponent<GameEngineTextureRenderer>();

    Renderer_->CreateFrameAnimationCutTexture("guiltSystem_blinkFxs", {"guiltSystem_blinkFxs.png", 0, 32, 0.07f, true});
    Renderer_->CreateFrameAnimationCutTexture("guiltDropVanish", {"guiltDropVanish.png", 0, 7, 0.07f, true});

    Renderer_->AnimationBindEnd("guiltDropVanish",
                                [&](const FrameAnimation_DESC&)
                                {
                                    StageBase* CurStage = dynamic_cast<StageBase*>(GetLevel());
                                    CurStage->DestroyGuilt();
                                    Death();
                                });

    Renderer_->ChangeFrameAnimation("guiltSystem_blinkFxs");
    Renderer_->GetTransform().SetWorldScale({200, 200, 1});
    Renderer_->SetPivot(PIVOTMODE::BOT);

    UICollider_ = CreateComponent<GameEngineCollision>();
    UICollider_->GetTransform().SetWorldScale({100.f, 200.f, 1.f});
    UICollider_->ChangeOrder(COLLISIONORDER::Object);
    UICollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});
    UICollider_->GetTransform().SetWorldMove({0, 100});

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
    UIRenderer_->GetTransform().SetWorldPosition({0, 0, AfterLayerZ});
    UIRenderer_->GetTransform().SetWorldMove({0, 220});
    UIRenderer_->Off();
}
 
void PenitentGuilt::Update(float _DeltaTime)
{
    if (true == Interaction_)
    {
        return;
    }

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

void PenitentGuilt::End() {}


void PenitentGuilt::DestroyGuilt()
{
    UICollider_->Off();
    UIRenderer_->Off();
    Renderer_->ChangeFrameAnimation("guiltDropVanish");

    LineUIActor* UI = GetLevel()->CreateActor<LineUIActor>();
    UI->GetTransform().SetWorldMove({0, 500});
    UI->GetUIRenderer()->GetColorData().MulColor.a = 1.0f;
    UI->SetFontSize(35);
    UI->SetFontPosition({640, 160});
    UI->CreateLine("Guilt has been restored.");
    UI->SpeechStart();

    Interaction_ = true;
}
