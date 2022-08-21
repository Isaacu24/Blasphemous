#pragma once
#include "NormalMonster.h"

 class LionHead : public NormalMonster
{
public:
	LionHead();
	~LionHead();

	LionHead(const LionHead& _Other) = delete;
	LionHead(LionHead&& _Other) noexcept = delete;
	LionHead& operator=(const LionHead& _Other) = delete;
	LionHead& operator=(LionHead&& _Other) noexcept = delete;

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

