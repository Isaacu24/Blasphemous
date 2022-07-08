#pragma once
#include <string>
#include <map>

enum class ShaderType
{
	Vertex,
	Pixel,
};

class ShaderResSetter 
{
public:
	ShaderType ShaderType; //셰이더 타입
	int BindPoint; //레지스터 슬롯
	std::string* Name; //
};

//상수 버퍼 세터
class GameEngineConstantBuffer;
class GameEngineConstantBufferSetter : public ShaderResSetter
{
public:
	GameEngineConstantBuffer* Buffer;
};

//텍스쳐 버퍼 세터
class GameEngineConstantBuffer;
class GameEngineTextureSetter : public ShaderResSetter
{

};

class GameEngineShaderResourcesHelper;
class GameEngineShader
{
	friend GameEngineShaderResourcesHelper;

public:
	static void AutoCompile(const std::string& _Path);

public:
	GameEngineShader();
	virtual ~GameEngineShader();
	
	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

	GameEngineConstantBufferSetter& GetConstantBufferSetter(std::string _Name);

protected:
	void ShaderResCheck();

	void CreateVersion(const std::string& _ShaderType, UINT _VersionHigh, UINT _VersionLow);

	void SetEntryPoint(const std::string& _EntryPoint)
	{
		EntryPoint = _EntryPoint;
	}

	ID3DBlob* BinaryPtr;
	std::string Version;
	ShaderType ShaderSettingType;

private:
	std::map<std::string, GameEngineConstantBufferSetter> ConstantBufferMap;
	std::map<std::string, GameEngineTextureSetter> TextureSetterMap;

	std::string EntryPoint;
};

