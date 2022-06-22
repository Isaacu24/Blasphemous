#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class Pilgrimage : public GameEngineLevel
{
public:
	// constrcuter destructer
	Pilgrimage();
	~Pilgrimage();

	// delete Function
	Pilgrimage(const Pilgrimage& _Other) = delete;
	Pilgrimage(Pilgrimage&& _Other) noexcept = delete;
	Pilgrimage& operator=(const Pilgrimage& _Other) = delete;
	Pilgrimage& operator=(Pilgrimage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	

};

