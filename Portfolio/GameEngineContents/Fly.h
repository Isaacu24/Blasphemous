#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Fly : public GameEngineActor
{
public:
    Fly();
    ~Fly();

    Fly(const Fly& _Other)                = delete;
    Fly(Fly&& _Other) noexcept            = delete;
    Fly& operator=(const Fly& _Other)     = delete;
    Fly& operator=(Fly&& _Other) noexcept = delete;

    inline MetaTextureRenderer* GetMetaRenderer() { return MetaRenderer_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    MetaTextureRenderer* MetaRenderer_;
};
