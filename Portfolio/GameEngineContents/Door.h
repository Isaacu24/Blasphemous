#pragma once
#include "ObjectBase.h"

class Door : public ObjectBase
{
public:
    Door();
    ~Door();

    Door(const Door& _Other)                = delete;
    Door(Door&& _Other) noexcept            = delete;
    Door& operator=(const Door& _Other)     = delete;
    Door& operator=(Door&& _Other) noexcept = delete;

    void Open();

    inline void SetLinkLevel(const std::string& _Level) { LinkLevel_ = _Level; }

    inline std::string& GetLinkLevel() { return LinkLevel_; }

    inline GameEngineTextureRenderer* GetDoorRenderer() { return Renderer_; }

    void SetMoveUIRenderer(const float4& _Value) 
    { 
        UIRenderer_->GetTransform().SetWorldMove(_Value);
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class GameEngineTextureRenderer* Renderer_;

    std::string LinkLevel_;
};
