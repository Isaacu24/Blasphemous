#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

class CherubPopUp : public GameEngineActor
{
public:
    CherubPopUp();
    ~CherubPopUp();

    CherubPopUp(const CherubPopUp& _Other)                = delete;
    CherubPopUp(CherubPopUp&& _Other) noexcept            = delete;
    CherubPopUp& operator=(const CherubPopUp& _Other)     = delete;
    CherubPopUp& operator=(CherubPopUp&& _Other) noexcept = delete;

    void SetCountFont(int _Count) { CountFont_->SetText(std::to_string(_Count), "NeoµÕ±Ù¸ð"); }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void LevelEndEvent() override;

private:
    class GameEngineUIRenderer*   PopUp_;
    class GameEngineFontRenderer* MaxFont_;
    GameEngineFontRenderer*       CountFont_;

    bool IsOn_;
    bool IsOff_;

    float ShowTime_;

    float Alpha_;
};