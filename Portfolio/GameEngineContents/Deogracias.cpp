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
    LineUIActor_->CreateLine("�״�� ���ϸ� �������κ��� �ع���״�. �׸��� ��Ȳ ���ϴ� ���� ���� �������� �ǳʰ�,\n"
                           "������ ������ �Բ��ϰ� �ִ�.");
    LineUIActor_->AddSound("DLG_0120_0.wav");
    LineUIActor_->CreateLine("������ ������ ���, ������ ������, �ູ�� �ο� ��Ʋ���鼭 ������ ��ź�ϰ� �����ϴ�\n"
                           "�ƹ����� �̸����� ������� �ǿ� Ȳ���� ���� ����.");
    LineUIActor_->AddSound("DLG_0120_1.wav");
    LineUIActor_->CreateLine(
        "ù �������� ���ϰ� ������ ������ �Ը����� ���� ������ ������ ��, \n�� ����� ���� ����⿡ �ִ�.");
    LineUIActor_->AddSound("DLG_0120_2.wav");
    LineUIActor_->CreateLine("�׸��� ����, �������� ������ ������ �״븦 ��ٸ��� �ִ�.");
    LineUIActor_->AddSound("DLG_0120_3.wav");
    LineUIActor_->CreateLine("������ �״��� �� ���� ���忡 �󸶳� �������°���, �״븸�� �ƴ� ���̴�.");
    LineUIActor_->AddSound("DLG_0120_4.wav");
    LineUIActor_->CreateLine("ù ��° �������� ������ �״븦 ��ٸ��� �ִ�.");
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
