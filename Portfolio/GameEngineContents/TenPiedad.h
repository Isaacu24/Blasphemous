#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonsterBase.h"

class TenPiedad : public GameEngineActor, public BossMonsterBase
{
public:
	TenPiedad();
	~TenPiedad();

	TenPiedad(const TenPiedad& _Other) = delete;
	TenPiedad(TenPiedad&& _Other) noexcept = delete;
	TenPiedad& operator=(const TenPiedad& _Other) = delete;
	TenPiedad& operator=(TenPiedad&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);
	void End();

private:
	 
};

