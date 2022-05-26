#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Otus : public GameEngineActor
{
public:
	// constrcuter destructer
	Otus();
	~Otus();

	// delete Function
	Otus(const Otus& _Other) = delete;
	Otus(Otus&& _Other) noexcept = delete;
	Otus& operator=(const Otus& _Other) = delete;
	Otus& operator=(Otus&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	float TimeAngle;

};

