#pragma once
#include <GameEngineCore/GameEngineCore.h>

class Blasphemous : public GameEngineCore
{
public:
	Blasphemous();
	~Blasphemous();

	Blasphemous(const Blasphemous& _Other) = delete;
	Blasphemous(Blasphemous&& _Other) noexcept = delete;
	Blasphemous& operator=(const Blasphemous& _Other) = delete;
	Blasphemous& operator=(Blasphemous&& _Other) noexcept = delete;

	std::string GetWindowTitle() override
	{
		return "Blasphemous";
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	float4 StartWindowSize() override
	{
		return { 1280.0f, 720.0f };
	};

	float4 StartWindowPosition() override
	{
		return { 300.0f, 200.0f };
	}

private:
	void LoadResources();
	void LoadMap(const std::string& _Level, int _Room, int _Index);
	void LoadBossMonster();
	void LoadNormalMonster();

	void LoadEffect();

	void CutTexture();

};

