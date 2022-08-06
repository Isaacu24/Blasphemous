#include "PreCompile.h"
#include "Penitent.h"


void Penitent::GroundCheck()
{
	float4 Color;

	if (true == IsLadder_)
	{
		Color = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 130));
	}

	else
	{
		Color = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 95));
	}

	if (true == Color.CompareInt4D(float4::BLACK)) //땅이라면 
	{
		IsJump_ = false;
		IsGround_ = true;

		UphillRoadCheck(); //오르막길 체크
	}

	else if (true == Color.CompareInt4D(float4::MAGENTA))
	{
		IsJump_ = false;
		IsGround_ = true;

		if (true == GameEngineInput::GetInst()->IsPressKey("PenitentDown"))
		{
			IsGround_ = false;
		}
	}

	else
	{
		IsGround_ = false;
	}
}

void Penitent::LadderCheck()
{
	float4 LowColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 200));
	float4 MiddleColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));

	if (true == LowColor.CompareInt4D(float4::GREEN))
	{
		if (GameEngineInput::GetInst()->IsDownKey("PenitentDown"))
		{
			State_.ChangeState("LadderClimb");
		}
	}

	if (true == MiddleColor.CompareInt4D(float4::GREEN))
	{
		State_.ChangeState("LadderClimb");
	}
}

void Penitent::UphillRoadCheck()
{
	while (true)
	{
		float4 Color = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 94));

		if (true == Color.CompareInt4D(float4::BLACK))
		{
			GetTransform().SetWorldMove(float4::UP);
			continue;
		}

		else
		{
			break;
		}
	}
}

bool Penitent::LeftObstacleCheck()
{
	float4 LeftColor;

	if (true == IsSlide_)
	{
		LeftColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x - 20, -(GetTransform().GetWorldPosition().y - 20));
	}

	else
	{
		LeftColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x - 20, -(GetTransform().GetWorldPosition().y - 10));
	}

	if (true == LeftColor.CompareInt4D(float4::BLACK))
	{
		return true;
	}

	return false;
}

bool Penitent::RightObstacleCheck()
{
	float4 RightColor;

	if (true == IsSlide_)
	{
		RightColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x + 20, -(GetTransform().GetWorldPosition().y - 20));
	}

	else
	{
		RightColor = ColMap_->GetCurTexture()->GetPixel(GetTransform().GetWorldPosition().x + 20, -(GetTransform().GetWorldPosition().y - 10));
	}

	if (true == RightColor.CompareInt4D(float4::BLACK))
	{
		return true;
	}

	return false;
}

void Penitent::CollisionCheck()
{
	Collider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Penitent::HitMonster, this, std::placeholders::_1, std::placeholders::_2)
	);

	Collider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Projectile, CollisionType::CT_OBB2D,
		std::bind(&Penitent::HitProjectile, this, std::placeholders::_1, std::placeholders::_2)
	);

	Collider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::BossMonster, CollisionType::CT_OBB2D,
		std::bind(&Penitent::HitMonster, this, std::placeholders::_1, std::placeholders::_2)
	);
}


void Penitent::HitStart(const StateInfo& _Info)
{
	State_.ChangeState("Idle");
}

void Penitent::HitUpdate(float _DeltaTime, const StateInfo& _Info)
{

}


//피격 함수
bool Penitent::HitMonster(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return false;
}

bool Penitent::HitProjectile(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	State_.ChangeState("Hit");
	return false;
}
