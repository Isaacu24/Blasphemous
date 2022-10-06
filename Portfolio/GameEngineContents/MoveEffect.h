#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MetaTextureRenderer;
class MoveEffect : public GameEngineActor 
{
    friend class Penitent;

public:
	MoveEffect();
	~MoveEffect();

	MoveEffect(const MoveEffect& _Other) = delete;
	MoveEffect(MoveEffect&& _Other) noexcept = delete;
	MoveEffect& operator=(const MoveEffect& _Other) = delete;
	MoveEffect& operator=(MoveEffect&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    MetaTextureRenderer* Renderer_;
    GameEngineSoundPlayer SoundPlayer_;
};

