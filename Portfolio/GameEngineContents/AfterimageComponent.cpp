#include "PreCompile.h"
#include "AfterimageComponent.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"


AfterimageComponent::AfterimageComponent() {}

AfterimageComponent::~AfterimageComponent()
{
    AfterimageActors_.clear();
    MetaAfterimages_.clear();
    AfterimageActors_.clear();
}


void AfterimageComponent::Start() {}

void AfterimageComponent::Update(float _DeltaTime)
{
    if (true == IsDraw_)
    {
        DrawAfterimage(_DeltaTime);
    }

    else if (true == IsMetaDraw_)
    {
        DrawMetaAfterimage(_DeltaTime);
    }

    for (size_t i = 0; i < Afterimages_.size(); i++)
    {
        if (false == Afterimages_[i]->IsUpdate())
        {
            continue;
        }

        Afterimages_[i]->GetColorData().MulColor.a -= _DeltaTime;

        if (0.f >= Afterimages_[i]->GetColorData().MulColor.a)
        {
            Afterimages_[i]->Off();
        }
    }

    for (size_t i = 0; i < MetaAfterimages_.size(); i++)
    {
        if (false == MetaAfterimages_[i]->IsUpdate())
        {
            continue;
        }

        MetaAfterimages_[i]->GetColorData().MulColor.a -= _DeltaTime;

        if (0.f >= MetaAfterimages_[i]->GetColorData().MulColor.a)
        {
            MetaAfterimages_[i]->Off();
        }
    }
}

void AfterimageComponent::DrawAfterimage(float _DeltaTime)
{
    DrawTime_ += _DeltaTime;

    if (0.05f < DrawTime_)
    {
        DrawTime_ = 0.f;

        if (AfterimageSize_ <= Index_)
        {
            Index_  = 0;
            IsDraw_ = false;
            return;
        }

        AfterimageActors_[Index_]->On();
        Afterimages_[Index_]->On();

        Afterimages_[Index_]->GetColorData().MulColor = float4{0.15f, 0.5f, 0.98f, 0.65f};

        if (0.0f > GetActor()->GetTransform().GetLocalScale().x)
        {
            AfterimageActors_[Index_]->GetTransform().PixLocalNegativeX();
            AfterimageActors_[Index_]->GetTransform().SetWorldPosition({GetActor()->GetTransform().GetWorldPosition().x,
                                                                      GetActor()->GetTransform().GetWorldPosition().y,
                                                                      ObjectZ});

            AfterimageActors_[Index_]->GetTransform().SetWorldRotation({
                GetActor()->GetTransform().GetWorldRotation().x,
                GetActor()->GetTransform().GetWorldRotation().y,
                GetActor()->GetTransform().GetWorldRotation().z,
            });
        }

        else
        {
            AfterimageActors_[Index_]->GetTransform().PixLocalPositiveX();
            AfterimageActors_[Index_]->GetTransform().SetWorldPosition({GetActor()->GetTransform().GetWorldPosition().x,
                                                                      GetActor()->GetTransform().GetWorldPosition().y,
                                                                      ObjectZ});

            AfterimageActors_[Index_]->GetTransform().SetWorldRotation({
                GetActor()->GetTransform().GetWorldRotation().x,
                GetActor()->GetTransform().GetWorldRotation().y,
                GetActor()->GetTransform().GetWorldRotation().z,
            });
        }

        ++Index_;
    }
}

void AfterimageComponent::DrawMetaAfterimage(float _DeltaTime)
{
    DrawTime_ += _DeltaTime;

    if (0.15f < DrawTime_)
    {
        DrawTime_ = 0.f;

        if (AfterimageSize_ <= Index_)
        {
            Index_      = 0;
            IsMetaDraw_ = false;
            return;
        }

        AfterimageActors_[Index_]->On();
        MetaAfterimages_[Index_]->On();

        MetaAfterimages_[Index_]->GetColorData().MulColor = float4{0.65f, 0.f, 1.0f, 0.65f};

        if (0.0f > GetActor()->GetTransform().GetLocalScale().x)
        {
            AfterimageActors_[Index_]->GetTransform().PixLocalNegativeX();
            AfterimageActors_[Index_]->GetTransform().SetWorldPosition({GetActor()->GetTransform().GetWorldPosition().x,
                                                                      GetActor()->GetTransform().GetWorldPosition().y,
                                                                      PlayerBehindEffectZ});
        }

        else
        {
            AfterimageActors_[Index_]->GetTransform().PixLocalPositiveX();
            AfterimageActors_[Index_]->GetTransform().SetWorldPosition({GetActor()->GetTransform().GetWorldPosition().x,
                                                                      GetActor()->GetTransform().GetWorldPosition().y,
                                                                      PlayerBehindEffectZ});
        }

        ++Index_;
    }
}

