#pragma once
#include <GameEngineCore/GameEngineTransformComponent.h>

class GravityComponent : public GameEngineTransformComponent
{
public:
	GravityComponent();
	~GravityComponent();

	GravityComponent(const GravityComponent& _Other) = delete;
	GravityComponent(GravityComponent&& _Other) noexcept = delete;
	GravityComponent& operator=(const GravityComponent& _Other) = delete;
	GravityComponent& operator=(GravityComponent&& _Other) noexcept = delete;

	void SetActive(bool _Active)
	{
		Active_ = _Active;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	bool Active_;
};

