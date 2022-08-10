#pragma once
#include <GameEngineCore/GameEngineActor.h>

class StageActor : public GameEngineActor
{
public:
    StageActor();
    ~StageActor();

    StageActor(const StageActor& _Other)                = delete;
    StageActor(StageActor&& _Other) noexcept            = delete;
    StageActor& operator=(const StageActor& _Other)     = delete;
    StageActor& operator=(StageActor&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
};
