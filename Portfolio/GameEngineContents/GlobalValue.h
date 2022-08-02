#pragma once

enum class ACTORORDER
{
	AfterParallax5 = 0,
	AfterParallax4,
	AfterParallax3,
	AfterParallax2,
	AfterParallax1,
	AfterParallax0,

	Door,

	Temp,

	Player,
	NPC,
	AtherMonster,
	Monster,
	Object,

	Tile,

	BeforeParallax5,
	BeforeParallax4,
	BeforeParallax3,
	BeforeParallax2,
	BeforeParallax1,
	BeforeParallax0,

	ColMap,
};

enum class COLLISIONORDER
{
	Player,
	Monster,
	BossMonster,
	Projectile,
	Object
};