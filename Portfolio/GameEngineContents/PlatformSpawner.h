#pragma once

enum class SpawnerOrder
{
	FristPattern,
	SecondPattern,
	ThirdPattern,
	FourthPattern,
	FifthPattern
};

//�÷��� ���� ��ġ�� �˷��ִ� Ŭ����
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

 