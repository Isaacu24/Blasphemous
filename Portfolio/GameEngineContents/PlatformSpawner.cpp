#include "PreCompile.h"
#include "PlatformSpawner.h"
#include "Platform.h"
#include "MetaTextureRenderer.h"

PlatformSpawner::PlatformSpawner()
    : CurrentOrder_(SpawnerOrder::FristPattern)
    , CreateTime_(0.f)
    , IsCreate_(false)
{}

PlatformSpawner::~PlatformSpawner() {}

void PlatformSpawner::CreateFristPattern()
{
    Platforms_.clear();

    for (int i = 0; i < 6; i++)
    {
        Platforms_.push_back(GetLevel()->CreateActor<Platform>());

        float4 Pos = GetTransform().GetWorldPosition();
        Platforms_[i]->GetTransform().SetWorldScale({2.f, 2.f, 1});
        Platforms_[i]->SetDeathTime(7.f);
    }

    Platforms_[0]->GetTransform().SetWorldPosition({650, -650, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[1]->GetTransform().SetWorldPosition({800, -800, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[2]->GetTransform().SetWorldPosition({1000, -650, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[3]->GetTransform().SetWorldPosition({1500, -650, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[4]->GetTransform().SetWorldPosition({1700, -800, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[5]->GetTransform().SetWorldPosition({1850, -650, static_cast<int>(ACTORORDER::Platform)});

    IsCreate_ = true;

    CurrentOrder_ = SpawnerOrder::SecondPattern;
}

void PlatformSpawner::CreateSecondPattern()
{
    Platforms_.clear();

    for (int i = 0; i < 6; i++)
    {
        Platforms_.push_back(GetLevel()->CreateActor<Platform>());

        float4 Pos = GetTransform().GetWorldPosition();
        Platforms_[i]->GetTransform().SetWorldScale({2.f, 2.f, 1});
        Platforms_[i]->SetDeathTime(7.f);
    }

    Platforms_[0]->GetTransform().SetWorldPosition({700, -800, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[1]->GetTransform().SetWorldPosition({800, -550, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[2]->GetTransform().SetWorldPosition({1100, -650, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[3]->GetTransform().SetWorldPosition({1400, -650, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[4]->GetTransform().SetWorldPosition({1700, -550, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[5]->GetTransform().SetWorldPosition({1800, -800, static_cast<int>(ACTORORDER::Platform)});

    CurrentOrder_ = SpawnerOrder::ThirdPattern;
}

void PlatformSpawner::CreateThirdPattern()
{
    Platforms_.clear();

    for (int i = 0; i < 6; i++)
    {
        Platforms_.push_back(GetLevel()->CreateActor<Platform>());

        float4 Pos = GetTransform().GetWorldPosition();
        Platforms_[i]->GetTransform().SetWorldScale({2.f, 2.f, 1});
        Platforms_[i]->SetDeathTime(7.f);
    }

    Platforms_[0]->GetTransform().SetWorldPosition({800, -650, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[1]->GetTransform().SetWorldPosition({900, -550, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[2]->GetTransform().SetWorldPosition({1100, -600, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[3]->GetTransform().SetWorldPosition({1400, -600, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[4]->GetTransform().SetWorldPosition({1600, -550, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[5]->GetTransform().SetWorldPosition({1700, -650, static_cast<int>(ACTORORDER::Platform)});

    CurrentOrder_ = SpawnerOrder::FourthPattern;
}

void PlatformSpawner::CreateFourthPattern()
{
    Platforms_.clear();

    for (int i = 0; i < 6; i++)
    {
        Platforms_.push_back(GetLevel()->CreateActor<Platform>());

        float4 Pos = GetTransform().GetWorldPosition();
        Platforms_[i]->GetTransform().SetWorldScale({2.f, 2.f, 1});
        Platforms_[i]->SetDeathTime(7.f);
    }

    Platforms_[0]->GetTransform().SetWorldPosition({900, -800, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[1]->GetTransform().SetWorldPosition({1100, -500, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[2]->GetTransform().SetWorldPosition({1150, -750, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[3]->GetTransform().SetWorldPosition({1450, -750, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[4]->GetTransform().SetWorldPosition({1500, -500, static_cast<int>(ACTORORDER::Platform)});
    Platforms_[5]->GetTransform().SetWorldPosition({1600, -800, static_cast<int>(ACTORORDER::Platform)});

    CurrentOrder_ = SpawnerOrder::FristPattern;
}

void PlatformSpawner::DeathPlatform() 
{
    for (int i = 0; i < Platforms_.size(); i++)
    {
        Platforms_[i]->GetRenderer()->ChangeMetaAnimation("bloodsand_platform_64x64_visible_to_novisible");
    }

    Platforms_.clear();
}


void PlatformSpawner::Start() {}

void PlatformSpawner::Update(float _DeltaTime)
{
    if (true == IsCreate_)
    {
        CreateTime_ += _DeltaTime;

        if (CreateTime_ < 6.f)
        {
            return;
        }

        switch (CurrentOrder_)
        {
            case SpawnerOrder::FristPattern:
                CreateFristPattern();
                break;
            case SpawnerOrder::SecondPattern:
                CreateSecondPattern();
                break;
            case SpawnerOrder::ThirdPattern:
                CreateThirdPattern();
                break;
            case SpawnerOrder::FourthPattern:
                CreateFourthPattern();
                break;
            case SpawnerOrder::Death:
                DeathPlatform();
                break;
        }

        CreateTime_ = 0.f;
    }
}

void PlatformSpawner::End() {}
