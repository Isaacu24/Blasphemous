#pragma once
#include "ObjectBase.h"

class PenitentGuilt : public ObjectBase
{
    friend class Penitent;

public:
    PenitentGuilt();
    ~PenitentGuilt();

    PenitentGuilt(const PenitentGuilt& _Other)                = delete;
    PenitentGuilt(PenitentGuilt&& _Other) noexcept            = delete;
    PenitentGuilt& operator=(const PenitentGuilt& _Other)     = delete;
    PenitentGuilt& operator=(PenitentGuilt&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* Renderer_;

    void DestroyGuilt();
};
