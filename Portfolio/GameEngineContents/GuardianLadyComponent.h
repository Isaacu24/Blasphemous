#pragma once
#include <GameEngineCore/GameEngineTransformComponent.h>

class GuardianLadyComponent : public GameEngineTransformComponent
{
    friend class Penitent;

public:
    GuardianLadyComponent();
    ~GuardianLadyComponent();

    GuardianLadyComponent(const GuardianLadyComponent& _Other)                = delete;
    GuardianLadyComponent(GuardianLadyComponent&& _Other) noexcept            = delete;
    GuardianLadyComponent& operator=(const GuardianLadyComponent& _Other)     = delete;
    GuardianLadyComponent& operator=(GuardianLadyComponent&& _Other) noexcept = delete;

    MetaTextureRenderer* GetMetaTextureRenderer() { return MetaRenderer_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class MetaTextureRenderer* MetaRenderer_;
    class GameEngineCollision* ProtectCollider_;

    bool IsProtected_;

    float CoolTime_;
};
