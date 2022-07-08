#pragma once
#include "GameEngineCore.h"

//GameEngineCore의 기능을 컨텐츠에 보여주기 위한 클래스
class GEngine
{
public:
	static void ChangeLevel(std::string _Name);

protected:

private:
	GEngine();
	virtual ~GEngine() = 0;

	GEngine(const GEngine& _Other) = delete;
	GEngine(GEngine&& _Other) noexcept = delete;
	GEngine& operator=(const GEngine& _Other) = delete;
	GEngine& operator=(GEngine&& _Other) noexcept = delete;

};