void AfterimageComponent::End() {}


void AfterimageComponent::CreateAfterimage(const std::string& _Name, const FrameAnimation_DESC& _Info)
{
    Afterimages_.reserve(_Info.Frames.size() - 1);

    for (size_t i = 0; i < _Info.Frames.size() - 1; i++)
    {
        GameEngineActor* Actor = GetActor()->GetLevel()->CreateActor<GameEngineActor>();
        Actor->GetTransform().SetWorldScale({2, 2, 1});
        Actor->Off();
        AfterimageActors_.push_back(Actor);
    }

    for (size_t i = 0; i < _Info.Frames.size() - 1; i++)
    {
        GameEngineTextureRenderer* Afterimages = AfterimageActors_[i]->CreateComponent<GameEngineTextureRenderer>();
        Afterimages->CreateFrameAnimationCutTexture(_Name + "_Afterimage", _Info);
        Afterimages->ChangeFrameAnimation(_Name + "_Afterimage");
        Afterimages->Off();
        Afterimages_.push_back(Afterimages);
    }
}

void AfterimageComponent::CreateMetaAfterimage(const std::string& _Name, const FrameAnimation_DESC& _Info)
{
    MetaAfterimages_.reserve(_Info.Frames.size() - 1);

    for (size_t i = 0; i < _Info.Frames.size() - 1; i++)
    {
        GameEngineActor* Actor = GetActor()->GetLevel()->CreateActor<GameEngineActor>();
        Actor->GetTransform().SetWorldScale({2, 2, 1});
        Actor->Off();
        AfterimageActors_.push_back(Actor);
    }

    for (size_t i = 0; i < _Info.Frames.size() - 1; i++)
    {
        MetaTextureRenderer*  Afterimage = AfterimageActors_[i]->CreateComponent<MetaTextureRenderer>();
        std::vector<MetaData> Data     = MetaSpriteManager::GetInst()->Find(_Name);
        Afterimage->CreateMetaAnimation(_Name + "_Afterimage", _Info, Data);
        Afterimage->ChangeMetaAnimation(_Name + "_Afterimage");
        Afterimage->Off();
        MetaAfterimages_.push_back(Afterimage);
    }
}

void AfterimageComponent::CreateOnceAfterimage(const std::string& _Name, const FrameAnimation_DESC& _Info, size_t _Size)
{
    Afterimages_.reserve(_Size);

    for (size_t i = 0; i < _Size - 1; i++)
    {
        GameEngineActor* Actor = GetActor()->GetLevel()->CreateActor<GameEngineActor>();
        Actor->GetTransform().SetWorldScale({1, 1, 1});
        Actor->Off();
        AfterimageActors_.push_back(Actor);
    }

    for (size_t i = 0; i < _Size - 1; i++)
    {
        GameEngineTextureRenderer* Afterimages = AfterimageActors_[i]->CreateComponent<GameEngineTextureRenderer>();
        Afterimages->CreateFrameAnimationCutTexture(_Name + "_Afterimage", _Info);
        Afterimages->ChangeFrameAnimation(_Name + "_Afterimage");
        Afterimages->Off();
        Afterimages_.push_back(Afterimages);
    }
}

void AfterimageComponent::SetAfterimageFrame(size_t Start, size_t End)
{
    size_t Length = End - Start;
    AfterimageSize_ = Length - 1;

    for (size_t i = 0; i < Length - 1; i++)
    {
        Afterimages_[i]->CurAnimationSetStartPivotFrame(static_cast<int>(Start));
        Afterimages_[i]->CurAnimationPauseOn();
        ++Start;
    }
}

void AfterimageComponent::SetMetaAfterimageFrame(size_t Start, size_t End)
{
    size_t Length = End - Start;
    AfterimageSize_ = Length - 1;

    for (size_t i = 0; i < Length - 1; i++)
    {
        MetaAfterimages_[i]->CurAnimationSetStartPivotFrame(static_cast<int>(Start));
        MetaAfterimages_[i]->CurAnimationPauseOn();
        ++Start;
    }
}

void AfterimageComponent::SetOnceAfterimageFrame(size_t _Length)
{
    AfterimageSize_ = static_cast<int>(_Length - 1);

    for (size_t i = 0; i < _Length - 1; i++)
    {
        Afterimages_[i]->GetTransform().SetWorldScale({125, 400});
        Afterimages_[i]->CurAnimationSetStartPivotFrame(0);
        Afterimages_[i]->CurAnimationPauseOn();
        Afterimages_[i]->SetPivot(PIVOTMODE::TOP);
    }
}
