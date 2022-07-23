#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BreakableTwistedCorpse : public GameEngineActor
{
public:
	BreakableTwistedCorpse();
	~BreakableTwistedCorpse();

	BreakableTwistedCorpse(const BreakableTwistedCorpse& _Other) = delete;
	BreakableTwistedCorpse(BreakableTwistedCorpse&& _Other) noexcept = delete;
	BreakableTwistedCorpse& operator=(const BreakableTwistedCorpse& _Other) = delete;
	BreakableTwistedCorpse& operator=(BreakableTwistedCorpse&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	class GameEngineTextureRenderer* Renderer_;

};

