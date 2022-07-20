#pragma once

enum class SpawnerOrder
{
	FristPattern,
	SecondPattern,
	ThirdPattern,
	FourthPattern,
	FifthPattern
};

//플랫폼 생성 위치를 알려주는 클래스
class GameEngineLevel;
class PlatformSpawner
{
public:
	PlatformSpawner();
	~PlatformSpawner();

	PlatformSpawner(const PlatformSpawner& _Other) = delete;
	PlatformSpawner(PlatformSpawner&& _Other) noexcept = delete;
	PlatformSpawner& operator=(const PlatformSpawner& _Other) = delete;
	PlatformSpawner& operator=(PlatformSpawner&& _Other) noexcept = delete;

	void CreateFristPattern(GameEngineLevel* _Level);
	void CreateSecondPattern(GameEngineLevel* _Level);
	void CreateThirdPattern(GameEngineLevel* _Level);
	void CreateFourthPattern(GameEngineLevel* _Level);
	void CreateFifthPattern(GameEngineLevel* _Level);

protected:

private:
	SpawnerOrder CurrentOrder_;


};

 