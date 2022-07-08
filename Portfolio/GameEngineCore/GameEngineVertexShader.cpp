#include "PreCompile.h"
#include "GameEngineVertexShader.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineVertexShader::GameEngineVertexShader()
	: ShaderPtr(nullptr)
{
	ShaderSettingType = ShaderType::Vertex;
}

GameEngineVertexShader::~GameEngineVertexShader()
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

void GameEngineVertexShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgBoxAssert("쉐이더 세팅 오류");
	}

	// 두번째 인자는 #include나 #define등 hlsl에서 사용할 헤더나 디파인의 객체를 넣어줄 수 있음
	GameEngineDevice::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}

GameEngineVertexShader* GameEngineVertexShader::Load(std::string _Path, std::string _EntryPoint, UINT _VersionHigh /*= 5*/, UINT _VersionLow /*= 0*/)
{
	return Load(_Path, GameEnginePath::GetFileName(_Path), _EntryPoint, _VersionHigh, _VersionLow);
}


GameEngineVertexShader* GameEngineVertexShader::Load(std::string _Path, std::string _Name, std::string _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
{
	GameEngineVertexShader* NewRes = CreateResName(_Name);
	NewRes->ShaderCompile(_Path, _EntryPoint, _VersionHigh, _VersionLow);

	return nullptr;
}


void GameEngineVertexShader::ShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	CreateVersion("vs", _VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif
	// 셰이더는 기본적으로 전치행렬이 들어감
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* Error;

	std::wstring UnicodePath = GameEngineString::AnsiToUnicodeReturn(_Path);

	// HLSL 파일 컴파일
	if (D3DCompileFromFile(
		UnicodePath.c_str(), // 파일 경로
		nullptr,  // 매크로
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // 헤더
		_EntryPoint.c_str(), // 진입점 COLOR_VS(
		Version.c_str(),  // vs_5_0
		Flag,
		0,
		&BinaryPtr,
		&Error)
		)
	{
		std::string ErrorText = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgBoxAssertString(ErrorText);
		return;
	}

	// 컴파일된 HLSL 파일의 바이너리 코드를 넣어줘서 생성하는 방식
	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(
		BinaryPtr->GetBufferPointer(),
		BinaryPtr->GetBufferSize(),
		nullptr,
		&ShaderPtr))
	{
		MsgBoxAssert("버텍스 쉐이더 핸들 생성에 실패했습니다.");
	}

	ShaderResCheck();
}