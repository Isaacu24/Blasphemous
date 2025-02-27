#pragma once
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineShader.h"

class GameEngineShader;
class GameEngineShaderResourcesHelper
{
	friend GameEngineShader;

public:
	GameEngineShaderResourcesHelper();
	~GameEngineShaderResourcesHelper();

	GameEngineShaderResourcesHelper(const GameEngineShaderResourcesHelper& _Other) = delete;
	GameEngineShaderResourcesHelper(GameEngineShaderResourcesHelper&& _Other) noexcept = delete;
	GameEngineShaderResourcesHelper& operator=(const GameEngineShaderResourcesHelper& _Other) = delete;
	GameEngineShaderResourcesHelper& operator=(GameEngineShaderResourcesHelper&& _Other) noexcept = delete;

	void AllResourcesSetting();

	void AllResourcesReset();

	void ResourcesCheck(GameEngineRenderingpipeline* _Line);

	bool IsConstantBuffer(const std::string& _Name);

	template<typename Res>
	void SetConstantBufferLink(const std::string& _Name, const Res& Data)
	{
		SetConstantBufferLink(_Name, &Data, sizeof(Res));
	}

	void SetConstantBufferLink(const std::string& _Name, const void* Data, UINT _Size);

	template<typename Res>
	void SetConstantBufferNew(const std::string& _Name, const Res& Data)
	{
		SetConstantBufferNew(_Name, &Data, sizeof(Res));
	}

	void SetConstantBufferNew(const std::string& _Name, const void* Data, UINT _Size);

	bool IsTexture(const std::string& _Name);

	GameEngineTexture* SetTexture(const std::string& _Name, const std::string& _TextureName);

	GameEngineTexture* SetTexture(const std::string& _Name, GameEngineTexture* _TextureName);

	bool IsSampler(const std::string& _Name);

	GameEngineSampler* SetSampler(const std::string& _Name, const std::string& _TextureName);

	GameEngineSampler* SetSampler(const std::string& _Name, GameEngineSampler* _SamplerName);


protected:
	void ShaderCheck(GameEngineShader* _Shader);

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSettingMap;
	std::multimap<std::string, GameEngineTextureSetter> TextureSettingMap;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSettingMap;

	void BindConstantBuffer(GameEngineConstantBufferSetter& _Setter, GameEngineConstantBuffer* _Res);
	void BindSampler(GameEngineSamplerSetter& _Setter, GameEngineSampler* _Res);
	void BindTexture(GameEngineTextureSetter& _Setter, GameEngineTexture* _Res);
};

