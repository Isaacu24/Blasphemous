#include "Blasphemous.h"
#include "Title.h"
#include "MainMenu.h"
#include "Option.h"

#include "PreCompile.h"

#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"
#include "Stage04.h"
#include "Stage05.h"

#include "Stage10.h"
#include "Stage11.h"
#include "Stage12.h"

#include "Stage20.h"
#include "Stage21.h"

#include "Stage30.h"

#include "Shop.h"

#include "MetaLevel.h"

#include "MetaSpriteManager.h"

#pragma comment(lib, "GameEngineBase.lib")


Blasphemous::Blasphemous() {}

Blasphemous::~Blasphemous() {}

void Blasphemous::Start()
{
    {
        GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("Distortion");
        NewPipe->SetInputAssembler1VertexBuffer("FullRect");
        NewPipe->SetInputAssembler2IndexBuffer("FullRect");
        NewPipe->SetVertexShader("Distortion.hlsl");
        NewPipe->SetPixelShader("Distortion.hlsl");
    }

    {
        GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("SinWave");
        NewPipe->SetInputAssembler1VertexBuffer("FullRect");
        NewPipe->SetInputAssembler2IndexBuffer("FullRect");
        NewPipe->SetVertexShader("SinWave.hlsl");
        NewPipe->SetPixelShader("SinWave.hlsl");
    }

    LoadResources();
    CutTexture();

    CreateLevel<Title>("Title");
    CreateLevel<MainMenu>("MainMenu");
    CreateLevel<Option>("Option");

    //형제단 본부
    CreateLevel<Stage01>("Stage01");
    CreateLevel<Stage02>("Stage02");
    CreateLevel<Stage03>("Stage03");
    CreateLevel<Stage04>("Stage04");
    CreateLevel<Stage05>("Stage05");

    // 파묻힌 교회의 황무지
    CreateLevel<Stage10>("Stage10");
    CreateLevel<Stage11>("Stage11");
    CreateLevel<Stage12>("Stage12");

    // 교황 성하의 회랑
    CreateLevel<Stage20>("Stage20");
    CreateLevel<Stage21>("Stage21");

    //꿈의 저편
    CreateLevel<Stage30>("Stage30");

    //상점
    CreateLevel<Shop>("Shop");

    //메타 파일 테스트 레벨
    CreateLevel<MetaLevel>("MetaLevel");

    ChangeLevel("Title");

    //디버깅
    GameEngineInput::GetInst()->CreateKey("GotoTitle", 'T');
    GameEngineInput::GetInst()->CreateKey("GotoMainMenu", 'M');
    GameEngineInput::GetInst()->CreateKey("GotoStage0", VK_NUMPAD0);
    GameEngineInput::GetInst()->CreateKey("GotoStage1", VK_NUMPAD1);
    GameEngineInput::GetInst()->CreateKey("GotoStage2", VK_NUMPAD2);
    GameEngineInput::GetInst()->CreateKey("GotoStage3", VK_NUMPAD3);
    GameEngineInput::GetInst()->CreateKey("GotoStage4", VK_NUMPAD4);

    GameEngineInput::GetInst()->CreateKey("GotoStage5", VK_NUMPAD5);
    GameEngineInput::GetInst()->CreateKey("GotoStage6", VK_NUMPAD6);
    GameEngineInput::GetInst()->CreateKey("GotoStage7", VK_NUMPAD7);
    GameEngineInput::GetInst()->CreateKey("GotoStage8", VK_NUMPAD8);
    GameEngineInput::GetInst()->CreateKey("GotoStage9", VK_NUMPAD9);

    GameEngineInput::GetInst()->CreateKey("ScriptSkip", VK_RETURN);

    GameEngineInput::GetInst()->CreateButton("GamePadX", GAMEPAD_X);
    GameEngineInput::GetInst()->CreateButton("GamePadA", GAMEPAD_A);
    GameEngineInput::GetInst()->CreateButton("GamePadB", GAMEPAD_B);
    GameEngineInput::GetInst()->CreateButton("GamePadY", GAMEPAD_Y);

    //플레이어 키
    if (false == GameEngineInput::GetInst()->IsButton("PenitentA"))
    {
        GameEngineInput::GetInst()->CreateButton("PenitentA", GAMEPAD_A);
        GameEngineInput::GetInst()->CreateButton("PenitentX", GAMEPAD_X);
        GameEngineInput::GetInst()->CreateButton("PenitentB", GAMEPAD_B);
        GameEngineInput::GetInst()->CreateButton("PenitentY", GAMEPAD_Y);

        GameEngineInput::GetInst()->CreateButton("PenitentLeftShoulder", GAMEPAD_LEFT_SHOULDER);  // LB
        GameEngineInput::GetInst()->CreateButton("PenitentRightShoulder", GAMEPAD_RIGHT_SHOULDER);

        GameEngineInput::GetInst()->CreateButton("PenitentLeftThumb", GAMEPAD_LEFT_THUMB);
        GameEngineInput::GetInst()->CreateButton("PenitentRightThumb", GAMEPAD_RIGHT_THUMB);

        GameEngineInput::GetInst()->CreateButton("PenitentStart", GAMEPAD_START);
        GameEngineInput::GetInst()->CreateButton("PenitentBack", GAMEPAD_BACK);

        GameEngineInput::GetInst()->CreateButton("PenitentDPADUP", XINPUT_GAMEPAD_DPAD_UP);
        GameEngineInput::GetInst()->CreateButton("PenitentDPADDOWN", XINPUT_GAMEPAD_DPAD_DOWN);
        GameEngineInput::GetInst()->CreateButton("PenitentDPADLEFT", XINPUT_GAMEPAD_DPAD_LEFT);
        GameEngineInput::GetInst()->CreateButton("PenitentDPADRIGHT", XINPUT_GAMEPAD_DPAD_RIGHT);
    }

    if (false == GameEngineInput::GetInst()->IsKey("PenitentLeft"))
    {
        GameEngineInput::GetInst()->CreateKey("PenitentLeft", 'A');
        GameEngineInput::GetInst()->CreateKey("PenitentRight", 'D');
        GameEngineInput::GetInst()->CreateKey("PenitentUp", 'W');
        GameEngineInput::GetInst()->CreateKey("PenitentDown", 'S');
        GameEngineInput::GetInst()->CreateKey("Interaction", 'E');
        GameEngineInput::GetInst()->CreateKey("Escape", VK_ESCAPE);
        GameEngineInput::GetInst()->CreateKey("PenitentJump", VK_SPACE);
        GameEngineInput::GetInst()->CreateKey("PenitentSlide", VK_LSHIFT);
        GameEngineInput::GetInst()->CreateKey("PenitentRecovery", 'F');
        GameEngineInput::GetInst()->CreateKey("PenitentAttack", 'K');
        GameEngineInput::GetInst()->CreateKey("PenitentParry", 'J');
        GameEngineInput::GetInst()->CreateKey("PenitentTelport", 'B');
        GameEngineInput::GetInst()->CreateKey("PenitentPary", 'P');
        GameEngineInput::GetInst()->CreateKey("PenitentL", 'L');
        GameEngineInput::GetInst()->CreateKey("PenitentChrage", 'Q');
        GameEngineInput::GetInst()->CreateKey("FreeCamera", 'O');

        GameEngineInput::GetInst()->CreateKey("PenitentAnimation", '1');
        GameEngineInput::GetInst()->CreateKey("InventoryOn", 'I');
    }

    GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void Blasphemous::Update(float _DeltaTime)
{
    if (true == GameEngineInput::GetInst()->IsDownKey("GotoTitle"))
    {
        ChangeLevel("Title");

        float4 _Scale = {1980, 1080};

        RECT Rc = {0, 0, _Scale.ix(), _Scale.iy()};

        AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, TRUE);
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoMainMenu"))
    {
        ChangeLevel("MainMenu");
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage0"))
    {
        ChangeLevel("Stage01");
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage1"))
    {
        ChangeLevel("Stage02");
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage2"))
    {
        ChangeLevel("Stage03");
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage3"))
    {
        ChangeLevel("Stage04");
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage4"))
    {
        ChangeLevel("Stage05");
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage5"))
    {
        ChangeLevel("Stage10");
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage6"))
    {
        ChangeLevel("Stage20");
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage7"))
    {
        ChangeLevel("Stage21");
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage8"))
    {
        ChangeLevel("Stage30");
    }

    if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage9"))
    {
        ChangeLevel("Shop");
    }
}

void Blasphemous::End() { MetaSpriteManager::Destroy(); }

void Blasphemous::LoadResources()
{
    LoadMap("Brotherhood", 1, 1);
    LoadMap("Brotherhood", 1, 2);
    LoadMap("Brotherhood", 1, 3);
    LoadMap("Brotherhood", 1, 4);
    LoadMap("Brotherhood", 1, 5);

    LoadMap("BuriedChurches", 2, 1);
    LoadMap("BuriedChurches", 2, 2);
    LoadMap("BuriedChurches", 2, 3);

    LoadMap("DeambulatoryOfHisHoliness", 12, 2);
    LoadMap("DeambulatoryOfHisHoliness", 12, 3);

    LoadMap("OtherSideoftheDream", 13, 1);

    LoadMap("Shop", 15, 1);


    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "Sound", "Actor", "Player"});

        std::vector<GameEngineFile> Sounds = Dir.GetAllFile();

        for (size_t i = 0; i < Sounds.size(); i++)
        {
            GameEngineSound::LoadRessource(Sounds[i].GetFullPath());
        }
    }

    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "Sound", "BossMusic"});

        std::vector<GameEngineFile> Sounds = Dir.GetAllFile();

        for (size_t i = 0; i < Sounds.size(); i++)
        {
            GameEngineSound::LoadRessource(Sounds[i].GetFullPath());
        }
    }


    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "Sound", "Actor", "ElderBrother"});

        std::vector<GameEngineFile> Sounds = Dir.GetAllFile();

        for (size_t i = 0; i < Sounds.size(); i++)
        {
            GameEngineSound::LoadRessource(Sounds[i].GetFullPath());
        }
    }

    // UI 이미지
    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "UI"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }


    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "UI", "MainMenu"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }

    // UI Inventory
    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "UI", "Inventory"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }

    // UI Loading
    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "UI", "Loading"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }

    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "UI", "Button"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }
    // NPC
    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "Sprite", "NPC", "Deosgracias"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }

    // Object
    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "Sprite", "Object"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }

    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "MetaAtlas", "MetaObject"});
        MetaSpriteManager::Inst_->Load(Dir);
    }

    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "MetaAtlas", "MetaUI"});
        MetaSpriteManager::Inst_->Load(Dir);
    }


    GameEngineFont::Load("궁서");
    GameEngineFont::Load("Neo둥근모");

    LoadBossMonster();
    LoadNormalMonster();
    LoadEffect();


    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "MetaAtlas", "Penitent"});
        MetaSpriteManager::Inst_->Load(Dir);
    }
}

