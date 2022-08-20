#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class MetaSpriteWindow;
class MetaLevel : public GameEngineLevel
{
public:
    MetaLevel();
    ~MetaLevel();

    MetaLevel(const MetaLevel& _Other)                = delete;
    MetaLevel(MetaLevel&& _Other) noexcept            = delete;
    MetaLevel& operator=(const MetaLevel& _Other)     = delete;
    MetaLevel& operator=(MetaLevel&& _Other) noexcept = delete;

    MetaSpriteWindow* MetaAnimationGUI_;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

	void LevelStartEvent() override;
    void LevelEndEvent() override;

private:
};
