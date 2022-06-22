#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

class TenPiedad : public GameEngineActor, public BossMonster
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

