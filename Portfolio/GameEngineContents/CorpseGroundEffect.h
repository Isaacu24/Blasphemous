#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class CorpseGroundEffect : public GameEngineActor
{
public:
	CorpseGroundEffect();
	~CorpseGroundEffect();

	CorpseGroundEffect(const CorpseGroundEffect& _Other) = delete;
	CorpseGroundEffect(CorpseGroundEffect&& _Other) noexcept = delete;
	CorpseGroundEffect& operator=(const CorpseGroundEffect& _Other) = delete;
	CorpseGroundEffect& operator=(CorpseGroundEffect&& _Other) noexcept = delete;
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer_;

	inline void EffetEnd(const FrameAnimation_DESC& _Info, CorpseGroundEffect* _Actor)
	{
		_Actor->Death();
	}

};

