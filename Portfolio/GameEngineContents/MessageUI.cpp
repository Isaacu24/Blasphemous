#include "PreCompile.h"
#include "MessageUI.h"

MessageUI::MessageUI() 
    : Alpha_(1.f)
{}

MessageUI::~MessageUI() { Script_.clear(); }


void MessageUI::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});
    GetTransform().SetWorldMove({0, -320});

    Renderer_ = CreateComponent<GameEngineUIRenderer>();
    Renderer_->SetTexture("popup_message_background.png");
    Renderer_->GetTransform().SetLocalPosition({0, 0, static_cast<int>(UIORDER::PlayerUI)});
    Renderer_->GetColorData().MulColor.a = 0.75f;
    Renderer_->ScaleToTexture();

    Font_ = CreateComponent<GameEngineFontRenderer>();
    Font_->SetColor({0.65f, 0.65f, 0.45f, 1.0f});
    Font_->SetScreenPostion({640, 650, static_cast<int>(UIORDER::PlayerUI)});
    Font_->SetSize(25);
    Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);

    Font_->ChangeCamera(CAMERAORDER::UICAMERA);
}

void MessageUI::Update(float _DeltaTime)
{
    if (true == IsSpeech_)
    {
        if (0 == Script_.size())
        {
            Off();
            Font_->Off();
            IsSpeech_ = false;
            return;
        }

        BreathTime_ += _DeltaTime;

        if (0 == LineIndex_)
        {
            ConstTime_ = 0.f;
        }

        else
        {
            ConstTime_ = static_cast<float>(Script_[LineIndex_ - 1].size());
            ConstTime_ /= 10.f;
        }

        if (ConstTime_ <= BreathTime_)
        {
            BreathTime_ = 0.f;

            if (LineIndex_ == Script_.size())
            {
                IsSpeech_    = false;
                IsSpeechEnd_ = true;
                return;
            }

            Font_->SetText(Script_[LineIndex_], "NeoµÕ±Ù¸ð");

            ++LineIndex_;
        }
    }

    if (true == IsSpeechEnd_)
    {
        Renderer_->GetColorData().MulColor.a -= _DeltaTime;

        Alpha_ -= _DeltaTime * 2;

        if (0.f < Alpha_)
        {
            Font_->SetColor(Alpha_);
        }

        if (0.f > Renderer_->GetColorData().MulColor.a)
        {
            Off();
            Font_->Off();

            IsSpeechEnd_ = false;
        }
    }
}

void MessageUI::End() {}


void MessageUI::CreateLine(const std::string& _Line) { Script_.push_back(_Line); }
