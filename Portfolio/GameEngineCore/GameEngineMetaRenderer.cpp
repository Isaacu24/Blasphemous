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

	//ShaderResources.SetConstantBufferLink("AtlasData", FrameData);
}

void GameEngineMetaRenderer::Update(float _Delta)
{
}

