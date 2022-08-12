#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GlobalValue.h"

class SymbolEffect : public GameEngineActor
{
    friend class Pope;
    friend class Pontiff;

public:
	SymbolEffect();
	~SymbolEffect();

	SymbolEffect(const SymbolEffect& _Other) = delete;
	SymbolEffect(SymbolEffect&& _Other) noexcept = delete;
	SymbolEffect& operator=(const SymbolEffect& _Other) = delete;
	SymbolEffect& operator=(SymbolEffect&& _Other) noexcept = delete;

	void SetColor(COLORTYPE _Type);

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class GameEngineTextureRenderer* Renderer_;
};

