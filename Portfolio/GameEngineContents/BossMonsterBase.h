#pragma once
#include "MonsterBase.h"

class BossMonsterBase : public MonsterBase
{
public:
	BossMonsterBase();
	~BossMonsterBase();

	BossMonsterBase(const BossMonsterBase& _Other) = delete;
	BossMonsterBase(BossMonsterBase&& _Other) noexcept = delete;
	BossMonsterBase& operator=(const BossMonsterBase& _Other) = delete;
	BossMonsterBase& operator=(BossMonsterBase&& _Other) noexcept = delete;

protected:

private:

};

