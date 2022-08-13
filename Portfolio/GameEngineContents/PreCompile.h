#pragma once

#define GAMEPAD_DPAD_UP					 0x0001
#define GAMEPAD_DPAD_DOWN				 0x0002
#define GAMEPAD_DPAD_LEFT				 0x0004
#define GAMEPAD_DPAD_RIGHT				 0x0008
#define GAMEPAD_START					 0x0010
#define GAMEPAD_BACK					 0x0020
#define GAMEPAD_LEFT_THUMB				 0x0040
#define GAMEPAD_RIGHT_THUMB				 0x0080
#define GAMEPAD_LEFT_SHOULDER			 0x0100
#define GAMEPAD_RIGHT_SHOULDER			 0x0200
#define GAMEPAD_A						 0x1000
#define GAMEPAD_B						 0x2000
#define GAMEPAD_X						 0x4000
#define GAMEPAD_Y                        0x8000


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

//Contents
#include <GameEngineContents/StageActor.h>
#include "GravityComponent.h"
#include "CutScenePlayer.h"
#include "GlobalValue.h"
#include "LoadingActor.h"

#include "Penitent.h"



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
}