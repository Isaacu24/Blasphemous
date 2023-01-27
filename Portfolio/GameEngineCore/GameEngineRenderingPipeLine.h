#pragma once
#include "GameEngineRes.h"


// 설명 :
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

	// 점의 구조를 알려주는 인풋레이아웃도 이 단계에서 세팅된다.
	void SetInputAssembler1VertexBuffer(const std::string& _Name);

	// 버텍스 쉐이더
	// 즉 점을 내마음대로 수치를 변경할수 있는 단계
	void SetVertexShader(const std::string& _Name);

	// 인덱스 버퍼가 세팅된다.
	void SetInputAssembler2IndexBuffer(const std::string& _Name);

	// 점들을 진짜 모니터 위치로 옮겨주는 역할
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
	GameEngineInputLayOut* InputLayOut; // 인풋어셈블러1 세팅
	GameEngineVertexBuffer* VertexBuffer; // 인풋어셈블러1 세팅

	// 정점을 이렇게 처리해.
	GameEngineVertexShader* VertexShader; // 버텍스쉐이더 세팅

	GameEngineIndexBuffer* IndexBuffer; // 인풋어셈블러2 세팅

	D3D11_PRIMITIVE_TOPOLOGY Topology;// 인풋어셈블러2 세팅

	GameEngineRasterizer* Rasterizer; // 레스터라이저 세팅

	// 픽셀을 이렇게 처리해.
	GameEnginePixelShader* PixelShader; // 픽셀쉐이더 세팅

	GameEngineDepthStencil* DepthStencil; // 아웃풋머저 누가 앞인지 세팅 

	GameEngineBlend* Blend; // 아웃풋머저 색상통합 세팅 


	// 아래쪽 함수들의 실행
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


