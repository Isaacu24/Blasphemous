#pragma once
#include "NPCBase.h"

class Deogracias : public NPCBase
{
public:
    Deogracias();
    ~Deogracias();

    Deogracias(const Deogracias& _Other)                = delete;
    Deogracias(Deogracias&& _Other) noexcept            = delete;
    Deogracias& operator=(const Deogracias& _Other)     = delete;
    Deogracias& operator=(Deogracias&& _Other) noexcept = delete;

    void SetIsSpeech(bool _Value) { IsSpeech_ = true; }

    void ChangeFrontAnimation();

    bool GetIsSpeech() { return MessageUI_->GetSpeechEnd(); }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* Renderer_;

    class MessageUI* MessageUI_;

    bool IsSpeech_;
};
