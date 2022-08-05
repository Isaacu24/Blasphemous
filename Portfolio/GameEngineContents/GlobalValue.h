#pragma once

enum class ACTORORDER
{
	AfterParallax5 = -50, //∞°¿Â æ’
	AfterParallax4,
	AfterParallax3,
	AfterParallax2,
	AfterParallax1,
	AfterParallax0,

	AfterLayer5 = 0,
	AfterLayer4,
	AfterLayer3,
	AfterLayer2,
	AfterLayer1,
	AfterLayer0,

	Door,

	Temp,

	Player,
	NPC,
	BossMonster,
	Monster,
	Object,

	Tile,

	BeforeLayer5,
	BeforeLayer4,
	BeforeLayer3,
	BeforeLayer2,
	BeforeLayer1,
	BeforeLayer0,

	BeforeParallax5 = 100,
	BeforeParallax4 = 150,
	BeforeParallax3 = 200,
	BeforeParallax2 = 250,
	BeforeParallax1 = 300,
	BeforeParallax0 = 350,

	ColMap = 500
};

enum class COLLISIONORDER
{
	Player,
	Monster,
	BossMonster,
	Projectile,
	Object
};