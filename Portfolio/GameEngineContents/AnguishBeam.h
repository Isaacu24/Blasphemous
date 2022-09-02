#pragma once
#include <GameEngineCore/GameEngineActor.h>

class AnguishBeam : public GameEngineActor
{
    friend class AnguishBeamSpawner;

public:
	AnguishBeam();
	~AnguishBeam();

	AnguishBeam(const AnguishBeam& _Other) = delete;
	AnguishBeam(AnguishBeam&& _Other) noexcept = delete;
	AnguishBeam& operator=(const AnguishBeam& _Other) = delete;
	AnguishBeam& operator=(AnguishBeam&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class MetaTextureRenderer* MetaRenderer_;

};

