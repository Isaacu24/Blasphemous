#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Deogracias : public GameEngineActor
{
public:
	Deogracias();
	~Deogracias();

	Deogracias(const Deogracias& _Other) = delete;
	Deogracias(Deogracias&& _Other) noexcept = delete;
	Deogracias& operator=(const Deogracias& _Other) = delete;
	Deogracias& operator=(Deogracias&& _Other) noexcept = delete;

	void ChangeFrontAnimation();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer_;
};

