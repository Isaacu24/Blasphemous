#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

class MonsterHitEffect : public GameEngineActor
{
public:
    MonsterHitEffect();
    ~MonsterHitEffect();

    MonsterHitEffect(const MonsterHitEffect& _Other)                = delete;
    MonsterHitEffect(MonsterHitEffect&& _Other) noexcept            = delete;
    MonsterHitEffect& operator=(const MonsterHitEffect& _Other)     = delete;
    MonsterHitEffect& operator=(MonsterHitEffect&& _Other) noexcept = delete;

    void ShowHitEffet();

    void ShowRangeHitEffect();

    void SetCount(int _Index)
    {
        HitCount_ = _Index;

        if (2 < HitCount_)
        {
            HitCount_ = 2;
        }
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    int HitCount_;

    float ResetTime_;

    class MetaTextureRenderer* Effect_;
    MetaTextureRenderer* RangeEffect_;

    GameEngineSoundPlayer SoundPlayer_;
};
