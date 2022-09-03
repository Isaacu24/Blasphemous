#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MagicMissile;
class MultipleMagicMissile : public GameEngineActor
{
public:
    MultipleMagicMissile();
    ~MultipleMagicMissile();

    MultipleMagicMissile(const MultipleMagicMissile& _Other)                = delete;
    MultipleMagicMissile(MultipleMagicMissile&& _Other) noexcept            = delete;
    MultipleMagicMissile& operator=(const MultipleMagicMissile& _Other)     = delete;
    MultipleMagicMissile& operator=(MultipleMagicMissile&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    MetaTextureRenderer* MetaRenderer_;

    int  AnimationCount_;
    bool IsCreate_;
};
