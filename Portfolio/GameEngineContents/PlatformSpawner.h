#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class SpawnerOrder
{
	FristPattern,
	SecondPattern,
	ThirdPattern,
	FourthPattern,
};

//플랫폼 생성 위치를 알려주는 클래스
class GameEngineLevel;
class PlatformSpawner : public GameEngineActor
{
public:
	PlatformSpawner();
	~PlatformSpawner();

	PlatformSpawner(const PlatformSpawner& _Other) = delete;
	PlatformSpawner(PlatformSpawner&& _Other) noexcept = delete;
	PlatformSpawner& operator=(const PlatformSpawner& _Other) = delete;
	PlatformSpawner& operator=(PlatformSpawner&& _Other) noexcept = delete;

	void CreateFristPattern();
	void CreateSecondPattern();
	void CreateThirdPattern();
	void CreateFourthPattern();

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
	SpawnerOrder CurrentOrder_;

	float CreateTime_;
	
	bool IsCreate_;
};

 