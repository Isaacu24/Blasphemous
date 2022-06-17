#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Penintent : public GameEngineActor
{
public:
	// constrcuter destructer
	Penintent();
	~Penintent();

	// delete Function
	Penintent(const Penintent& _Other) = delete;
	Penintent(Penintent&& _Other) noexcept = delete;
	Penintent& operator=(const Penintent& _Other) = delete;
	Penintent& operator=(Penintent&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

