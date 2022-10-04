#pragma once
#include <GameEngineCore/GameEngineActor.h>

class CutScenePlayer : public GameEngineActor
{
public:
    CutScenePlayer();
    ~CutScenePlayer();

    CutScenePlayer(const CutScenePlayer& _Other)                = delete;
    CutScenePlayer(CutScenePlayer&& _Other) noexcept            = delete;
    CutScenePlayer& operator=(const CutScenePlayer& _Other)     = delete;
    CutScenePlayer& operator=(CutScenePlayer&& _Other) noexcept = delete;

    void CutScenePlay() { IsPlay_ = true; }

    void SetCutScene(std::string _Name, int MaxFrame)
    {
        for (size_t i = 0; i < MaxFrame; i++)
        {
            SceneFrameList_.push_back(_Name + std::to_string(i));
        }

        MaxFrame_ = MaxFrame;
    }

    bool GetIsPlay() { return IsPlay_; }

    void SetCutScenePlayEnd(std::function<void()> _Func) { EndFunc_ = _Func; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class GameEngineUIRenderer* CutRenderer_;

    std::vector<std::string> SceneFrameList_;

    std::function<void()> EndFunc_;

    float PlayTime_;
    float Speed_;

    int CurrentFrame_;
    int MaxFrame_;

    bool IsPlay_;
};