//맵 텍스쳐
void Blasphemous::LoadMap(const std::string& _Level, int _Room, int _Index)
{
    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "Map"});
        Dir.Move(_Level);
        Dir.Move(std::to_string(_Room) + "-" + std::to_string(_Index));

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }
}

// BossMonster
void Blasphemous::LoadBossMonster()
{
    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "MetaAtlas", "MetaMonster", "Boss", "Pope"});
        MetaSpriteManager::Inst_->Load(Dir);
    }

    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "Sprite", "Monster", "Boss", "Pontiff"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }

    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "Sprite", "Monster", "Boss", "ElderBrother"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }
}

void Blasphemous::LoadNormalMonster()
{
    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "MetaAtlas", "MetaMonster", "Normal", "ShieldMaiden"});
        MetaSpriteManager::Inst_->Load(Dir);
    }

    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "MetaAtlas", "MetaMonster", "Normal", "Crosscrawler"});
        MetaSpriteManager::Inst_->Load(Dir);
    }

    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "MetaAtlas", "MetaMonster", "Normal", "LionHead"});
        MetaSpriteManager::Inst_->Load(Dir);
    }

    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "MetaAtlas", "MetaMonster", "Normal", "WingedFace"});
        MetaSpriteManager::Inst_->Load(Dir);
    }

    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "Sprite", "Monster", "Normal", "Fool_knife"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }
}

