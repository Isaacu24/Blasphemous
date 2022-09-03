#include "PreCompile.h"
#include "JumpCorpseEffecter.h"
#include "Corpse.h"

JumpCorpseEffecter::JumpCorpseEffecter() 
	: Random_{}
	, Index_(0)
	, CreatePos_(float4::ZERO)
	, IsEffect_(false)
	, DelayTime_(0.f)
{
}

JumpCorpseEffecter::~JumpCorpseEffecter() 
{
}

void JumpCorpseEffecter::Start()
{
}

void JumpCorpseEffecter::Update(float _DeltaTime)
{
	if (true == IsEffect_)
	{
		DelayTime_ += _DeltaTime;

		if (0.15f < DelayTime_)
		{
			++Index_;
			DelayTime_ -= 0.15f;

			float PosX = Random_.RandomFloat(-100.f, 100.f);

			Corpse* NewCorpse = GetLevel()->CreateActor<Corpse>();
			NewCorpse->SetCreatePos({ CreatePos_.x + PosX, CreatePos_.y });

			NewCorpse->GetTransform().SetWorldPosition({ CreatePos_.x + PosX, CreatePos_.y , static_cast<int>(ACTORORDER::Monster) });

			if (3 < Index_)
			{
				Index_ = 0;
				IsEffect_ = false;
			}
			
		}
	}
}

void JumpCorpseEffecter::End()
{
}
