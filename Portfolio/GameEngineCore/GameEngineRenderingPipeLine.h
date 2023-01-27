#pragma once
#include "GameEngineRes.h"


// ���� :
class GameEngineInputLayOut;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineDepthStencil;
class GameEngineBlend;
class GameEngineRenderingpipeline : public GameEngineRes<GameEngineRenderingpipeline>
{
public:
	static void AllShaderReset();

	static GameEngineRenderingpipeline* Create();

	static GameEngineRenderingpipeline* Create(const std::string& _Name);

public:
	// constrcuter destructer
	GameEngineRenderingpipeline();
	~GameEngineRenderingpipeline();

	// delete Function
	GameEngineRenderingpipeline(const GameEngineRenderingpipeline& _Other) = delete;
	GameEngineRenderingpipeline(GameEngineRenderingpipeline&& _Other) noexcept = delete;
	GameEngineRenderingpipeline& operator=(const GameEngineRenderingpipeline& _Other) = delete;
	GameEngineRenderingpipeline& operator=(GameEngineRenderingpipeline&& _Other) noexcept = delete;

	// void SetInputAssembler1InputLayOutSetting(const std::string& _Name);

	// ���� ������ �˷��ִ� ��ǲ���̾ƿ��� �� �ܰ迡�� ���õȴ�.
	void SetInputAssembler1VertexBuffer(const std::string& _Name);

	// ���ؽ� ���̴�
	// �� ���� ��������� ��ġ�� �����Ҽ� �ִ� �ܰ�
	void SetVertexShader(const std::string& _Name);

	// �ε��� ���۰� ���õȴ�.
	void SetInputAssembler2IndexBuffer(const std::string& _Name);

	// ������ ��¥ ����� ��ġ�� �Ű��ִ� ����
	void SetRasterizer(const std::string& _Name);

	void SetPixelShader(const std::string& _Name);

	void SetOutputMergerBlend(const std::string& _Name);

	void SetOutputMergerDepthStencil(const std::string& _Name);

	void Rendering(bool IsInstancing = false);

	inline GameEngineVertexShader* GetVertexShader()
	{
		return VertexShader;
	}

	inline GameEnginePixelShader* GetPixelShader()
	{
		return PixelShader;
	}

	void Copy(GameEngineRenderingpipeline* _Original);

	void SetWireFrame();

protected:


private:
	GameEngineInputLayOut* InputLayOut; // ��ǲ�����1 ����
	GameEngineVertexBuffer* VertexBuffer; // ��ǲ�����1 ����

	// ������ �̷��� ó����.
	GameEngineVertexShader* VertexShader; // ���ؽ����̴� ����

	GameEngineIndexBuffer* IndexBuffer; // ��ǲ�����2 ����

	D3D11_PRIMITIVE_TOPOLOGY Topology;// ��ǲ�����2 ����

	GameEngineRasterizer* Rasterizer; // �����Ͷ����� ����

	// �ȼ��� �̷��� ó����.
	GameEnginePixelShader* PixelShader; // �ȼ����̴� ����

	GameEngineDepthStencil* DepthStencil; // �ƿ�ǲ���� ���� ������ ���� 

	GameEngineBlend* Blend; // �ƿ�ǲ���� �������� ���� 


	// �Ʒ��� �Լ����� ����
	void InputAssembler1VertexBufferSetting();

	void VertexShaderSetting();

	void InputAssembler2IndexBufferSetting();

	void RasterizerSetting();

	void PixelShaderSetting();

	void OutputMergerBlendSetting();

	void OutputMergerDepthStencilSetting();

	void Draw();

	void InstancingDraw();

	void InstancingDataCollect();
};


