#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "SpawnerBase.h"
 
class MagicMissileSpawner 
    : public GameEngineActor
    , public SpawnerBase
{
public:
    MagicMissileSpawner();
    ~MagicMissileSpawner();

    MagicMissileSpawner(const MagicMissileSpawner& _Other)                = delete;
    MagicMissileSpawner(MagicMissileSpawner&& _Other) noexcept            = delete;
    MagicMissileSpawner& operator=(const MagicMissileSpawner& _Other)     = delete;
    MagicMissileSpawner& operator=(MagicMissileSpawner&& _Other) noexcept = delete;

    void SetDirection(float4 _Dir) { Dir_ = _Dir; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    float DelayTime_;
    
    //¦����� ��, Ȧ����� �Ʒ�
    int MissileCount_;

    float4 Dir_;
};
