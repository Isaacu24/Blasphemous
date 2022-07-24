#pragma once
#include "GameEngineDefaultRenderer.h"


//class MetaAnimation_DESC
//{
//public:
//	std::string TextureName_;
//
//	unsigned int CurFrame_;
//	unsigned int Start_;
//	unsigned int End_;
//
//	float FrameTime_;
//
//	float Inter_; // 0.1f
//
//	bool Loop_;
//
//public:
//	MetaAnimation_DESC()
//		: Loop_(false)
//		, Inter_(0.1f)
//		, CurFrame_(-1)
//		, Start_(-1)
//		, End_(-1)
//		, FrameTime_(0.0f)
//	{
//
//	}
//};

class GameEngineMetaRenderer;
class MetaAnimation : public GameEngineNameObject
{
	friend GameEngineMetaRenderer;

	GameEngineTexture* Texture_; //아틀라스 이미지
	std::vector<class GameEngineMetaData*> Datas_; //프레임별 메타 데이터

	void Update(float _DeltaTime);
};

class GameEngineMetaData;
class GameEngineMetaRenderer : public GameEngineDefaultRenderer
{
public:
	GameEngineMetaRenderer();
	~GameEngineMetaRenderer();

	GameEngineMetaRenderer(const GameEngineMetaRenderer& _Other) = delete;
	GameEngineMetaRenderer(GameEngineMetaRenderer&& _Other) noexcept = delete;
	GameEngineMetaRenderer& operator=(const GameEngineMetaRenderer& _Other) = delete;
	GameEngineMetaRenderer& operator=(GameEngineMetaRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

/*
* CreateMetaAnimation();
* 
* //메타데이터를 얻어온다. 
* 애니메이션 이름(텍스쳐 이름)과 메타 데이터의 이름이 동일한지 확인
* 
* 
*/