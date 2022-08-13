#include "PreCompile.h"
#include "MagicMissileSpawner.h"
#include "MagicMissile.h"

MagicMissileSpawner::MagicMissileSpawner() 
	: MissileCount_(1)
{}

MagicMissileSpawner::~MagicMissileSpawner() {}

void MagicMissileSpawner::Start() {}

void MagicMissileSpawner::Update(float _DeltaTime) 
{
	DelayTime_ += _DeltaTime; 

	if (0.5f >= DelayTime_)
    {
        return;
	}

    if (8 == MissileCount_)
    {
        Off();
        MissileCount_ = 0;
        return;
    }

	if (0 == MissileCount_ % 2) //Â¦¼ö(À§)
    {
        MagicMissile* Missile = GetLevel()->CreateActor<MagicMissile>();
        Missile->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
        Missile->SetDirection(Dir_);

        DelayTime_ = 0.f;
        ++MissileCount_;
	}

	else //È¦¼ö(¾Æ·¡)
	{
        MagicMissile* Missile = GetLevel()->CreateActor<MagicMissile>();
        Missile->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
        Missile->SetDirection(Dir_);

        DelayTime_ = 0.f;
        ++MissileCount_;
	}
}

void MagicMissileSpawner::End() {}
