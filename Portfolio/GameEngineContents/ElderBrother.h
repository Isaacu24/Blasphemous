#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"
#include "AttackCorpseEffecter.h"
#include "JumpCorpseEffecter.h"
#include "GravityActor.h"

class GravityActor;
class JumpCorpseEffecter;
class AttackCorpseEffecter;
class ElderBrother : public GameEngineActor, public BossMonster
{
public:
	ElderBrother();
	~ElderBrother();

	ElderBrother(const ElderBrother& _Other) = delete;
	ElderBrother(ElderBrother&& _Other) noexcept = delete;
	ElderBrother& operator=(const ElderBrother& _Other) = delete;
	ElderBrother& operator=(ElderBrother&& _Other) noexcept = delete;

	void FreezeStart(const StateInfo& _Info);
	void FreezeUpdate(float _DeltaTime, const StateInfo& _Info);

	void AppearStart(const StateInfo& _Info);
	void AppearUpdate(float _DeltaTime, const StateInfo& _Info);

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackStart(const StateInfo& _Info);
	void AttackUpdate(float _DeltaTime, const StateInfo& _Info);
	void AttackEnd(const StateInfo& _Info);

	void DeathStart(const StateInfo& _Info);
	void DeathUpdate(float _DeltaTime, const StateInfo& _Info);

	bool DecideState(GameEngineCollision* _This, GameEngineCollision* _Other);

	bool AttackToPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);

	bool JumpToPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);

	inline void ChangeState(const std::string& _State)
	{
		State_.ChangeState(_State);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	float4 Dir_;

	AttackCorpseEffecter* AttackEffecter_;
	JumpCorpseEffecter* JumpEffecter_;

	GravityActor* AffectChecker;

	GameEngineCollision* JumpCollider_;

	float4 Target_;

	bool IsDecide_;

	float DecideTime_;
	float AppearTime_;

	float JumpForce_;

	float Alpha_;
	bool IsJump_;

	inline void ChangeIdle(const FrameAnimation_DESC& _Info)
	{
		State_.ChangeState("Idle");
	}

	inline void JumpFrame(const FrameAnimation_DESC& _Info, float _DeltaTime)
	{
		if (10 == _Info.CurFrame)
		{
			IsJump_ = true;
		}

		if (24 == _Info.CurFrame)
		{
			IsJump_ = false;
			JumpEffecter_->SetCreatePos(GetTransform().GetWorldPosition());
			JumpEffecter_->CreateEffect();
		}

		if (25 == _Info.CurFrame)
		{
			JumpCollider_->On();
			JumpCollider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D,
				std::bind(&ElderBrother::JumpToPlayer, this, std::placeholders::_1, std::placeholders::_2));
		}
	}

	inline void AttackFrame(const FrameAnimation_DESC& _Info)
	{
		if (16 == _Info.CurFrame)
		{
			AffectChecker->Move();
			AffectChecker->On();
		}

		if (17 < _Info.CurFrame)
		{
			if (nullptr == AffectChecker)
			{
				return;
			}

			if (Dir_.CompareInt4D(float4::LEFT))
			{
				AttackEffecter_->SetCreatePos(AffectChecker->GetTransform().GetWorldPosition() + float4{0, 60 });
				AttackEffecter_->CreateEffect();
			}

			else
			{
				AttackEffecter_->SetCreatePos(AffectChecker->GetTransform().GetWorldPosition() + float4{ 0, 60 });
				AttackEffecter_->CreateEffect();
			}

			AttackCollider_->On();
			AttackCollider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D,
				std::bind(&ElderBrother::AttackToPlayer, this, std::placeholders::_1, std::placeholders::_2));
		}
	}

};

