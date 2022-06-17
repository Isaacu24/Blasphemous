#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class Titile : public GameEngineLevel
{
public:
	// constrcuter destructer
	Titile();
	~Titile();

	// delete Function
	Titile(const Titile& _Other) = delete;
	Titile(Titile&& _Other) noexcept = delete;
	Titile& operator=(const Titile& _Other) = delete;
	Titile& operator=(Titile&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

