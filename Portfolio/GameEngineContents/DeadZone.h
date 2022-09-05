#pragma once
#include <GameEngineCore/GameEngineActor.h>

class DeadZone : public GameEngineActor
{
public:
	DeadZone();
	~DeadZone();

	DeadZone(const DeadZone& _Other) = delete;
	DeadZone(DeadZone&& _Other) noexcept = delete;
	DeadZone& operator=(const DeadZone& _Other) = delete;
	DeadZone& operator=(DeadZone&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineCollision* Collider_;

};

