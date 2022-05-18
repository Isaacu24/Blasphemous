#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Torque : public GameEngineActor
{
public:
	// constrcuter destructer
	Torque();
	~Torque();

	// delete Function
	Torque(const Torque& _Other) = delete;
	Torque(Torque&& _Other) noexcept = delete;
	Torque& operator=(const Torque& _Other) = delete;
	Torque& operator=(Torque&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

