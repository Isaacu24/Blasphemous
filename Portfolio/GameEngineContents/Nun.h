#pragma once
#include "NormalMonster.h"

class Nun : public NormalMonster
{
public:
	Nun();
	~Nun();

	Nun(const Nun& _Other) = delete;
	Nun(Nun&& _Other) noexcept = delete;
	Nun& operator=(const Nun& _Other) = delete;
	Nun& operator=(Nun&& _Other) noexcept = delete;

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void IdleEnd(const StateInfo& _Info);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void PatrolMoveX(float _DeltaTime) override;
    void PatrolMoveY(float _DeltaTime) override;

private:

};

