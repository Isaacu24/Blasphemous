#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Titile : public GameEngineLevel
{
public:
	Titile();
	~Titile();

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

