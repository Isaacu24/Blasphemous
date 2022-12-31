#include "PreCompile.h"
#include "Deogracias.h"

Deogracias::Deogracias() {}

Deogracias::~Deogracias() {}

void Deogracias::ChangeFrontAnimation() { Renderer_->ChangeFrameAnimation("Deosgracias_front"); }

void Deogracias::Start()
{
    SetObjectType(ObjectType::NPC);

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

    LineUIActor_ = GetLevel()->CreateActor<LineUIActor>();
    LineUIActor_->CreateLine("그대는 성하를 고통으로부터 해방시켰다. 그리고 교황 성하는 지금 꿈의 저편으로 건너가,\n"
                           "원초의 행진을 함께하고 있다.");
    LineUIActor_->AddSound("DLG_0120_0.wav");
    LineUIActor_->CreateLine("비통한 기적의 요람, 최후의 성유물, 축복에 싸여 뒤틀리면서 조용히 한탄하고 슬퍼하는\n"
                           "아버지의 이마에서 새어나오는 피와 황금을 다음 성배.");
    LineUIActor_->AddSound("DLG_0120_1.wav");
    LineUIActor_->CreateLine(
        "첫 성유물은 성하가 기적의 고통의 입맞춤을 받은 뒤집힌 옥좌의 옆, \n이 잿더미 산의 꼭대기에 있다.");
    LineUIActor_->AddSound("DLG_0120_2.wav");
    LineUIActor_->CreateLine("그리고 지금, 기적과의 마지막 교분이 그대를 기다리고 있다.");
    LineUIActor_->AddSound("DLG_0120_3.wav");
    LineUIActor_->CreateLine("기적이 그대의 죄 많은 심장에 얼마나 스며들었는가는, 그대만이 아는 것이다.");
    LineUIActor_->AddSound("DLG_0120_4.wav");
    LineUIActor_->CreateLine("첫 번째 기적과의 교분이 그대를 기다리고 있다.");
    LineUIActor_->AddSound("DLG_0122_0.wav");
    LineUIActor_->SetFontColor(float4{0.63f, 0.6f, 0.55f});
    LineUIActor_->SetSpeed(10.f);
    LineUIActor_->Off();

    LineUIActor_->SetMassageEndEvent(6, [&]() { Penitent::GetMainPlayer()->SetIsFreezeEnd(true); });
}

void Deogracias::Update(float _DeltaTime)
{
    if (true == IsSpeech_ && false == Interaction_)
    {
        LineUIActor_->On();
        LineUIActor_->SpeechStart();
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
