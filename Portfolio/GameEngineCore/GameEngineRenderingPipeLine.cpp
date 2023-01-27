#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"

#include "GameEngineInputLayOut.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineBlend.h"


GameEngineRenderingpipeline::GameEngineRenderingpipeline()
	: InputLayOut(nullptr)
	, VertexBuffer(nullptr)
	, VertexShader(nullptr)
	, IndexBuffer(nullptr)
	, Rasterizer(nullptr)
	, PixelShader(nullptr)
	, DepthStencil(nullptr)
	, Blend(nullptr)
	, Topology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	VertexBuffer = GameEngineVertexBuffer::Find("rect");
	IndexBuffer = GameEngineIndexBuffer::Find("rect");
	Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
	Blend = GameEngineBlend::Find("AlphaBlend");
	DepthStencil = GameEngineDepthStencil::Find("EngineBaseDepth");
}

GameEngineRenderingpipeline::~GameEngineRenderingpipeline()
{
}

//
//void GameEngineRenderingPipeLine::SetInputAssembler1InputLayOutSetting(const std::string& _Name)
//{
//	InputLayOut = GameEngineInputLayOut::Find(_Name);
//
//	if (nullptr == InputLayOut)
//	{
//		MsgBoxAssert("�������� �ʴ� ��ǲ���̾ƿ��� �����Ϸ��� �߽��ϴ�.");
//		return;
//	}
//}

void GameEngineRenderingpipeline::AllShaderReset()
{
	GameEngineDevice::GetContext()->VSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->DSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->HSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->PSSetShader(nullptr, nullptr, 0);
}

GameEngineRenderingpipeline* GameEngineRenderingpipeline::Create()
{
	return CreateResUnName();
}

GameEngineRenderingpipeline* GameEngineRenderingpipeline::Create(const std::string& _Name)
{
	return CreateResName(_Name);
}

