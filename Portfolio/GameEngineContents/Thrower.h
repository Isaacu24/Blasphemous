#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Thrower : public GameEngineActor
{
public:
	Thrower();
	~Thrower();

	// delete Function
	Thrower(const Thrower& _Other) = delete;
	Thrower(Thrower&& _Other) noexcept = delete;
	Thrower& operator=(const Thrower& _Other) = delete;
	Thrower& operator=(Thrower&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

