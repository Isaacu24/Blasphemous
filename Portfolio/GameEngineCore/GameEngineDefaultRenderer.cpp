#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineRenderingPipeLine.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer()
	:PipeLine(nullptr),
	IsInstancing(false)
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer()
{
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();
}

void GameEngineDefaultRenderer::SetPipeLine(const std::string& _Name)
{
	PipeLine = GameEngineRenderingpipeline::Find(_Name);

	if (nullptr == PipeLine)
	{
		MsgBoxAssert("존재하지 않는 파이프라인을 세팅하려고 했습니다.");
		return;
	}

	ShaderResources.ResourcesCheck(PipeLine);

	if (true == ShaderResources.IsConstantBuffer("TRANSFORMDATA"))
	{
		ShaderResources.SetConstantBufferLink("TRANSFORMDATA", &GetTransformData(), sizeof(GetTransformData()));
	}

	if (true == ShaderResources.IsConstantBuffer("RENDEROPTION"))
	{
		ShaderResources.SetConstantBufferLink("RENDEROPTION", &Option, sizeof(Option));
	}

}

void GameEngineDefaultRenderer::Render(float _DeltaTime)
{
	if (nullptr == PipeLine)
	{
		MsgBoxAssert("랜더링 파이프라인이 세팅되지 않으면 랜더링을 할수 없습니다.");
	}

	// 준비된 모든 리소스들을 다 세팅해준다.
	ShaderResources.AllResourcesSetting();
	PipeLine->Rendering();
	ShaderResources.AllResourcesReset();
}



GameEngineRenderingpipeline* GameEngineDefaultRenderer::GetPipeLine()
{
	if (false == PipeLine->IsOriginal())
	{
		return PipeLine;
	}

	PipeLine = GetClonePipeLine(PipeLine);
	return PipeLine;
}


void GameEngineDefaultRenderer::InstanceOn()
{
	IsInstancing = true;

	InstanceSetting();
}