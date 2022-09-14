#pragma once


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
    BossMonsterBody,
    BossMonsterAttack,
    BossMonsterAttack1,
    Projectile,
    Gas,
    Object,
    LeftLedge,  //난간
    RightLedge,
    Debug,
    GlassSwitch,
    Platform,
    DeadZone,
    PlayerParry
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
