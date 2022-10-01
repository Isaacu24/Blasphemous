#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Milestone : public GameEngineActor
{
public:
    Milestone();
    ~Milestone();

    Milestone(const Milestone& _Other)                = delete;
    Milestone(Milestone&& _Other) noexcept            = delete;
    Milestone& operator=(const Milestone& _Other)     = delete;
    Milestone& operator=(Milestone&& _Other) noexcept = delete;

    inline void SetTownName(const std::string& _Name) { Font_->SetText(_Name, "NeoµÕ±Ù¸ð"); }

    void SetFontPosition(float4 _Value) { Font_->SetScreenPostion(_Value); }

    void SetFontSize(float _Value) { Font_->SetSize(_Value); }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
    class GameEngineUIRenderer*   UIRenderer_;
    class GameEngineFontRenderer* Font_;

    float ShowTime_;

    float Alpha_;

    bool IsInvisible_;

    GameEngineSoundPlayer SoundPlayer_;
};
