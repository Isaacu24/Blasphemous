#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Cemetry : public GameEngineActor
{
public:
	Cemetry();
	~Cemetry();

	Cemetry(const Cemetry& _Other) = delete;
	Cemetry(Cemetry&& _Other) noexcept = delete;
	Cemetry& operator=(const Cemetry& _Other) = delete;
	Cemetry& operator=(Cemetry&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class MetaTextureRenderer* MetaRenderer_;
};

