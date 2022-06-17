#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 그래픽카드에 연결

// 설명 :
class GameEngineDevice
{
private:
	static GameEngineDevice* Inst;

public:
	static GameEngineDevice& GetInst() 
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

public:
	// constrcuter destructer
	GameEngineDevice();
	~GameEngineDevice();

	// delete Function
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator=(GameEngineDevice&& _Other) noexcept = delete;

protected:

private:

};

