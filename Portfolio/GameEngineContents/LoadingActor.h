#pragma once
#include <GameEngineCore/GameEngineActor.h>

class LoadingActor : public GameEngineActor
{
public:
    LoadingActor();
    ~LoadingActor();

    LoadingActor(const LoadingActor& _Other)                = delete;
    LoadingActor(LoadingActor&& _Other) noexcept            = delete;
    LoadingActor& operator=(const LoadingActor& _Other)     = delete;
    LoadingActor& operator=(LoadingActor&& _Other) noexcept = delete;

    void Entrance(float _DeltaTime);
    void Exit(const std::string& _Level);

    void IsEntrance(bool _Value) { IsEntrance_ = _Value; }

    inline bool GetEntrance() { return IsEntrance_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    std::string NextLevel_;

    GameEngineUIRenderer* Background_;
    GameEngineUIRenderer* Icon_;

    float RendererTime_;
    float DeathTime_;

    float Alpha_;

    int CurrentFrame_;

    bool IsEntrance_;
    bool IsExit_;
};
