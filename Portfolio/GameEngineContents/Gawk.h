#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Gawk : public GameEngineActor
{
public:
	// constrcuter destructer
	Gawk();
	~Gawk();

	// delete Function
	Gawk(const Gawk& _Other) = delete;
	Gawk(Gawk&& _Other) noexcept = delete;
	Gawk& operator=(const Gawk& _Other) = delete;
	Gawk& operator=(Gawk&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

