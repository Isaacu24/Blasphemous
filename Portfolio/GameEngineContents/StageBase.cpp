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
	, CameraZPos_(-1400.f)
	, IsChangeCameraPos_(false)
	, CameraOffset_(200.f)
    , IsEvent_(false)
{
}

StageBase::~StageBase() 
{
}
