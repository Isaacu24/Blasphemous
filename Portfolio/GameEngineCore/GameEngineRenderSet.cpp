#include "PreCompile.h"
#include "GameEngineRenderSet.h"

GameEngineRenderSet::GameEngineRenderSet()
{
}

GameEngineRenderSet::~GameEngineRenderSet()
{
}


void GameEngineRenderSet::SetPipeLine(const std::string& _Name)
{
	PipeLine = GameEngineRenderingpipeline::Find(_Name);

	if (nullptr == PipeLine)
	{
		MsgBoxAssert("�������� �ʴ� ������������ �����Ϸ��� �߽��ϴ�.");
		return;
	}

	ShaderResources.ResourcesCheck(PipeLine);

	//if (true == ShaderResources.IsConstantBuffer("TRANSFORMDATA"))
	//{
	//	ShaderResources.SetConstantBufferLink("TRANSFORMDATA", &GetTransformData(), sizeof(GetTransformData()));
	//}

	//if (true == ShaderResources.IsConstantBuffer("RENDEROPTION"))
	//{
	//	ShaderResources.SetConstantBufferLink("RENDEROPTION", &Option, sizeof(Option));
	//}

}

void GameEngineRenderSet::Render()
{
	if (nullptr == PipeLine)
	{
		MsgBoxAssert("������ ������������ ���õ��� ������ �������� �Ҽ� �����ϴ�.");
	}

	// �غ�� ��� ���ҽ����� �� �������ش�.
	ShaderResources.AllResourcesSetting();
	PipeLine->Rendering();
	ShaderResources.AllResourcesReset();
}

GameEngineRenderingpipeline* GameEngineRenderSet::GetPipeLine()
{
	if (false == PipeLine->IsOriginal())
	{
		return PipeLine;
	}

	GameEngineRenderingpipeline* Clone = GameEngineRenderingpipeline::Create();
	Clone->Copy(PipeLine);
	PipeLine = Clone;
	return PipeLine;
}