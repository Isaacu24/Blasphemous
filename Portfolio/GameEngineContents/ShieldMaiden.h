#pragma once
#include "NormalMonster.h"

class ShieldMaiden : public NormalMonster
{
public:
	ShieldMaiden();
	~ShieldMaiden();

	ShieldMaiden(const ShieldMaiden& _Other) = delete;
	ShieldMaiden(ShieldMaiden&& _Other) noexcept = delete;
	ShieldMaiden& operator=(const ShieldMaiden& _Other) = delete;
	ShieldMaiden& operator=(ShieldMaiden&& _Other) noexcept = delete;

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void IdleEnd(const StateInfo& _Info);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void PatrolMoveX(float _DeltaTime) override;

private:

};

