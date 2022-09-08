#include "PreCompile.h"
#include "SpectrumComponent.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"


SpectrumComponent::SpectrumComponent() {}

SpectrumComponent::~SpectrumComponent()
{
    SpectrumActors_.clear();
    MetaSpectrums_.clear();
    SpectrumActors_.clear();
}


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
        for (size_t i = 0; i < Spectrums_.size(); i++)
        {
            Spectrums_[i]->GetColorData().MulColor.a -= _DeltaTime * 0.5f;

            if (0.f >= Spectrums_[i]->GetColorData().MulColor.a)
            {
                if (i >= Spectrums_.size())
                {
                    IsDisAppear_ = false;
                }

                Spectrums_[i]->Off();
            }
        }
    }


    if (true == IsMetaDisAppear_)
    {
        for (size_t i = 0; i < MetaSpectrums_.size(); i++)
        {
            MetaSpectrums_[i]->GetColorData().MulColor.a -= _DeltaTime * 0.5f;

            if (0.f >= MetaSpectrums_[i]->GetColorData().MulColor.a)
            {
                if (i >= MetaSpectrums_.size())
                {
                    IsMetaDisAppear_ = false;
                }

                MetaSpectrums_[i]->Off();
            }
        }
    }
}

void SpectrumComponent::DrawSpectrum(float _DeltaTime)
{
    DrawTime_ += _DeltaTime;

    if (0.07f < DrawTime_)
    {
        DrawTime_ = 0.f;

        if (SpectrumSize_ <= Index_)
        {
            Index_       = 0.f;
            IsDraw_      = false;
            IsDisAppear_ = true;
            return;
        }

        SpectrumActors_[Index_]->On();
        Spectrums_[Index_]->On();

        Spectrums_[Index_]->GetColorData().MulColor = float4{0.15, 0.5f, 0.98f, 0.5f};

        if (0.0f > GetActor()->GetTransform().GetLocalScale().x)
        {
            SpectrumActors_[Index_]->GetTransform().PixLocalNegativeX();
            SpectrumActors_[Index_]->GetTransform().SetWorldPosition({GetActor()->GetTransform().GetWorldPosition().x,
                                                                      GetActor()->GetTransform().GetWorldPosition().y,
                                                                      static_cast<int>(ACTORORDER::Object)});

            SpectrumActors_[Index_]->GetTransform().SetWorldRotation({
                GetActor()->GetTransform().GetWorldRotation().x,
                GetActor()->GetTransform().GetWorldRotation().y,
                GetActor()->GetTransform().GetWorldRotation().z,
            });
        }

        else
        {
            SpectrumActors_[Index_]->GetTransform().PixLocalPositiveX();
            SpectrumActors_[Index_]->GetTransform().SetWorldPosition({GetActor()->GetTransform().GetWorldPosition().x,
                                                                      GetActor()->GetTransform().GetWorldPosition().y,
                                                                      static_cast<int>(ACTORORDER::Object)});

            SpectrumActors_[Index_]->GetTransform().SetWorldRotation({
                GetActor()->GetTransform().GetWorldRotation().x,
                GetActor()->GetTransform().GetWorldRotation().y,
                GetActor()->GetTransform().GetWorldRotation().z,
            });
        }

        ++Index_;
    }
}

void SpectrumComponent::DrawMetaSpectrum(float _DeltaTime)
{
    DrawTime_ += _DeltaTime;

    if (0.15f < DrawTime_)
    {
        DrawTime_ = 0.f;

        if (SpectrumSize_ <= Index_)
        {
            Index_           = 0.f;
            IsMetaDraw_      = false;
            IsMetaDisAppear_ = true;
            return;
        }

        SpectrumActors_[Index_]->On();
        MetaSpectrums_[Index_]->On();

        MetaSpectrums_[Index_]->GetColorData().MulColor = float4{0.65, 0.f, 1.0f, 0.5f};

        if (0.0f > GetActor()->GetTransform().GetLocalScale().x)
        {
            SpectrumActors_[Index_]->GetTransform().PixLocalNegativeX();
            SpectrumActors_[Index_]->GetTransform().SetWorldPosition({GetActor()->GetTransform().GetWorldPosition().x,
                                                                      GetActor()->GetTransform().GetWorldPosition().y,
                                                                      static_cast<int>(ACTORORDER::BehindEffect)});
        }

        else
        {
            SpectrumActors_[Index_]->GetTransform().PixLocalPositiveX();
            SpectrumActors_[Index_]->GetTransform().SetWorldPosition({GetActor()->GetTransform().GetWorldPosition().x,
                                                                      GetActor()->GetTransform().GetWorldPosition().y,
                                                                      static_cast<int>(ACTORORDER::BehindEffect)});
        }

        ++Index_;
    }
}

