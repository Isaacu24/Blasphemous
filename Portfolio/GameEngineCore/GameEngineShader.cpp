#include "PreCompile.h"
#include "GameEngineShader.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineStructuredBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

void GameEngineConstantBufferSetter::Setting() const
{
	Res->ChangeData(SetData, Size);
	SettingFunction();
}

void GameEngineTextureSetter::Setting() const
{
	SettingFunction();
}

void GameEngineTextureSetter::Reset() const
{
	ResetFunction();
}

void GameEngineSamplerSetter::Setting() const
{
	SettingFunction();
}

void GameEngineShader::AutoCompile(const std::string& _Path)
{
	GameEngineFile File = GameEngineFile(_Path);
	File.Open(OpenMode::Read, FileMode::Text);

	std::string AllHlslCode = File.GetString();

	size_t VSEntryIndex = AllHlslCode.find("_VS(");
	// 0123456789
	//"a Color_VS("
	// VSEntryIndex == 7
	if (std::string::npos != VSEntryIndex)
	{
		// size_t VSEntryIndex = AllHlslCode.find("_VS(");
		// 7부터 찾아라 앞쪽으로
		// 1
		size_t FirstIndex = AllHlslCode.find_last_of(" ", VSEntryIndex);
		// "01234567"
		// substr(2, 3); "234"

		// ' 'Color_VS 
		std::string EntryName = AllHlslCode.substr(FirstIndex + 1, VSEntryIndex - FirstIndex - 1);
		EntryName += "_VS";
		GameEngineVertexShader::Load(_Path, EntryName);
	}

	size_t PSEntryIndex = AllHlslCode.find("_PS(");
	if (std::string::npos != PSEntryIndex)
	{
		size_t FirstIndex = AllHlslCode.find_last_of(" ", PSEntryIndex);
		std::string EntryName = AllHlslCode.substr(FirstIndex + 1, PSEntryIndex - FirstIndex - 1);
		EntryName += "_PS";
		GameEnginePixelShader::Load(_Path, EntryName);
	}

	// File.GetFileSize();

}

GameEngineShader::GameEngineShader()
	: Version("")
	, BinaryPtr(nullptr)
{
}

GameEngineShader::~GameEngineShader()
{
	if (nullptr != BinaryPtr)
	{
		BinaryPtr->Release();
		BinaryPtr = nullptr;
	}
}



void GameEngineShader::CreateVersion(const std::string& _ShaderType, UINT _VersionHigh, UINT _VersionLow)
{
	Version = "";
	Version += _ShaderType + "_"; // vs_
	Version += std::to_string(_VersionHigh); // vs_5
	Version += "_"; // vs_5_
	Version += std::to_string(_VersionLow); // vs_5_0
}

// 쉐이더에서 상수버퍼를 사용했는지 텍스처를 썼는지
void GameEngineShader::ShaderResCheck()
{
	// BinaryPtr 완전히 빌드된 쉐이더 파일의 2진 메모리
	if (nullptr == BinaryPtr)
	{
		MsgBoxAssert("쉐이더 리소스가 만들어지지 않았는데 리소스(상수버퍼 and 텍스처) 체크를 하려고 했습니다.");
		return;
	}

	// Reflection 
	// 클래스의 세부 정보를 언어차원에서 우리에게 제공해줄때 그 클래스나 함수들이 이런 이름을 가지고 있다.
	// 이런 이름의 인터페이스 
	ID3D11ShaderReflection* CompileInfo = nullptr;

	if (S_OK != D3DReflect(
		BinaryPtr->GetBufferPointer(),
		BinaryPtr->GetBufferSize(),
		IID_ID3D11ShaderReflection,
		reinterpret_cast<void**>(&CompileInfo)
	))
	{
		MsgBoxAssert("쉐이더 리플렉션이 잘못 되었습니다.");
		return;
	}


	D3D11_SHADER_DESC Info;
	CompileInfo->GetDesc(&Info);

	D3D11_SHADER_INPUT_BIND_DESC ResInfo;

	// Info.BoundResources 이게 이 쉐이더에서 사용된 총 리소스 양
	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		CompileInfo->GetResourceBindingDesc(i, &ResInfo);
		std::string Name = GameEngineString::ToUpperReturn(ResInfo.Name);
		D3D_SHADER_INPUT_TYPE Type = ResInfo.Type;

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResInfo.Name);
			D3D11_SHADER_BUFFER_DESC BufferDesc;
			CBufferPtr->GetDesc(&BufferDesc);

			GameEngineConstantBufferSetter NewSetter;
			NewSetter.ParentShader = this;
			NewSetter.SetName(Name);
			NewSetter.ShaderType = ShaderSettingType;
			NewSetter.Res = GameEngineConstantBuffer::CreateAndFind(Name, BufferDesc);
			NewSetter.BindPoint = ResInfo.BindPoint;
			ConstantBufferMap.insert(std::make_pair(Name, NewSetter));

			break;
		}
		case D3D_SIT_TEXTURE:
		{
			GameEngineTextureSetter NewSetter;
			NewSetter.ParentShader = this;
			NewSetter.SetName(Name);
			NewSetter.ShaderType = ShaderSettingType;
			NewSetter.Res = GameEngineTexture::Find("NSet.png");
			NewSetter.BindPoint = ResInfo.BindPoint;
			TextureMap.insert(std::make_pair(Name, NewSetter));
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			GameEngineSamplerSetter NewSetter;
			NewSetter.ParentShader = this;
			NewSetter.SetName(Name);
			NewSetter.ShaderType = ShaderSettingType;
			NewSetter.Res = GameEngineSampler::Find("EngineSamplerPoint");
			NewSetter.BindPoint = ResInfo.BindPoint;
			SamplerMap.insert(std::make_pair(Name, NewSetter));
			break;
		}
		case D3D_SIT_STRUCTURED:
		{
			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResInfo.Name);
			D3D11_SHADER_BUFFER_DESC BufferDesc;
			CBufferPtr->GetDesc(&BufferDesc);

			GameEngineStructuredBufferSetter NewSetter;
			NewSetter.ParentShader = this;
			NewSetter.SetName(Name);
			NewSetter.ShaderType = ShaderSettingType;
			// 아직은 데이터의 사이즈는 알수있어도 이걸로 몇개짜리 버퍼를 만들지는 알수가 없다.
			NewSetter.Res = GameEngineStructuredBuffer::CreateAndFind(Name, BufferDesc, 0);
			NewSetter.BindPoint = ResInfo.BindPoint;

			StructuredBufferMap.insert(std::make_pair(Name, NewSetter));

			break;
		}
		default:
			MsgBoxAssert("아직 처리하지 않은 쉐이더 리소스");
			break;
		}
	}

	ConstantBufferMap;
	TextureMap;
}

GameEngineConstantBufferSetter& GameEngineShader::GetConstantBufferSetter(std::string _Name)
{
	std::string Name = GameEngineString::ToUpperReturn(_Name);

	if (ConstantBufferMap.end() == ConstantBufferMap.find(Name))
	{
		MsgBoxAssert("존재하지 않는 상수버퍼를 찾으려고 했습니다.");
	}

	return ConstantBufferMap[Name];
}