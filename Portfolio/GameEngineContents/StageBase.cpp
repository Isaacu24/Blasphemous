#include "PreCompile.h"
#include "StageBase.h"

StageBase::StageBase() 
	: Stage_(nullptr)
	, ColMap_(nullptr)
	, Penitent_(nullptr)
	, BossMonster_(nullptr)
	, MonsterList_{}
	, IsLeftExit_(false)
	, IsRightExit_(false)
{
}

StageBase::~StageBase() 
{
}

void StageBase::MoveParallax(float4 _Dir, float _DeltaTime)
{
	_Dir.Normalize();
	_Dir = -_Dir;

	for (size_t i = 0; i < Parallaxs_.size(); i++)
	{
		ACTORORDER Order = static_cast<ACTORORDER>(Parallaxs_[i]->GetTransform().GetWorldPosition().z);

		switch (Order)
		{
		case ACTORORDER::AfterParallax3:
			Parallaxs_[i]->GetTransform().SetWorldMove(_Dir * 25 * _DeltaTime);
			break;
		case ACTORORDER::AfterParallax2:
			Parallaxs_[i]->GetTransform().SetWorldMove(_Dir * 20 * _DeltaTime);
			break;
		case ACTORORDER::AfterParallax1:
			Parallaxs_[i]->GetTransform().SetWorldMove(_Dir * 15 * _DeltaTime);
			break;
		case ACTORORDER::AfterParallax0:
			Parallaxs_[i]->GetTransform().SetWorldMove(_Dir * 5 * _DeltaTime);
			break;
		case ACTORORDER::BeforeParallax5:
			Parallaxs_[i]->GetTransform().SetWorldMove(_Dir * 35 * _DeltaTime);
			break;
		case ACTORORDER::BeforeParallax4:
			Parallaxs_[i]->GetTransform().SetWorldMove(_Dir * 30 * _DeltaTime);
			break;
		case ACTORORDER::BeforeParallax3:
			Parallaxs_[i]->GetTransform().SetWorldMove(_Dir * 25 * _DeltaTime);
			break;
		case ACTORORDER::BeforeParallax2:
			Parallaxs_[i]->GetTransform().SetWorldMove(_Dir * 20 * _DeltaTime);
			break;
		case ACTORORDER::BeforeParallax1:
			Parallaxs_[i]->GetTransform().SetWorldMove(_Dir * 15 * _DeltaTime);
			break;
		case ACTORORDER::BeforeParallax0:
			Parallaxs_[i]->GetTransform().SetWorldMove(_Dir * 5 * _DeltaTime);
			break;
		}
	}
}

