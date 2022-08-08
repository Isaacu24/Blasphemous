#pragma once
#include "GameEngineCore.h"

class GEngine
{
	static bool CollisionDebug;

public:
	static void ChangeLevel(std::string _Name);
	static void CollisionDebugOn();
	static void CollisionDebugOff();
	static void CollisionDebugSwitch();

	static bool IsCollisionDebug();

	static GameEngineLevel* GetCurrentLevel();


protected:

private:
	// constrcuter destructer
	GEngine();
	virtual ~GEngine() = 0;
	// delete Function
	GEngine(const GEngine& _Other) = delete;
	GEngine(GEngine&& _Other) noexcept = delete;
	GEngine& operator=(const GEngine& _Other) = delete;
	GEngine& operator=(GEngine&& _Other) noexcept = delete;

};

