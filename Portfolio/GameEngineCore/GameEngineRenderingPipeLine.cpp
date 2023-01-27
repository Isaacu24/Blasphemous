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
//		MsgBoxAssert("존재하지 않는 인풋레이아웃을 세팅하려고 했습니다.");
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
		MsgBoxAssert("존재하지 않는 버텍스 버퍼를 세팅하려고 했습니다.");
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
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
		return;
	}

	// 인풋레이아웃이 만들어지지 않았는데.
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
		MsgBoxAssert("존재하지 않는 인덱스버퍼를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingpipeline::SetRasterizer(const std::string& _Name)
{
	Rasterizer = GameEngineRasterizer::Find(_Name);

	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("존재하지 않는 레스터라이저 세팅를 세팅하려고 했습니다.");
		return;
	}

}


void GameEngineRenderingpipeline::SetPixelShader(const std::string& _Name)
{
	PixelShader = GameEnginePixelShader::Find(_Name);

	if (nullptr == PixelShader)
	{
		MsgBoxAssert("존재하지 않는 픽셀쉐이더를 세팅하려고 했습니다.");
		return;
	}

}



void GameEngineRenderingpipeline::SetOutputMergerDepthStencil(const std::string& _Name)
{
	DepthStencil = GameEngineDepthStencil::Find(_Name);

	if (nullptr == DepthStencil)
	{
		MsgBoxAssert("존재하지 않는 깊이스텐실를 세팅하려고 했습니다.");
		return;
	}

}


void GameEngineRenderingpipeline::SetOutputMergerBlend(const std::string& _Name)
{
	Blend = GameEngineBlend::Find(_Name);

	if (nullptr == Blend)
	{
		MsgBoxAssert("존재하지 않는 블랜더를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingpipeline::Rendering(bool IsInstancing /*= false*/)
{
	if (true == IsInstancing)
	{
		// 데이터 수집을 한다.
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
	// 그래픽리소스에 Setting이라는 함수가 존재한다면
	InputLayOut->Setting();
	// 버텍스 버퍼는 세팅할게 없다.
	VertexBuffer->Setting();
}

void GameEngineRenderingpipeline::VertexShaderSetting()
{
	VertexShader->Setting();
	// 위치 
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
	//[in] IndexCountPerInstance 유형 : UINT
	//각 인스턴스에 대해 인덱스 버퍼에서 읽은 인덱스 수입니다.
	//

	//[in] InstanceCount 유형 : UINT
	//그릴 인스턴스 수입니다.

	//[in] StartIndexLocation
	//유형 : UINT GPU가 인덱스 버퍼에서 읽은 첫 번째 인덱스의 위치입니다.

	//[in] BaseVertexLocation 유형 : 지능
	//정점 버퍼에서 정점을 읽기 전에 각 인덱스에 추가된 값입니다.

	//[in] StartInstanceLocation 유형 : UINT
	//정점 버퍼에서 인스턴스별 데이터를 읽기 전에 각 인덱스에 추가된 값입니다.

	// 그냥 4가 들어간다.
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
