#pragma once

//½ºÆ÷³Ê
enum class SPAWNERTYPE
{
    SP_LOWLEVLE,
    SP_HIGHLEVLE
};

class GameEngineActor;
class SpawnerBase
{
public:
    SpawnerBase();
    ~SpawnerBase();

    SpawnerBase(const SpawnerBase& _Other)                = delete;
    SpawnerBase(SpawnerBase&& _Other) noexcept            = delete;
    SpawnerBase& operator=(const SpawnerBase& _Other)     = delete;
    SpawnerBase& operator=(SpawnerBase&& _Other) noexcept = delete;

    inline bool GetSpawnerEnd() { return SpawnerEnd_; }

    inline void SetSpawnerEnd(bool _Value) { SpawnerEnd_ = _Value; }

    inline void SetSpawnerType(SPAWNERTYPE _Type) { SpawnerType_ = _Type; }

    void SetTarget(GameEngineActor* _Target) { Target_ = _Target; }

protected:
    SPAWNERTYPE SpawnerType_;

    GameEngineActor* Target_;

    bool SpawnerEnd_;

    bool IsStop_;

private:
};
