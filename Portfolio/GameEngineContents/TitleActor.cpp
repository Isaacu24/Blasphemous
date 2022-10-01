#include "PreCompile.h"
#include "TitleActor.h"

TitleActor::TitleActor()
    : ButttonShadow_(nullptr)
    , IsReverse_(false)
    , IsDown_(false)
    , Alpha_(1.0f)
    , ChangeTime_(0.f)
{}

TitleActor::~TitleActor() {}

void TitleActor::Start()
{
    GameEngineUIRenderer* TitleRenderer = CreateComponent<GameEngineUIRenderer>();
    TitleRenderer->SetTexture("BlackBackground.png");
    TitleRenderer->ScaleToTexture();

    DescRenderer_ = CreateComponent<GameEngineUIRenderer>();
    DescRenderer_->SetTexture("StartCopyRight.png");
    DescRenderer_->GetTransform().SetWorldMove({0.f, -270.f, 0});
    DescRenderer_->GetTransform().SetWorldScale({900, 124});

    ButttonShadow_ = CreateComponent<GameEngineUIRenderer>();
    ButttonShadow_->SetTexture("PressAnyButttonShadow.png");
    ButttonShadow_->GetTransform().SetWorldScale({250, 35});
    ButttonShadow_->GetTransform().SetWorldMove({0.f, -150.f, 0.f});

    PressAnyKey_ = CreateComponent<GameEngineUIRenderer>();
    PressAnyKey_->SetTexture("PressAnyButton.png");
    PressAnyKey_->GetTransform().SetWorldScale({290, 25});
    PressAnyKey_->GetTransform().SetWorldMove({0.f, -150.f, 0.f});

    GameLogo_ = CreateComponent<GameEngineUIRenderer>();
    GameLogo_->GetTransform().SetWorldScale({800, 300});
    GameLogo_->GetTransform().SetWorldMove({0, 30.f, 0.f});
    GameLogo_->SetTexture("GameLogo.png");

    GameEngineInput::GetInst()->CreateKey("ChangeTitle", VK_RETURN);
}

void TitleActor::Update(float _DeltaTime)
{
    if (true == GameEngineInput::GetInst()->IsDownKey("ChangeTitle")
        || true == GameEngineInput::GetInst()->IsDownButton("GamePadA"))
    {
        IsDown_ = true;

        SoundPlayer_ = GameEngineSound::SoundPlayControl("Relic.wav");
    }

    if (true == IsChage_)
    {
        ChangeTime_ += _DeltaTime;
    }

    if (1.5f < ChangeTime_)
    {
        ChangeTime_ = 0.f;
        GEngine::ChangeLevel("MainMenu");
    }

    if (true == IsDown_)
    {
        Alpha_ -= 0.5f * _DeltaTime;

        GameLogo_->GetColorData().MulColor.a      = Alpha_;
        PressAnyKey_->GetColorData().MulColor.a   = Alpha_;
        ButttonShadow_->GetColorData().MulColor.a = Alpha_;

        if (0.f >= Alpha_)
        {
            IsDown_  = false;
            IsChage_ = true;
            DescRenderer_->GetTransform().SetWorldMove({0.f, 0.f, 10.f});
        }

        return;
    }

    if (false == IsReverse_ && false == IsChage_)
    {
        Alpha_ -= 0.5f * _DeltaTime;
        ButttonShadow_->GetColorData().MulColor = float4{1.0f, 1.0f, 1.0f, Alpha_};

        if (0.3f >= Alpha_)
        {
            IsReverse_ = true;
        }
    }

    else if (true == IsReverse_ && false == IsChage_)
    {
        Alpha_ += 0.5f * _DeltaTime;
        ButttonShadow_->GetColorData().MulColor = float4{1.0f, 1.0f, 1.0f, Alpha_};

        if (1.0f <= Alpha_)
        {
            IsReverse_ = false;
        }
    }
}

void TitleActor::End() {}
