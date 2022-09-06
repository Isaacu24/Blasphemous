#pragma once

#define AO_AFTERPARALLAX5     -50;
#define AO_AFTERPARALLAX4     -49;
#define AO_AFTERPARALLAX3     -48;
#define AO_AFTERPARALLAX2     -47;
#define AO_AFTERPARALLAX1     -46;
#define AO_AFTERPARALLAX0     -45;

#define AO_AfterLayer5        -30;
#define AO_AfterLayer4        -29;
#define AO_AfterLayer3        -28;
#define AO_AfterLayer2        -27;
#define AO_AfterLayer1        -26;
#define AO_AfterLayer0        -25;

#define AO_DOOR               0;

#define AO_PLAYEREFFECT       0.1f;
#define AO_PLAYER             0.2f;
#define AO_PLAYERBEHINDEFFECT 0.3f;
#define AO_NPC                0.4f;
#define AO_PLATFORM           0.5f;
#define AO_BOSSMONSTEREFFECT  0.6f;
#define AO_BOSSMONSTER        0.7f;
#define AO_MONSTER            0.8f;
#define AO_OBJECT             0.9f;
#define AO_TILE               1.0;

#define AO_BEFORELAYER5       2;
#define AO_BEFORELAYER4       3;
#define AO_BEFORELAYER3       4;
#define AO_BEFORELAYER2       5;
#define AO_BEFORELAYER1       6;
#define AO_BEFORELAYER0       7;

#define AO_BEFOREPARALLAX5    100;
#define AO_BEFOREPARALLAX4    200;
#define AO_BEFOREPARALLAX3    300;
#define AO_BEFOREPARALLAX2    400;
#define AO_BEFOREPARALLAX1    500;
#define AO_BEFOREPARALLAX0    600;

#define AO_COLMAP             601;


enum class ACTORORDER
{
    AfterParallax5 = -50,  //가장 앞
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

    PlayerEffect,
    Player,
    BehindEffect,

    NPC,

    Platform,

    Temp2,

    Temp3,

    BossMonsterEffect,
    BossMonster,
    MonsterEffect,
    Monster,

    Object,
    Object1,
    Object2,
    Object3,

    Tile,

    BeforeLayer5,
    BeforeLayer4,
    BeforeLayer3,
    BeforeLayer2,
    BeforeLayer1,
    BeforeLayer0,

    BeforeParallax5 = 100,
    BeforeParallax4 = 200,
    BeforeParallax3 = 300,
    BeforeParallax2 = 400,
    BeforeParallax1 = 500,
    BeforeParallax0 = 600,

    ColMap
};

enum class COLLISIONORDER
{
    Player,
    PlayerFoot,
    PlayerAttack,
    PlayerSkill,
    PlayerSkill1,
    PlayerSkill2,
    MonsterDetect,  //몬스터 감지 영역
    Monster,
    MonsterAttack,
    MonsterAttack1,
    MonsterShield,
    BossMonster,
    BossMonsterAttack,
    BossMonsterAttack1,
    Projectile,
    Object,
    LeftLedge,  //난간
    RightLedge,
    Debug,
    GlassSwitch,
    Platform,
    DeadZone
};


enum class UIORDER
{
    LodingUI = 0,
    Inventory,
    ScreenUI,
    BackScreenUI,
    InteractionUI,
    BossUI,
    MonterUI,
    NumberUI,
    PlayerUIFrame,
    PlayerUI,
};


enum class COLORTYPE
{
    RED,
    BLUE,
    GREEN,
    PURPLE
};
