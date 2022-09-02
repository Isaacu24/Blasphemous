#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "SpawnerBase.h"

class ToxicCloudSpawner 
    : public GameEngineActor
    , public SpawnerBase 
{
public:
	ToxicCloudSpawner();
	~ToxicCloudSpawner();

	ToxicCloudSpawner(const ToxicCloudSpawner& _Other) = delete;
	ToxicCloudSpawner(ToxicCloudSpawner&& _Other) noexcept = delete;
	ToxicCloudSpawner& operator=(const ToxicCloudSpawner& _Other) = delete;
	ToxicCloudSpawner& operator=(ToxicCloudSpawner&& _Other) noexcept = delete;

    void SetGround(GameEngineTextureRenderer* _Ground) { ColMap_ = _Ground; }

    void SetDirection(float4 _Dir)
    {
        Dir_ = _Dir;
        Dir_.Normalize();
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* ColMap_;

    GameEngineRandom Random_;

    float4 Dir_;

    float DelayTime_;

    int CloudCount_;
};

