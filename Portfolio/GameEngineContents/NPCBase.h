#pragma once
#include "ObjectBase.h"

class NPCBase : public ObjectBase
{
public:
    NPCBase();
    ~NPCBase();

    NPCBase(const NPCBase& _Other)                = delete;
    NPCBase(NPCBase&& _Other) noexcept            = delete;
    NPCBase& operator=(const NPCBase& _Other)     = delete;
    NPCBase& operator=(NPCBase&& _Other) noexcept = delete;

    void SetIsSpeech(bool _Value) { IsSpeech_ = true; }
    bool GetIsSpeech() { return LineUI_->GetSpeechEnd(); }

protected:
    bool IsSpeech_;

    class LineUI* LineUI_;

    void Start() = 0;
    void Update(float _DeltaTime) override;
    void End() override;

private:
};
