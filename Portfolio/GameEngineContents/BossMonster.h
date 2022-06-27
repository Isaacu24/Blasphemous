#pragma once
#include "MonsterBase.h"

class BossMonster : public MonsterBase
{
public:
	BossMonster();
	~BossMonster();

	BossMonster(const BossMonster& _Other) = delete;
	BossMonster(BossMonster&& _Other) noexcept = delete;
	BossMonster& operator=(const BossMonster& _Other) = delete;
	BossMonster& operator=(BossMonster&& _Other) noexcept = delete;

protected:

private:

};

