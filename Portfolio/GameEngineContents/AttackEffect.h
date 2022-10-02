#pragma once
#include <GameEngineCore/GameEngineActor.h>

//공격 및 패링 이펙트
class MetaTextureRenderer;
class AttackEffect : public GameEngineActor
{
    friend class Penitent;

public:
	AttackEffect();
	~AttackEffect();

	AttackEffect(const AttackEffect& _Other) = delete;
	AttackEffect(AttackEffect&& _Other) noexcept = delete;
	AttackEffect& operator=(const AttackEffect& _Other) = delete;
	AttackEffect& operator=(AttackEffect&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    MetaTextureRenderer* Renderer_;

	GameEngineSoundPlayer SoundPlayer_;

	bool IsGettingSoul_;
};

