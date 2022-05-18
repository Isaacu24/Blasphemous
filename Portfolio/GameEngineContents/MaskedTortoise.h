#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MaskedTortoise : public GameEngineActor
{
public:
	// constrcuter destructer
	MaskedTortoise();
	~MaskedTortoise();

	// delete Function
	MaskedTortoise(const MaskedTortoise& _Other) = delete;
	MaskedTortoise(MaskedTortoise&& _Other) noexcept = delete;
	MaskedTortoise& operator=(const MaskedTortoise& _Other) = delete;
	MaskedTortoise& operator=(MaskedTortoise&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

