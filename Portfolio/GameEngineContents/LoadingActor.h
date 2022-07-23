#pragma once
#include <GameEngineCore/GameEngineActor.h>

class LoadingActor : public GameEngineActor
{
public:
	LoadingActor();
	~LoadingActor();

	LoadingActor(const LoadingActor& _Other) = delete;
	LoadingActor(LoadingActor&& _Other) noexcept = delete;
	LoadingActor& operator=(const LoadingActor& _Other) = delete;
	LoadingActor& operator=(LoadingActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer_;

	float RendererTime_;

	int CurrentFrame_;
};

