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
    
    void AddSound(const std::string& _Sound);

    void ResetLine() { Script_.clear(); }

    void SpeechStart()
    {
        IsSpeech_    = true;
        IsSpeechEnd_ = false;
    }

    bool GetSpeechEnd() { return IsSpeechEnd_; }

    void SetFontPosition(float4 _Value) { Font_->SetScreenPostion(_Value); }

    void SetFontColor(float4 _Value) { Font_->SetColor({_Value.x, _Value.y, _Value.z, Alpha_}); }

    void SetFontSize(float _Value) { Font_->SetSize(_Value); }

    void SetMassageStartEvent(int Index, std::function<void()> _Fuction)
    {
        StartEventIndex_ = Index;
        StartEvent_      = _Fuction;
    }

    void SetMassageEndEvent(int Index, std::function<void()> _Fuction)
    {
        EndEventIndex_ = Index;
        EndEvent_      = _Fuction;
    }

    void SetSpeed(float _Speed) { Speed_ = _Speed; }

    void SetBackgroudAlpha(float _Alpha) { BackgroundAlpha_ = _Alpha; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void LevelEndEvent() override;

    void OnEvent() override;
    void OffEvent() override;

private:
    class GameEngineUIRenderer*   Renderer_;
    class GameEngineFontRenderer* Font_;

    GameEngineSoundPlayer SoundPlayer_;

    std::vector<std::string> Script_;
    std::vector<std::string> SoundList_;

    //텍스트가 처음 출력되기 이전에 실행
    std::function<void()> StartEvent_;

    //텍스트가 전부 출력된 후 실행
    std::function<void()> EndEvent_;

    int StartEventIndex_;
    int EndEventIndex_;

    bool IsSpeech_;
    bool IsSpeechEnd_;

    float BreathTime_;

    int LineIndex_;

    float ConstTime_;

    float Alpha_;

    //클수록 빨리 바뀜
    float Speed_;

    bool IsOn_;
    bool IsOff_;

    bool IsSoundPlay_;

    float BackgroundAlpha_;
};
