#pragma once
#include "GameEngineDefaultRenderer.h"

class GameEngineMetaRenderer : public GameEngineDefaultRenderer
{
public:
	GameEngineMetaRenderer();
	~GameEngineMetaRenderer();

	GameEngineMetaRenderer(const GameEngineMetaRenderer& _Other) = delete;
	GameEngineMetaRenderer(GameEngineMetaRenderer&& _Other) noexcept = delete;
	GameEngineMetaRenderer& operator=(const GameEngineMetaRenderer& _Other) = delete;
	GameEngineMetaRenderer& operator=(GameEngineMetaRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineTexture* CurTex;
	float4 FrameData;

};

