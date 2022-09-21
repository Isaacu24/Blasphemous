#pragma once

#define GAMEPAD_DPAD_UP        0x0001
#define GAMEPAD_DPAD_DOWN      0x0002
#define GAMEPAD_DPAD_LEFT      0x0004
#define GAMEPAD_DPAD_RIGHT     0x0008
#define GAMEPAD_START          0x0010
#define GAMEPAD_BACK           0x0020
#define GAMEPAD_LEFT_THUMB     0x0040
#define GAMEPAD_RIGHT_THUMB    0x0080
#define GAMEPAD_LEFT_SHOULDER  0x0100
#define GAMEPAD_RIGHT_SHOULDER 0x0200
#define GAMEPAD_A              0x1000
#define GAMEPAD_B              0x2000
#define GAMEPAD_X              0x4000
#define GAMEPAD_Y              0x8000


// std and direct
#include <string>

#include <map>
#include <list>
#include <set>
#include <vector>
#include <chrono>

#include <Windows.h>

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>

#include <DirectXCollision.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

// base
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

// core
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineStateManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

// Contents
#include <GameEngineContents/StageActor.h>
#include "GravityComponent.h"
#include "SpectrumComponent.h"
#include "CutScenePlayer.h"
#include "GlobalValue.h"
#include "LoadingActor.h"
#include "StageBase.h"
#include "Item.h"

#include "Penitent.h"

#include "MessageUI.h"
#include "Milestone.h"

#include "Candle.h"
#include "Fly.h"
#include "Cemetry.h"


namespace
{
    inline void MovePath(GameEngineDirectory& dir, std::initializer_list<std::string> path)
    {
        dir.MoveParentToExitsChildDirectory(*path.begin());
        dir.Move(*path.begin());

        for (int i = 1; i < path.size(); ++i)
        {
            dir.Move(*(path.begin() + i));
        }
    }
}  // namespace

struct MetaData
{
    int   Index;
    float PosX;
    float PosY;
    float Width;
    float Height;
    float PivotX;
    float PivotY;
};

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
#define AO_FRONTEFFECT        0.425f;
#define AO_FRONTBOSS          0.45f;
#define AO_PLATFORM           0.5f;
#define AO_BOSSMONSTEREFFECT  0.6f;
#define AO_BOSSMONSTER        0.7f;
#define AO_MONSTER            0.8f;
#define AO_OBJECT             0.9f;
#define AO_TILE               1.0f;

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

namespace
{
    float AfterParallaxZ  = AO_AFTERPARALLAX0;
    float AfterParallax1Z = AO_AFTERPARALLAX1;
    float AfterParallax2Z = AO_AFTERPARALLAX2;
    float AfterParallax3Z = AO_AFTERPARALLAX3;
    float AfterParallax4Z = AO_AFTERPARALLAX4;
    float AfterParallax5Z = AO_AFTERPARALLAX5;

    float AfterLayerZ  = AO_AfterLayer0;
    float AfterLayer1Z = AO_AfterLayer1;
    float AfterLayer2Z = AO_AfterLayer2;
    float AfterLayer3Z = AO_AfterLayer3;
    float AfterLayer4Z = AO_AfterLayer4;
    float AfterLayer5Z = AO_AfterLayer5;

    float DoorZ = AO_DOOR;

    float PlayerEffectZ       = AO_PLAYEREFFECT;
    float PlayerZ             = AO_PLAYER;
    float PlayerBehindEffectZ = AO_PLAYERBEHINDEFFECT;
    float NPCZ                = AO_NPC;
    float FrontEffetZ          = AO_FRONTEFFECT;
    float FrontBossZ           = AO_FRONTBOSS;
    float PlatformZ           = AO_PLATFORM;
    float BossMonsterEffectZ  = AO_BOSSMONSTEREFFECT;
    float BossMonsterZ        = AO_BOSSMONSTER;
    float MonsterZ            = AO_MONSTER;
    float ObjectZ             = AO_OBJECT;

    float TileZ = AO_TILE;

    float BeforeLayerZ  = AO_BEFORELAYER0;
    float BeforeLayer1Z = AO_BEFORELAYER1;
    float BeforeLayer2Z = AO_BEFORELAYER2;
    float BeforeLayer3Z = AO_BEFORELAYER3;
    float BeforeLayer4Z = AO_BEFORELAYER4;
    float BeforeLayer5Z = AO_BEFORELAYER5;

    float BeforeParallaxZ  = AO_BEFOREPARALLAX0;
    float BeforeParallax1Z = AO_BEFOREPARALLAX1;
    float BeforeParallax2Z = AO_BEFOREPARALLAX2;
    float BeforeParallax3Z = AO_BEFOREPARALLAX3;
    float BeforeParallax4Z = AO_BEFOREPARALLAX4;
    float BeforeParallax5Z = AO_BEFOREPARALLAX5;

    float ColmapZ = AO_COLMAP;
}  // namespace
