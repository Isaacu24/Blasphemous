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

