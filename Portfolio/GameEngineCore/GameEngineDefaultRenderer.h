#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineShaderResourcesHelper.h"

class GameEngineRenderingpipeline;
class GameEngineDefaultRenderer : public GameEngineRenderer
{
public:
	GameEngineShaderResourcesHelper ShaderResources;

	GameEngineDefaultRenderer();
	~GameEngineDefaultRenderer();

	// delete Function
	GameEngineDefaultRenderer(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer(GameEngineDefaultRenderer&& _Other) noexcept = delete;
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer& operator=(GameEngineDefaultRenderer&& _Other) noexcept = delete;

	virtual void Render(float _DeltaTime);

	void SetPipeLine(const std::string& _Name);

	GameEngineRenderingpipeline* GetPipeLine();

	void InstanceOn();

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

	virtual void InstanceSetting() {}

private:
	// �������� �޸� �����ϴ� �޷θ����� ��� �ְ�
	GameEngineRenderingpipeline* PipeLine;

	bool IsInstancing;
};