void Blasphemous::LoadEffect()
{
    {
        GameEngineDirectory Dir;
        MovePath(Dir, {"ContentsResources", "Resources", "Sprite", "Effect"});

        std::vector<GameEngineFile> Textures = Dir.GetAllFile();

        for (size_t i = 0; i < Textures.size(); i++)
        {
            GameEngineTexture::Load(Textures[i].GetFullPath());
        }
    }
}

void Blasphemous::CutTexture()
{
    // BossMonster
    GameEngineTexture::Cut("pontiff_closing_face.png", 5, 3);
    GameEngineTexture::Cut("pontiff_closing_torso.png", 5, 3);
    GameEngineTexture::Cut("pontiff_idle_helmet.png", 7, 5);
    GameEngineTexture::Cut("pontiff_idle_torso.png", 7, 5);
    GameEngineTexture::Cut("pontiff_openedIdle_face_DEATH.png", 10, 7);
    GameEngineTexture::Cut("pontiff_openIdle_face.png", 7, 5);
    GameEngineTexture::Cut("pontiff_opening_face.png", 5, 4);
    GameEngineTexture::Cut("pontiff_opening_torso.png", 5, 4);
    GameEngineTexture::Cut("pontiff_opening_helmet.png", 1, 1);
    GameEngineTexture::Cut("pontiff_closing_helmet.png", 1, 1);

    GameEngineTexture::Cut("elderBrother_idle.png", 3, 4);
    GameEngineTexture::Cut("elderBrother_jump.png", 4, 7);
    GameEngineTexture::Cut("elderBrother_attack.png", 4, 6);
    GameEngineTexture::Cut("elderBrother_death.png", 5, 10);

    GameEngineTexture::Cut("pontiff_giantSword_teleportOUT.png", 9, 3);
    GameEngineTexture::Cut("pontiff_giantSword_teleportIN.png", 9, 3);
    GameEngineTexture::Cut("pontiff_giantSword_eyeLids.png", 5, 4);
    GameEngineTexture::Cut("pontiff_giantSword_swordSprite.png", 1, 1);

    // NormalMonster
    GameEngineTexture::Cut("Fool_death_knife.png", 4, 4);
    GameEngineTexture::Cut("Fool_hurt_knife.png", 3, 3);
    GameEngineTexture::Cut("fool_idle_knife.png", 3, 4);
    GameEngineTexture::Cut("Fool_turn_knife.png", 3, 3);
    GameEngineTexture::Cut("Fool_walk_knife.png", 3, 3);

    // NPC
    GameEngineTexture::Cut("Deosgracias_idle.png", 7, 3);
    GameEngineTexture::Cut("Deosgracias_front.png", 13, 7);

    // Object
    GameEngineTexture::Cut("priedieu_stand_and_liton_anim.png", 7, 1);
    GameEngineTexture::Cut("brotherhood_door_anim 1.png", 8, 2);
    GameEngineTexture::Cut("glassSwitch.png", 7, 4);
    GameEngineTexture::Cut("crow_idle_anim.png", 8, 13);
    GameEngineTexture::Cut("reja_lateral_invertedBell_descending.png", 7, 3);
    // GameEngineTexture::Cut("breakableTwistedCorpse04.png", 5, 3);

    GameEngineTexture::Cut("guiltSystem_blinkFxs.png", 7, 5);
    GameEngineTexture::Cut("guiltDropVanish.png", 5, 2);

    // Effect
    GameEngineTexture::Cut("BloodSplatters.png", 5, 5);
    GameEngineTexture::Cut("BloodSplattersV3.png", 4, 4);
    GameEngineTexture::Cut("BloodSplattersV4.png", 4, 4);

    GameEngineTexture::Cut("burntFace_rayBeam_impact.png", 5, 4);
    GameEngineTexture::Cut("elderBrother_corpse.png", 4, 3);

    GameEngineTexture::Cut("TakeBackProyectile.png", 6, 2);
    GameEngineTexture::Cut("TakeBackProyectileExplosion.png", 6, 3);
    GameEngineTexture::Cut("TakeBackProyectileHead.png", 6, 2);

    GameEngineTexture::Cut("pope_twistedOne_symbol.png", 8, 3);
    GameEngineTexture::Cut("pope_fireBall.png", 4, 3);
    GameEngineTexture::Cut("pope_fireBallVortex.png", 7, 7);

    GameEngineTexture::Cut("pope_toxicOrb.png", 6, 6);
    GameEngineTexture::Cut("Pope_toxicCloud.png", 6, 5);
    GameEngineTexture::Cut("pope_toxicCloudv2.png", 4, 4);

    GameEngineTexture::Cut("lightningBolt_fxs.png", 12, 6);
    GameEngineTexture::Cut("lightningBolt_Tileable_fxs.png", 13, 6);

    GameEngineTexture::Cut("pope_magicMissile.png", 6, 5);

    // UI
    GameEngineTexture::Cut("ItemCursorAlt.png", 4, 4);
    GameEngineTexture::Cut("alliedCherub.png", 4, 3);
}
