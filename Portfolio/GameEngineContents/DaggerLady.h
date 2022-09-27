#pragma once
#include "NPCBase.h"

class DaggerLady : public NPCBase
{
public:
    DaggerLady();
    ~DaggerLady();

    DaggerLady(const DaggerLady& _Other)                = delete;
    DaggerLady(DaggerLady&& _Other) noexcept            = delete;
    DaggerLady& operator=(const DaggerLady& _Other)     = delete;
    DaggerLady& operator=(DaggerLady&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Update) override;
    void End() override;

private:
    class MetaTextureRenderer*      MetaRenderer_;
    class GameEngineTextureRenderer* Renderer_;
};
