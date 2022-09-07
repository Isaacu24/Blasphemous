#include "PreCompile.h"
#include "SpectrumComponent.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"


SpectrumComponent::SpectrumComponent() {}

SpectrumComponent::~SpectrumComponent() {}


void SpectrumComponent::Start() {}

void SpectrumComponent::Update(float _DeltaTime)
{
    if (true == IsDraw_)
    {
        DrawSpectrum(_DeltaTime);
    }

    else if (true == IsMetaDraw_)
    {
        DrawMetaSpectrum(_DeltaTime);
    }

     if (true == IsDisAppear_)
    {
         DisAppearTime_ += _DeltaTime;

        if (0.05f < DisAppearTime_)
        {
            DisAppearTime_ = 0.f;

            if (MetaSpectrums_.size() <= Index_)
            {
                Index_  = 0.f;
                IsDisAppear_ = false;
                return;
            }

            MetaSpectrums_[Index_]->Off();

            ++Index_;
        }
    }
}

void SpectrumComponent::DrawSpectrum(float _DeltaTime)
{
    DrawTime_ += _DeltaTime;

    if (0.5f < DrawTime_)
    {
        DrawTime_ = 0.f;

        if (Spectrums_.size() <= Index_)
        {
            Index_  = 0.f;
            IsDraw_ = false;
            return;
        }

        Spectrums_[Index_]->On();
        Spectrums_[Index_]->ScaleToTexture();
        Spectrums_[Index_]->GetTransform().SetWorldPosition(GetActor()->GetTransform().GetWorldPosition());

        ++Index_;
    }
}

void SpectrumComponent::DrawMetaSpectrum(float _DeltaTime)
{
    DrawTime_ += _DeltaTime;

    if (0.15f < DrawTime_)
    {
        DrawTime_ = 0.f;

        if (MetaSpectrums_.size() <= Index_)
        {
            Index_      = 0.f;
            IsMetaDraw_ = false;
            IsDisAppear_ = true;
            return;
        }

        GameEngineActor* Actor = GetActor()->GetLevel()->CreateActor<GameEngineActor>();
        Actor->GetTransform().SetWorldScale({2, 2, 1});

        MetaSpectrums_[Index_]->SetParent(Actor);
        MetaSpectrums_[Index_]->GetColorData().MulColor = float4{0.65, 0.f, 1.0f, 0.5f};
        MetaSpectrums_[Index_]->On();

        Actor->GetTransform().SetWorldPosition({GetActor()->GetTransform().GetWorldPosition().x,
                                                GetActor()->GetTransform().GetWorldPosition().y,
                                                static_cast<int>(ACTORORDER::BehindEffect)});

        ++Index_;
    }
}

void SpectrumComponent::End() {}


void SpectrumComponent::CreateSpectrum(const std::string& _Name, const FrameAnimation_DESC& _Info, size_t _SpectrumSize)
{
    Spectrums_.reserve(_SpectrumSize);

    for (size_t i = 0; i < _SpectrumSize; i++)
    {
        GameEngineTextureRenderer* Spectrums = GetActor()->CreateComponent<GameEngineTextureRenderer>();
        Spectrums->CreateFrameAnimationCutTexture(_Name + "_Spectrum", _Info);
        Spectrums->ChangeFrameAnimation(_Name + "_Spectrum");
        Spectrums->Off();
        Spectrums_.push_back(Spectrums);
    }
}

void SpectrumComponent::CreateMetaSpectrum(const std::string&         _Name,
                                           const FrameAnimation_DESC& _Info,
                                           size_t                     _SpectrumSize)
{
    MetaSpectrums_.reserve(_SpectrumSize);

    for (size_t i = 0; i < _SpectrumSize; i++)
    {
        MetaTextureRenderer*  Spectrum = GetActor()->CreateComponent<MetaTextureRenderer>();
        std::vector<MetaData> Data     = MetaSpriteManager::Inst_->Find(_Name);
        Spectrum->CreateMetaAnimation(_Name + "_Spectrum", _Info, Data);
        Spectrum->ChangeMetaAnimation(_Name + "_Spectrum");
        Spectrum->Off();
        MetaSpectrums_.push_back(Spectrum);
    }
}

void SpectrumComponent::SetSpectrum(size_t Start, size_t End)
{
    size_t Length = Start - End;

    Length = abs(static_cast<long long>(Length));

    for (size_t i = 0; i < Length; i++)
    {
        ++Start;
        Spectrums_[i]->SetFrame(Start);
        Spectrums_[i]->CurAnimationPauseOn();
    }
}

void SpectrumComponent::SetMetaSpectrum(size_t Start, size_t End)
{
    size_t Length = Start - End;
    Length        = abs(static_cast<long long>(Length));

    for (size_t i = 0; i < Length; i++)
    {
        ++Start;
        MetaSpectrums_[i]->SetFrame(Start);
        MetaSpectrums_[i]->CurAnimationPauseOn();
    }
}
