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

	//UINT ByteWidth; // 할당하려는 버퍼의 크기
	//D3D11_USAGE Usage; // 할당하려는 버퍼의 액세스 권한과 용도
	//UINT BindFlags; // 버퍼의 랜더링적 용도
	//UINT CPUAccessFlags; // CPU에서 액세스 할수 있는지
	//UINT MiscFlags; // 
	//UINT StructureByteStride;

	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.ByteWidth = _VertexSize * _VertexCount;

	// VertexCount = _Size / 

	BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	// BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	BufferDesc.CPUAccessFlags = 0;

	// 추가 옵션(사용 안함)
	BufferDesc.MiscFlags = 0;
	// 버텍스 버퍼에서는 세팅해줄 필요 없음
	BufferDesc.StructureByteStride = 0;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, &Data, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
	}
}

void GameEngineVertexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert("버텍스 버퍼에 문제가 있습니다.");
	}

	GameEngineDevice::GetContext()->IASetVertexBuffers(
		0, // 버텍스 버퍼의 사용시작 인덱스
		1, &Buffer, &VertexSize, &OffSet);
}






