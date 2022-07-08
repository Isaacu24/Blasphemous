#pragma once
#include "GameEngineRes.h"


class GameEngineInputLayOut;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineDepthStencil;
class GameEngineBlend;
class GameEngineRenderingPipeLine : public GameEngineRes<GameEngineRenderingPipeLine>
{
public:
	static GameEngineRenderingPipeLine* Create(const std::string& _Name);

public:
	GameEngineRenderingPipeLine();
	~GameEngineRenderingPipeLine();

	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

	//void SetInputAssembler1InputLayOutSetting(const std::string& _Name);

	void SetInputAssembler1VertexBuffer(const std::string& _Name);

	void SetVertexShader(const std::string& _Name);

	void SetInputAssembler2IndexBuffer(const std::string& _Name);

	void SetRasterizer(const std::string& _Name);

	void SetPixelShader(const std::string& _Name);

	void SetOutputMergerBlend(const std::string& _Name);

	void SetOutputMergerDepthStencil(const std::string& _Name);

	void Rendering();

	inline GameEngineVertexShader* GetVertexShader()
	{
		return VertexShader;
	}

	inline GameEnginePixelShader* GetPixelShader()
	{
		return PixelShader;
	}

protected:


private:
	GameEngineInputLayOut* InputLayOut; // ��ǲ�������1 ����

	GameEngineVertexBuffer* VertexBuffer; // ��ǲ�������1 ����

	//HLSL ��� �ܰ�
	GameEngineVertexShader* VertexShader; // ���ؽ����̴� ����

	GameEngineIndexBuffer* IndexBuffer; // ��ǲ�������2 ����

	D3D11_PRIMITIVE_TOPOLOGY Topology;// ��ǲ�������2 ����

	GameEngineRasterizer* Rasterizer; // �����Ͷ����� ����

	GameEnginePixelShader* PixelShader; // �ȼ����̴� ����

	GameEngineDepthStencil* DepthStencil; // �ƿ�ǲ���� ���� 

	GameEngineBlend* Blend; // �ƿ�ǲ���� �������� ���� 


	void InputAssembler1VertexBufferSetting();

	void VertexShaderSetting();

	void InputAssembler2IndexBufferSetting();

	void RasterizerSetting();

	void PixelShaderSetting();

	void OutputMergerBlendSetting();

	void OutputMergerDepthStencilSetting();

	void Draw();
};


