#pragma once
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineShader.h"

//���̴��� ������� �ؽ��� ��� �ѹ� ���� �������̽�
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

	void ResourcesCheck(GameEngineRenderingPipeLine* _Line);

	bool IsConstantBufferSetter(const std::string& _Name);

protected:
	void ShaderCheck(GameEngineShader* _Shader);

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferMap;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetterMap;
};

