#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class FireBallSpawner : public GameEngineActor
{
public:
    FireBallSpawner();
    ~FireBallSpawner();

    FireBallSpawner(const FireBallSpawner& _Other)                = delete;
    FireBallSpawner(FireBallSpawner&& _Other) noexcept            = delete;
    FireBallSpawner& operator=(const FireBallSpawner& _Other)     = delete;
    FireBallSpawner& operator=(FireBallSpawner&& _Other) noexcept = delete;

    void SetGround(GameEngineTextureRenderer* _Ground) { ColMap_ = _Ground; }

    void CreateFireBall(const FrameAnimation_DESC& _Info);

    void SetDirection(float4 _Dir) 
    { 
        Dir_ = _Dir; 
        Dir_.Normalize();
        Dir_ = float4{Dir_.x, -1, 0};
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* Renderer_;

    GameEngineTextureRenderer* ColMap_;

    int BallCount_;

    float4 Dir_;
};
