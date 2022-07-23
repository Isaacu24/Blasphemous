#pragma once
#include "GameEngineDefaultRenderer.h"


class MetaAnimation_DESC
{
public:
	std::string TextureName_;

	unsigned int CurFrame_;
	unsigned int Start_;
	unsigned int End_;

	float FrameTime_;

	float Inter_; // 0.1f

	bool Loop_;

public:
	MetaAnimation_DESC()
		: Loop_(false)
		, Inter_(0.1f)
		, CurFrame_(-1)
		, Start_(-1)
		, End_(-1)
		, FrameTime_(0.0f)
	{

	}
};

class GameEngineMetaRenderer;
class MetaAnimation : public GameEngineNameObject
{
	friend GameEngineMetaRenderer;

	MetaAnimation_DESC Info_;

	GameEngineMetaRenderer* ParentRenderer_;
	GameEngineTexture* Texture_;

	void Update(float _DeltaTime);
};

class GameEngineMeta;
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
	GameEngineTexture* CurTex_;
	std::map<std::string, MetaAnimation*> MetaAni_;
	
	float4 MetaData_;
	MetaAnimation* CurAni_;
};