void GameEngineRenderingpipeline::SetInputAssembler1VertexBuffer(const std::string& _Name)
{
	VertexBuffer = GameEngineVertexBuffer::Find(_Name);

	if (nullptr == VertexBuffer)
	{
		MsgBoxAssert("�������� �ʴ� ���ؽ� ���۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}


	if (nullptr == InputLayOut && nullptr != VertexShader)
	{
		InputLayOut = GameEngineInputLayOut::Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	}
}

void GameEngineRenderingpipeline::SetVertexShader(const std::string& _Name)
{
	VertexShader = GameEngineVertexShader::Find(_Name);

	if (nullptr == VertexShader)
	{
		MsgBoxAssert("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// ��ǲ���̾ƿ��� ��������� �ʾҴµ�.
	if (nullptr == InputLayOut && nullptr != VertexBuffer)
	{
		InputLayOut = GameEngineInputLayOut::Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	}
}

void GameEngineRenderingpipeline::SetInputAssembler2IndexBuffer(const std::string& _Name)
{
	IndexBuffer = GameEngineIndexBuffer::Find(_Name);

	if (nullptr == IndexBuffer)
	{
		MsgBoxAssert("�������� �ʴ� �ε������۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingpipeline::SetRasterizer(const std::string& _Name)
{
	Rasterizer = GameEngineRasterizer::Find(_Name);

	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("�������� �ʴ� �����Ͷ����� ���ø� �����Ϸ��� �߽��ϴ�.");
		return;
	}

}


void GameEngineRenderingpipeline::SetPixelShader(const std::string& _Name)
{
	PixelShader = GameEnginePixelShader::Find(_Name);

	if (nullptr == PixelShader)
	{
		MsgBoxAssert("�������� �ʴ� �ȼ����̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

}



void GameEngineRenderingpipeline::SetOutputMergerDepthStencil(const std::string& _Name)
{
	DepthStencil = GameEngineDepthStencil::Find(_Name);

	if (nullptr == DepthStencil)
	{
		MsgBoxAssert("�������� �ʴ� ���̽��ٽǸ� �����Ϸ��� �߽��ϴ�.");
		return;
	}

}


void GameEngineRenderingpipeline::SetOutputMergerBlend(const std::string& _Name)
{
	Blend = GameEngineBlend::Find(_Name);

	if (nullptr == Blend)
	{
		MsgBoxAssert("�������� �ʴ� ������ �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingpipeline::Rendering(bool IsInstancing /*= false*/)
{
	if (true == IsInstancing)
	{
		// ������ ������ �Ѵ�.
		InstancingDataCollect();
		return;
	}

	InputAssembler1VertexBufferSetting();

	VertexShaderSetting();

	InputAssembler2IndexBufferSetting();

	RasterizerSetting();

	PixelShaderSetting();

	OutputMergerBlendSetting();

	OutputMergerDepthStencilSetting();

	Draw();
}

void GameEngineRenderingpipeline::InstancingDataCollect()
{
	// InstancingDraw();
}


void GameEngineRenderingpipeline::InputAssembler1VertexBufferSetting()
{
	// �׷��ȸ��ҽ��� Setting�̶�� �Լ��� �����Ѵٸ�
	InputLayOut->Setting();
	// ���ؽ� ���۴� �����Ұ� ����.
	VertexBuffer->Setting();
}

void GameEngineRenderingpipeline::VertexShaderSetting()
{
	VertexShader->Setting();
	// ��ġ 
	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

void GameEngineRenderingpipeline::InputAssembler2IndexBufferSetting()
{
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(Topology);

	IndexBuffer->Setting();
}

void GameEngineRenderingpipeline::RasterizerSetting()
{
	Rasterizer->Setting();
}

void GameEngineRenderingpipeline::PixelShaderSetting()
{
	PixelShader->Setting();
}

void GameEngineRenderingpipeline::OutputMergerBlendSetting()
{
	Blend->Setting();
}

void GameEngineRenderingpipeline::OutputMergerDepthStencilSetting()
{
	DepthStencil->Setting();
}


void GameEngineRenderingpipeline::Draw()
{
	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer->GetIndexCount(), 0, 0);
}


void GameEngineRenderingpipeline::InstancingDraw()
{
	//[in] IndexCountPerInstance ���� : UINT
	//�� �ν��Ͻ��� ���� �ε��� ���ۿ��� ���� �ε��� ���Դϴ�.
	//

	//[in] InstanceCount ���� : UINT
	//�׸� �ν��Ͻ� ���Դϴ�.

	//[in] StartIndexLocation
	//���� : UINT GPU�� �ε��� ���ۿ��� ���� ù ��° �ε����� ��ġ�Դϴ�.

	//[in] BaseVertexLocation ���� : ����
	//���� ���ۿ��� ������ �б� ���� �� �ε����� �߰��� ���Դϴ�.

	//[in] StartInstanceLocation ���� : UINT
	//���� ���ۿ��� �ν��Ͻ��� �����͸� �б� ���� �� �ε����� �߰��� ���Դϴ�.

	// �׳� 4�� ����.
	GameEngineDevice::GetContext()->DrawIndexedInstanced(IndexBuffer->GetIndexCount(), 100, 0, 0, 0);
}

void GameEngineRenderingpipeline::Copy(GameEngineRenderingpipeline* _Original)
{
	InputLayOut = _Original->InputLayOut;
	VertexBuffer = _Original->VertexBuffer;
	VertexShader = _Original->VertexShader;
	IndexBuffer = _Original->IndexBuffer;
	Topology = _Original->Topology;
	Rasterizer = _Original->Rasterizer;
	PixelShader = _Original->PixelShader;
	DepthStencil = _Original->DepthStencil;
	Blend = _Original->Blend;

}

void GameEngineRenderingpipeline::SetWireFrame()
{
	Rasterizer = GameEngineRasterizer::Find("EngineRasterizer_Wire");
}
