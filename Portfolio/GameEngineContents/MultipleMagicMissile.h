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

    void SetGround(GameEngineTextureRenderer* _Texture) { ColMap_ = _Texture; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    MetaTextureRenderer* MetaRenderer_;

    int  AnimationCount_;
    bool IsCreate_;

    GameEngineTextureRenderer* ColMap_;
};
