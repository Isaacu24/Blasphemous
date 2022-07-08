#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineVertexBuffer::GameEngineVertexBuffer() 
	: Buffer(nullptr)
	, BufferDesc{}
	, OffSet(0)
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer() 
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
	}
}

GameEngineVertexBuffer* GameEngineVertexBuffer::Create(
	const std::string& _Name, 
	const void* _Data, UINT _VertexSize,
	UINT _VertexCount,
	const GameEngineLayOutDesc& _LayOut)
{
	GameEngineVertexBuffer* NewRes = CreateResName(_Name);
	NewRes->LayOutDesc = &_LayOut;
	NewRes->BufferCreate(_Data, _VertexSize, _VertexCount);
	return NewRes;
}

void GameEngineVertexBuffer::BufferCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
	VertexSize = _VertexSize;
	VertexCount = _VertexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	//UINT ByteWidth; // �Ҵ��Ϸ��� ������ ũ��
	//D3D11_USAGE Usage; // �Ҵ��Ϸ��� ������ �׼��� ���Ѱ� �뵵
	//UINT BindFlags; // ������ �������� �뵵
	//UINT CPUAccessFlags; // CPU���� �׼��� �Ҽ� �ִ���
	//UINT MiscFlags; // 
	//UINT StructureByteStride;

	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.ByteWidth = _VertexSize * _VertexCount;

	// VertexCount = _Size / 

	BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	// BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	BufferDesc.CPUAccessFlags = 0;

	// �߰� �ɼ�(��� ����)
	BufferDesc.MiscFlags = 0;
	// ���ؽ� ���ۿ����� �������� �ʿ� ����
	BufferDesc.StructureByteStride = 0;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, &Data, &Buffer))
	{
		MsgBoxAssert("���ؽ� ���� ������ �����߽��ϴ�.");
	}
}

void GameEngineVertexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert("���ؽ� ���ۿ� ������ �ֽ��ϴ�.");
	}

	GameEngineDevice::GetContext()->IASetVertexBuffers(
		0, // ���ؽ� ������ ������ �ε���
		1, &Buffer, &VertexSize, &OffSet);
}






