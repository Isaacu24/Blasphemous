#include "PreCompile.h"
#include "StageBase.h"

StageBase::StageBase()
    : Stage_(nullptr)
    , ColMap_(nullptr)
    , DangleColiders_{}
    , Penitent_(nullptr)
    , BossMonster_(nullptr)
    , MonsterList_{}
    , IsLeftExit_(false)
    , IsRightExit_(false)
    , CameraZPos_(-1400.f)
    , IsChangeCameraPos_(false)
    , CameraOffset_(200.f)
{
    AfterParallaxZ = AO_AFTERPARALLAX0;
    AfterParallax1Z = AO_AFTERPARALLAX1;
    AfterParallax2Z = AO_AFTERPARALLAX2;
    AfterParallax3Z = AO_AFTERPARALLAX3;
    AfterParallax4Z = AO_AFTERPARALLAX4;
    AfterParallax5Z = AO_AFTERPARALLAX5;

    AfterLayerZ = AO_AfterLayer0;
    AfterLayer1Z= AO_AfterLayer1;
    AfterLayer2Z= AO_AfterLayer2;
    AfterLayer3Z= AO_AfterLayer3;
    AfterLayer4Z= AO_AfterLayer4;
    AfterLayer5Z= AO_AfterLayer5;

    DoorZ = AO_DOOR;

    PlayerEffectZ = AO_PLAYEREFFECT;
    PlayerZ = AO_PLAYER;
    PlayerBehindEffectZ = AO_PLAYERBEHINDEFFECT;
    NPCZ = AO_NPC;
    PlatformZ = AO_PLATFORM;
    BossMonsterEffectZ = AO_BOSSMONSTEREFFECT;
    BossMonsterZ        = AO_BOSSMONSTER;
    MonsterZ = AO_MONSTER;
    ObjectZ = AO_OBJECT;

    TileZ = AO_TILE;

    BeforeLayerZ  = AO_BEFORELAYER0;
    BeforeLayer1Z = AO_BEFORELAYER1;
    BeforeLayer2Z = AO_BEFORELAYER2;
    BeforeLayer3Z = AO_BEFORELAYER3;
    BeforeLayer4Z = AO_BEFORELAYER4;
    BeforeLayer5Z = AO_BEFORELAYER5;

    BeforeParallaxZ  = AO_BEFOREPARALLAX0;
    BeforeParallax1Z = AO_BEFOREPARALLAX1;
    BeforeParallax2Z = AO_BEFOREPARALLAX2;
    BeforeParallax3Z = AO_BEFOREPARALLAX3;
    BeforeParallax4Z = AO_BEFOREPARALLAX4;
    BeforeParallax5Z = AO_BEFOREPARALLAX5;

    ColmapZ         = AO_COLMAP;
}

//#define AO_DOOR               0;
//
//#define AO_PLAYEREFFECT       0.1f;
//#define AO_PLAYER             0.2f;
//#define AO_PLAYERBEHINDEFFECT 0.3f;
//#define AO_NPC                0.4f;
//#define AO_PLATFORM           0.5f;
//#define AO_BOSSMONSTEREFFECT  0.6f;
//#define AO_BOSSMONSTER        0.7f;
//#define AO_MONSTER            0.8f;
//#define AO_OBJECT             0.9f;
//#define AO_TILE               1.0;
//
//#define AO_BEFORELAYER5       2;
//#define AO_BEFORELAYER4       3;
//#define AO_BEFORELAYER3       4;
//#define AO_BEFORELAYER2       5;
//#define AO_BEFORELAYER1       6;
//#define AO_BEFORELAYER0       7;
//
//#define AO_BEFOREPARALLAX5    100;
//#define AO_BEFOREPARALLAX4    200;
//#define AO_BEFOREPARALLAX3    300;
//#define AO_BEFOREPARALLAX2    400;
//#define AO_BEFOREPARALLAX1    500;
//#define AO_BEFOREPARALLAX0    600;
//
//#define AO_COLMAP             601;

StageBase::~StageBase() {}
