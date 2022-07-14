#pragma once
#include <random>

class GameEngineRandom
{
public:
	static GameEngineRandom MainRandom;

private:
	// 메르헨 트위스터의 알고리즘으로 비트를 뒤섞는 녀석.
	std::mt19937_64 mt_;

public:
	int RandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> Uniform(_Min, _Max);
		return Uniform(mt_);
	}

	float RandomFloat(float _Min, float _Max)
	{
		std::uniform_real_distribution<float> Uniform(_Min, _Max);
		return Uniform(mt_);
	}

public:
	// constrcuter destructer
	GameEngineRandom(long long _Seed = -1);
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

protected:

private:

};

