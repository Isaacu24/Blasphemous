#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PenitentGuilt : public GameEngineActor
{
public:
    PenitentGuilt();
    ~PenitentGuilt();

	PenitentGuilt(const PenitentGuilt& _Other)                  = delete;
    PenitentGuilt(PenitentGuilt&& _Other) noexcept              = delete;
    PenitentGuilt&  operator=(const PenitentGuilt& _Other)      = delete;
    PenitentGuilt& operator=(PenitentGuilt&& _Other) noexcept   = delete;

    void Expiation();

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* Renderer_;

};