void SpectrumComponent::End() {}


void SpectrumComponent::CreateSpectrum(const std::string& _Name, const FrameAnimation_DESC& _Info)
{
    Spectrums_.reserve(_Info.Frames.size() - 1);

    for (size_t i = 0; i < _Info.Frames.size() - 1; i++)
    {
        GameEngineActor* Actor = GetActor()->GetLevel()->CreateActor<GameEngineActor>();
        Actor->GetTransform().SetWorldScale({2, 2, 1});
        Actor->SetLevelOverOn();
        Actor->Off();
        SpectrumActors_.push_back(Actor);
    }

    for (size_t i = 0; i < _Info.Frames.size() - 1; i++)
    {
        GameEngineTextureRenderer* Spectrums = SpectrumActors_[i]->CreateComponent<GameEngineTextureRenderer>();
        Spectrums->CreateFrameAnimationCutTexture(_Name + "_Spectrum", _Info);
        Spectrums->ChangeFrameAnimation(_Name + "_Spectrum");
        Spectrums->Off();
        Spectrums_.push_back(Spectrums);
    }
}

void SpectrumComponent::CreateMetaSpectrum(const std::string& _Name, const FrameAnimation_DESC& _Info)
{
    MetaSpectrums_.reserve(_Info.Frames.size() - 1);

    for (size_t i = 0; i < _Info.Frames.size() - 1; i++)
    {
        GameEngineActor* Actor = GetActor()->GetLevel()->CreateActor<GameEngineActor>();
        Actor->GetTransform().SetWorldScale({2, 2, 1});
        Actor->SetLevelOverOn();
        Actor->Off();
        SpectrumActors_.push_back(Actor);
    }

    for (size_t i = 0; i < _Info.Frames.size() - 1; i++)
    {
        MetaTextureRenderer*  Spectrum = SpectrumActors_[i]->CreateComponent<MetaTextureRenderer>();
        std::vector<MetaData> Data     = MetaSpriteManager::Inst_->Find(_Name);
        Spectrum->CreateMetaAnimation(_Name + "_Spectrum", _Info, Data);
        Spectrum->ChangeMetaAnimation(_Name + "_Spectrum");
        Spectrum->Off();
        MetaSpectrums_.push_back(Spectrum);
    }
}

void SpectrumComponent::CreateOnceSpectrum(const std::string& _Name, const FrameAnimation_DESC& _Info, size_t _Size)
{
    Spectrums_.reserve(_Size);

    for (size_t i = 0; i < _Size - 1; i++)
    {
        GameEngineActor* Actor = GetActor()->GetLevel()->CreateActor<GameEngineActor>();
        Actor->GetTransform().SetWorldScale({1, 1, 1});
        Actor->SetLevelOverOn();
        Actor->Off();
        SpectrumActors_.push_back(Actor);
    }

    for (size_t i = 0; i < _Size - 1; i++)
    {
        GameEngineTextureRenderer* Spectrums = SpectrumActors_[i]->CreateComponent<GameEngineTextureRenderer>();
        Spectrums->CreateFrameAnimationCutTexture(_Name + "_Spectrum", _Info);
        Spectrums->ChangeFrameAnimation(_Name + "_Spectrum");
        Spectrums->Off();
        Spectrums_.push_back(Spectrums);
    }
}

void SpectrumComponent::SetSpectrumFrame(size_t Start, size_t End)
{
    size_t Length = End - Start;
    SpectrumSize_ = Length - 1;

    for (size_t i = 0; i < Length - 1; i++)
    {
        Spectrums_[i]->CurAnimationSetStartPivotFrame(Start);
        Spectrums_[i]->CurAnimationPauseOn();
        ++Start;
    }
}

void SpectrumComponent::SetMetaSpectrumFrame(size_t Start, size_t End)
{
    size_t Length = End - Start;
    SpectrumSize_ = Length - 1;

    for (size_t i = 0; i < Length - 1; i++)
    {
        MetaSpectrums_[i]->CurAnimationSetStartPivotFrame(Start);
        MetaSpectrums_[i]->CurAnimationPauseOn();
        ++Start;
    }
}

void SpectrumComponent::SetOnceSpectrumFrame(size_t _Length)
{
    SpectrumSize_ = _Length - 1;

    for (size_t i = 0; i < _Length - 1; i++)
    {
        Spectrums_[i]->GetTransform().SetWorldScale({125, 400});
        Spectrums_[i]->CurAnimationSetStartPivotFrame(0);
        Spectrums_[i]->CurAnimationPauseOn();
        Spectrums_[i]->SetPivot(PIVOTMODE::TOP);
    }
}
