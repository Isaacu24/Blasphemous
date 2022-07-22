#include "PreCompile.h"
#include "GameEngineMetaRenderer.h"

GameEngineMetaRenderer::GameEngineMetaRenderer() 
{
}

GameEngineMetaRenderer::~GameEngineMetaRenderer() 
{
}

void GameEngineMetaRenderer::Start()
{
	GameEngineDefaultRenderer::Start();
	SetPipeLine("TextureMeta");

	FrameData.PosX = 0.0f;
	FrameData.PosY = 0.0f;
	FrameData.SizeX = 1.0f;
	FrameData.SizeY = 1.0f;

	ShaderResources.SetConstantBufferLink("AtlasData", FrameData);
}

void GameEngineMetaRenderer::Update(float _Delta)
{
}

