#include "PreCompile.h"
#include "GameEngineShaderResourcesHelper.h"
#include "GameEnginePixelShader.h"
#include "GameEngineVertexShader.h"

GameEngineShaderResourcesHelper::GameEngineShaderResourcesHelper()
{
}

GameEngineShaderResourcesHelper::~GameEngineShaderResourcesHelper()
{
}

void GameEngineShaderResourcesHelper::ResourcesCheck(GameEngineRenderingPipeLine* _Line)
{
	//렌더링 파이프라인 셰이더 체크
	ShaderCheck(_Line->GetVertexShader());
	ShaderCheck(_Line->GetPixelShader());

}

void GameEngineShaderResourcesHelper::ShaderCheck(GameEngineShader* _Shader)
{
	// 픽셀쉐이더와 버텍스 쉐이더에서 TransformData 같은 중요 상수 버퍼의 이름을 똑같이 해서 사용하기 위해 multimap
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Data : _Shader->ConstantBufferMap)
	{
		ConstantBufferMap.insert(std::make_pair(Data.first, Data.second));
	}

	for (const std::pair<std::string, GameEngineTextureSetter>& Data : _Shader->TextureSetterMap)
	{
		TextureSetterMap.insert(std::make_pair(Data.first, Data.second));
	}
}

bool GameEngineShaderResourcesHelper::IsConstantBufferSetter(const std::string& _Name)
{
	std::string Key = GameEngineString::ToUpperReturn(_Name);

	if (ConstantBufferMap.end() != ConstantBufferMap.find(Key))
	{
		return true;
	}

	return false;
}