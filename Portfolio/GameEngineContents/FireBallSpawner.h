#pragma once
#include <GameEngineCore/GameEngineActor.h>

class FireBallSpawner : public GameEngineActor
{
public:
	FireBallSpawner();
	~FireBallSpawner();

	FireBallSpawner(const FireBallSpawner& _Other) = delete;
	FireBallSpawner(FireBallSpawner&& _Other) noexcept = delete;
	FireBallSpawner& operator=(const FireBallSpawner& _Other) = delete;
	FireBallSpawner& operator=(FireBallSpawner&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:

};

