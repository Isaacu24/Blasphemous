#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class SpawnerOrder
{
    FristPattern,
    SecondPattern,
    ThirdPattern,
    FourthPattern,
    Death
};

//플랫폼 생성 위치를 알려주는 클래스
class Platform;
class GameEngineLevel;
class PlatformSpawner : public GameEngineActor
{
public:
    PlatformSpawner();
    ~PlatformSpawner();

    PlatformSpawner(const PlatformSpawner& _Other)                = delete;
    PlatformSpawner(PlatformSpawner&& _Other) noexcept            = delete;
    PlatformSpawner& operator=(const PlatformSpawner& _Other)     = delete;
    PlatformSpawner& operator=(PlatformSpawner&& _Other) noexcept = delete;

    void CreateFristPattern();
    void CreateSecondPattern();
    void CreateThirdPattern();
    void CreateFourthPattern();

    void DeathPlatform();

    inline void SetSpawnerOrder(SpawnerOrder _Order) 
    {
        CreateTime_   = 6.f;
        CurrentOrder_ = _Order; 
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    SpawnerOrder CurrentOrder_;

    std::vector<Platform*> Platforms_;

    float CreateTime_;

    bool IsCreate_;
};
