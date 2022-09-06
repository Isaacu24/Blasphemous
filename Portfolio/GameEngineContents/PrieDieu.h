#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ObjectBase.h"

// 세이브 포인트
class PrieDieu
    : public GameEngineActor
    , public ObjectBase
{
public:
	PrieDieu();
	~PrieDieu();

	PrieDieu(const PrieDieu& _Other) = delete;
	PrieDieu(PrieDieu&& _Other) noexcept = delete;
	PrieDieu& operator=(const PrieDieu& _Other) = delete;
	PrieDieu& operator=(PrieDieu&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	class GameEngineTextureRenderer* Renderer_;

private:
};

