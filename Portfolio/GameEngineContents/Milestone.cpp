#include "PreCompile.h"
#include "Milestone.h"

Milestone::Milestone()
    : ShowTime_(0.f)
    , Alpha_(0.f)
    , IsInvisible_(false)
{}

Milestone::~Milestone() {}

void Milestone::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});
    GetTransform().SetWorldMove({0, 150});

    UIRenderer_ = CreateComponent<GameEngineUIRenderer>();
    UIRenderer_->GetTransform().SetLocalPosition({0, 0, static_cast<int>(UIORDER::PlayerUI)});
    UIRenderer_->SetTexture("message_area.png");
    UIRenderer_->ScaleToTexture();
    UIRenderer_->GetColorData().MulColor.a = 0.f;

    Font_ = CreateComponent<GameEngineFontRenderer>();
    Font_->SetScreenPostion({640, 190, static_cast<int>(UIORDER::PlayerUI)});
    Font_->SetSize(40);
    Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
    Font_->SetColor(float4{0.65f, 0.65f, 0.45f, 0.f});

    Font_->ChangeCamera(CAMERAORDER::UICAMERA);

    SoundPlayer_ = GameEngineSound::SoundPlayControl("ZONE_INFO.wav");
}

void Milestone::Update(float _DeltaTime)
{
    if (false == IsInvisible_)
    {
        UIRenderer_->GetColorData().MulColor.a += _DeltaTime * 2;
        Alpha_ += _DeltaTime * 4;

        if (1.f <= Alpha_)
        {
            Alpha_ = 1.f;
        }

        else
        {
            Font_->SetColor(float4{0.65f, 0.65f, 0.45f, Alpha_});
        }

        if (1.f <= UIRenderer_->GetColorData().MulColor.a)
        {
            UIRenderer_->GetColorData().MulColor.a = 1.f;
            Font_->SetColor(float4{0.65f, 0.65f, 0.45f, 1.f});

            ShowTime_ += _DeltaTime;

            if (1.f <= ShowTime_)
            {
                ShowTime_    = 0.f;
                IsInvisible_ = true;
            }
        }
    }

    if (true == IsInvisible_)
    {
        UIRenderer_->GetColorData().MulColor.a -= _DeltaTime;

        Alpha_ -= _DeltaTime * 2;

        if (0.f >= Alpha_)
        {
            Alpha_ = 0.f;
            Font_->Off();
        }

        else
        {
            Font_->SetColor(float4{0.65f, 0.65f, 0.45f, Alpha_});
        }

        if (0.f >= UIRenderer_->GetColorData().MulColor.a)
        {
            UIRenderer_->Off();
            Off();
        }
    }
}

void Milestone::End() {}

void Milestone::LevelStartEvent() {}

void Milestone::LevelEndEvent() { Death(); }

