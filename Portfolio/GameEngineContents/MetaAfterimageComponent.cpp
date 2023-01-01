#include "PreCompile.h"
#include "MetaAfterimageComponent.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

MetaAfterimageComponent::MetaAfterimageComponent() {}

MetaAfterimageComponent::~MetaAfterimageComponent() 
{
    MetaAfterimages_.clear();
    AfterimageActors_.clear();
}


void MetaAfterimageComponent::Start() {}

void MetaAfterimageComponent::Update(float _DeltaTime)
{
    if (true == IsDraw_)
    {
        DrawAfterimage(_DeltaTime);
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

void MetaAfterimageComponent::End() {}


void MetaAfterimageComponent::CreateAfterimage(const std::string& _Name, const FrameAnimation_DESC& _Info)
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
        std::vector<MetaData> Data       = MetaSpriteManager::GetInst()->Find(_Name);
        Afterimage->CreateMetaAnimation(_Name + "_Afterimage", _Info, Data);
        Afterimage->ChangeMetaAnimation(_Name + "_Afterimage");
        Afterimage->Off();
        MetaAfterimages_.push_back(Afterimage);
    }
}

void MetaAfterimageComponent::DrawAfterimage(float _DeltaTime)
{
    DrawTime_ += _DeltaTime;

    if (0.15f < DrawTime_)
    {
        DrawTime_ = 0.f;

        if (AfterimageSize_ <= Index_)
        {
            Index_  = 0;
            IsDraw_ = false;
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

void MetaAfterimageComponent::SetAfterimageFrame(size_t Start, size_t End)
{
    size_t Length   = End - Start;
    AfterimageSize_ = Length - 1;

    for (size_t i = 0; i < Length - 1; i++)
    {
        MetaAfterimages_[i]->CurAnimationSetStartPivotFrame(static_cast<int>(Start));
        MetaAfterimages_[i]->CurAnimationPauseOn();
        ++Start;
    }
}
