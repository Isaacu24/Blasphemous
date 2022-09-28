#pragma once
#include "ObjectBase.h"

// ���̺� ����Ʈ
class PrieDieu : public ObjectBase
{
public:
    PrieDieu();
    ~PrieDieu();

    PrieDieu(const PrieDieu& _Other)                = delete;
    PrieDieu(PrieDieu&& _Other) noexcept            = delete;
    PrieDieu& operator=(const PrieDieu& _Other)     = delete;
    PrieDieu& operator=(PrieDieu&& _Other) noexcept = delete;

    MetaTextureRenderer* GetMetaRenderer() { return MetaRenderer_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    class MetaTextureRenderer* MetaRenderer_;

private:
};
