#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Flyer : public GameEngineActor
{
public:
	// constrcuter destructer
	Flyer();
	~Flyer();

	// delete Function
	Flyer(const Flyer& _Other) = delete;
	Flyer(Flyer&& _Other) noexcept = delete;
	Flyer& operator=(const Flyer& _Other) = delete;
	Flyer& operator=(Flyer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

