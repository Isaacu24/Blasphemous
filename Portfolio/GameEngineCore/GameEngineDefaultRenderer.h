#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineShaderResourcesHelper.h"

class GameEngineRenderingPipeLine;
class GameEngineDefaultRenderer : public GameEngineRenderer
{
	// 하나의 랜더링 파이프라인은
	// 하나의 매쉬
	// 하나의 메테리얼
	// 하나의 랜더타겟

public:
	GameEngineRenderingPipeLine* GetPipeLine()
	{
		return PipeLine;
	}

	GameEngineDefaultRenderer();
	~GameEngineDefaultRenderer();

	GameEngineDefaultRenderer(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer(GameEngineDefaultRenderer&& _Other) noexcept = delete;
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer& operator=(GameEngineDefaultRenderer&& _Other) noexcept = delete;

	virtual void Render(float _DeltaTime);

	void SetPipeLine(const std::string& _Name);

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

private:
	// 공통적인 메모리 공유하는 파이프라인
	GameEngineRenderingPipeLine* PipeLine;

	// 렌더링 파이프라인 셰이더 속성 변경을 도와주는 클래스
	GameEngineShaderResourcesHelper PipeLineHelper;
};

