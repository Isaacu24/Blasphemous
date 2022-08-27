#pragma once
#include <GameEngineCore/GameEngineActor.h>

//보이지 않는 엑터
//픽셀 충돌과 중력이 적용된 위치를 받아오기 위한 존재
class GravityComponent;
class GameEngineTextureRenderer;
class GravityActor : public GameEngineActor
{
public:
	GravityActor();
	~GravityActor();

	GravityActor(const GravityActor& _Other) = delete;
	GravityActor(GravityActor&& _Other) noexcept = delete;
	GravityActor& operator=(const GravityActor& _Other) = delete;
	GravityActor& operator=(GravityActor&& _Other) noexcept = delete;

	inline void SetDirection(float4 _Dir)
	{
		Dir_ = _Dir;

		Dir_.NormalizeReturn();

		if (1 == Dir_.x)
		{
			Dir_ = GetTransform().GetRightVector();
		}

		else if (-1 == Dir_.x)
		{
			Dir_ = GetTransform().GetLeftVector();
		}
	}

	inline void Move()
	{
		IsMove_ = true;

		Alpha_ = 0.f;

		StartPos_ = GetTransform().GetWorldPosition();
		EndPos_ = StartPos_ + float4{ Dir_.x * 850.f, 0.f };
	}
	
	void GroundCheck();
	void UphillRoadCheck();

	inline void SetGround(GameEngineTextureRenderer* _ColMap)
	{
		ColMap_ = _ColMap;
	}

	inline void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GravityComponent* Gravity_;
	GameEngineTextureRenderer* Renderer_;

	GameEngineTextureRenderer* ColMap_;

	float4 Dir_;

	bool IsMove_;
	bool IsGround_;

	float Speed_;

	float Alpha_;

	float4 StartPos_;
	float4 EndPos_;
};

