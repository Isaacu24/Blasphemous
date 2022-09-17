#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MessageUI : public GameEngineActor
{
public:
    MessageUI();
    ~MessageUI();

    MessageUI(const MessageUI& _Other)                = delete;
    MessageUI(MessageUI&& _Other) noexcept            = delete;
    MessageUI& operator=(const MessageUI& _Other)     = delete;
    MessageUI& operator=(MessageUI&& _Other) noexcept = delete;

    GameEngineUIRenderer* GetUIRenderer() { return Renderer_; }

    void CreateLine(const std::string& _Line);

    void ResetLine() { Script_.clear(); }

    void SpeechStart()
    {
        IsSpeech_    = true;
        IsSpeechEnd_ = false;
    }

    void SetFontPosition(float4 _Value) { Font_->SetScreenPostion(_Value); }

    void SetFontSize(float _Value) { Font_->SetSize(_Value); }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void LevelEndEvent() override;

private:
    class GameEngineUIRenderer*   Renderer_;
    class GameEngineFontRenderer* Font_;

    std::vector<std::string> Script_;

    bool IsSpeech_;
    bool IsSpeechEnd_;

    float BreathTime_;

    int LineIndex_;

    float ConstTime_;

    float Alpha_;
};
