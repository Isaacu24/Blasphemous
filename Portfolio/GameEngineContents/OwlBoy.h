#pragma once
#include <GameEngineCore/GameEngineCore.h>

class OwlBoy : public GameEngineCore
{
public:
	OwlBoy();
	~OwlBoy();

	OwlBoy(const OwlBoy& _Other) = delete;
	OwlBoy(OwlBoy&& _Other) noexcept = delete;
	OwlBoy& operator=(const OwlBoy& _Other) = delete;
	OwlBoy& operator=(OwlBoy&& _Other) noexcept = delete;

	std::string GetWindowTitle() override
	{
		return "OwlBoy";
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void ResourceInit();

private:

};

