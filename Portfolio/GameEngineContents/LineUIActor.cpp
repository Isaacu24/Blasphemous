#include "PreCompile.h"
#include "LineUIActor.h"

LineUIActor::LineUIActor()
    : Alpha_(0.f)
    , StartEventIndex_(-1)
    , EndEventIndex_(-1)
    , Speed_(20.f)
    , BackgroundAlpha_(0.75f)
{}

LineUIActor::~LineUIActor() { Script_.clear(); }


void LineUIActor::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});
    GetTransform().SetWorldMove({0, -320});

    Renderer_ = CreateComponent<GameEngineUIRenderer>();
    Renderer_->SetTexture("popup_message_background.png");
    Renderer_->GetTransform().SetLocalPosition({0, 0, static_cast<int>(UIORDER::PlayerUI)});
    // Renderer_->GetColorData().MulColor.a = 0.75f;
    Renderer_->GetColorData().MulColor.a = 0.f;
    Renderer_->ScaleToTexture();

    Font_ = CreateComponent<GameEngineFontRenderer>();
    // Font_->SetColor({0.65f, 0.65f, 0.45f, 1.0f});
    Font_->SetColor({0.65f, 0.65f, 0.45f, 0.0f});
    Font_->SetScreenPostion({640, 650, static_cast<int>(UIORDER::PlayerUI)});
    Font_->SetSize(25);
    Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
    Font_->ChangeCamera(CAMERAORDER::UICAMERA);

    IsOn_ = true;
}

void LineUIActor::Update(float _DeltaTime)
{
    if (true == IsOn_)
    {
        Renderer_->GetColorData().MulColor.a += _DeltaTime;

        Alpha_ += _DeltaTime * 1.5f;

        if (1.f <= Alpha_)
        {
            Alpha_ = 1.f;
        }

        Font_->SetText(Script_[0].Text, "NeoµÕ±Ù¸ð");
        Font_->SetColor({0.65f, 0.65f, 0.45f, Alpha_});

        if (false == IsSoundPlay_)
        {
            IsSoundPlay_ = true;

            if (0 != Script_.size())
            {
                SoundPlayer_ = GameEngineSound::SoundPlayControl(Script_[0].Sound);
                SoundPlayer_.Volume(0.5f);
            }
        }

        if (BackgroundAlpha_ <= Renderer_->GetColorData().MulColor.a)
        {
            IsOn_  = false;
            Alpha_ = 1;
            ++LineIndex_;

            Font_->SetColor({0.65f, 0.65f, 0.45f, 1.f});
            Renderer_->GetColorData().MulColor.a = BackgroundAlpha_;
        }
    }

    if (true == IsSpeech_ && false == IsOn_)
    {
        BreathTime_ += _DeltaTime;

        ConstTime_ = static_cast<float>(Script_[0].Sound.size());
        ConstTime_ /= Speed_;

        if (true == GameEngineInput::GetInst()->IsDownKey("ScriptSkip")
            || true == GameEngineInput::GetInst()->IsDownButton("PenitentA"))
        {
            ConstTime_ = 0.f;
            SoundPlayer_.Stop();
        }

        if (ConstTime_ <= BreathTime_)
        {
            BreathTime_ = 0.f;

            if (LineIndex_ == Script_.size())
            {
                if (EndEventIndex_ == LineIndex_ && nullptr != EndEvent_)
                {
                    EndEvent_();
                }

                IsSpeech_    = false;
                IsSpeechEnd_ = true;
                return;
            }

            if (StartEventIndex_ == LineIndex_ && nullptr != StartEvent_)
            {
                StartEvent_();
            }

            Font_->SetText(Script_[LineIndex_].Text, "NeoµÕ±Ù¸ð");

            SoundPlayer_ = GameEngineSound::SoundPlayControl(Script_[LineIndex_].Sound);
            SoundPlayer_.Volume(0.5f);

            ++LineIndex_;
        }
    }

    if (true == IsSpeechEnd_)
    {
        Renderer_->GetColorData().MulColor.a -= _DeltaTime;

        Alpha_ -= _DeltaTime * 2;
        Font_->SetColor({Font_->GetColor().x, Font_->GetColor().y, Font_->GetColor().z, Alpha_});

        if (0.f >= Alpha_)
        {
            Alpha_ = 0.f;
            Font_->SetColor({Font_->GetColor().x, Font_->GetColor().y, Font_->GetColor().z, Alpha_});
        }

        if (0.f >= Renderer_->GetColorData().MulColor.a)
        {
            Off();
            Font_->Off();

            Alpha_       = 0.f;
            IsSpeechEnd_ = false;
        }
    }
}

void LineUIActor::End() {}


void LineUIActor::LevelEndEvent() { Death(); }


void LineUIActor::OnEvent() 
{
    Renderer_->On(); 
    Font_->On();
}

void LineUIActor::OffEvent() 
{
    Renderer_->Off();
    Font_->Off();
}


void LineUIActor::AddLine(const std::string& _Line, const std::string& _Sound)
{
    Script_.emplace_back(Line(_Line, _Sound));
}
