#include "Blasphemous.h"
#include "Title.h"
#include "MainMenu.h"
#include "PreCompile.h"

#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"
#include "Stage04.h"
#include "Stage05.h"

#include "Stage10.h"

#include "Stage20.h"
#include "Stage21.h"

#include "Stage30.h"


#pragma comment(lib, "GameEngineBase.lib")


Blasphemous::Blasphemous() 
{
}

Blasphemous::~Blasphemous() 
{
}

void Blasphemous::Start()
{
	LoadResources();
	CutTexture();

	CreateLevel<Title>("Title"); 
	CreateLevel<MainMenu>("MainMenu");

	//형제단 본부
	CreateLevel<Stage01>("Stage01");
	CreateLevel<Stage02>("Stage02");
	CreateLevel<Stage03>("Stage03");
	CreateLevel<Stage04>("Stage04");
	CreateLevel<Stage05>("Stage05");

	// 파묻힌 교회의 황무지
	CreateLevel<Stage10>("Stage10");

	// 교황 성하의 회랑
	CreateLevel<Stage20>("Stage20");
	CreateLevel<Stage21>("Stage21");

	//꿈의 저편
	CreateLevel<Stage30>("Stage30");

	ChangeLevel("MainMenu");

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
}

void Blasphemous::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDownKey("GotoTitle"))
	{
		ChangeLevel("Title");
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
		//ChangeLevel("Stage10");
	}

}

void Blasphemous::End()
{
}

void Blasphemous::LoadResources()
{
	LoadMap("Brotherhood", 1, 1);
	LoadMap("Brotherhood", 1, 2);
	LoadMap("Brotherhood", 1, 3);
	LoadMap("Brotherhood", 1, 4);
	LoadMap("Brotherhood", 1, 5);

	LoadMap("BuriedChurches", 2, 1);

	LoadMap("DeambulatoryOfHisHoliness", 12, 2);
	LoadMap("DeambulatoryOfHisHoliness", 12, 3);

	LoadMap("OtherSideoftheDream", 13, 1);

	//UI 이미지
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("GameEngineResources");
		Dir.Move("GameEngineResources");
		Dir.Move("Resources");
		Dir.Move("UI");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}


	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("GameEngineResources");
		Dir.Move("GameEngineResources");
		Dir.Move("Resources");
		Dir.Move("UI");
		Dir.Move("MainMenu");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	//UI Inventory
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("GameEngineResources");
		Dir.Move("GameEngineResources");
		Dir.Move("Resources");
		Dir.Move("UI");
		Dir.Move("Inventory");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}


	//Player
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("GameEngineResources");
		Dir.Move("GameEngineResources");
		Dir.Move("Resources");
		Dir.Move("Sprite");
		Dir.Move("Player");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	//NPC
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("GameEngineResources");
		Dir.Move("GameEngineResources");
		Dir.Move("Resources");
		Dir.Move("Sprite");
		Dir.Move("NPC");
		Dir.Move("Deosgracias");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	//Object
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("GameEngineResources");
		Dir.Move("GameEngineResources");
		Dir.Move("Resources");
		Dir.Move("Sprite");
		Dir.Move("Object");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	LoadBossMonster();

	//{
	//	GameEngineDirectory Dir;

	//	Dir.MoveParentToExitsChildDirectory("GameEngineResources");
	//	Dir.Move("GameEngineResources");
	//	Dir.Move("Resources");
	//	Dir.Move("VideoImage");
	//	Dir.Move("FirstBoss");

	//	std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

	//	for (size_t i = 0; i < Shaders.size(); i++)
	//	{
	//		GameEngineTexture::Load(Shaders[i].GetFullPath());
	//	}
	//}
}

//맵 텍스쳐
void Blasphemous::LoadMap(const std::string& _Level, int _Room, int _Index)
{
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("GameEngineResources");
		Dir.Move("GameEngineResources");
		Dir.Move("Resources");
		Dir.Move("Map");
		Dir.Move(_Level);
		Dir.Move(std::to_string(_Room) + "-" + std::to_string(_Index));

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}
}

//BossMonster
void Blasphemous::LoadBossMonster()
{
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("GameEngineResources");
		Dir.Move("GameEngineResources");
		Dir.Move("Resources");
		Dir.Move("Sprite");
		Dir.Move("Monster");
		Dir.Move("Boss");
		Dir.Move("Pontiff");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}
}

void Blasphemous::CutTexture()
{
	//Player
	GameEngineTexture::Cut("penintent_idle_anim.png", 8, 2);
	GameEngineTexture::Cut("penitent_sheathedIdle.png", 7, 7);
	GameEngineTexture::Cut("penitent_verticalattack_LVL3_anim.png", 8, 3);
	GameEngineTexture::Cut("penitent_climbledge_reviewed.png", 4, 3);
	//GameEngineTexture::Cut("penitent_respawning_hw.png", 6, 6);

	//BossMonster
	GameEngineTexture::Cut("pontiff_closing_face.png", 5, 3);
	GameEngineTexture::Cut("pontiff_closing_torso.png", 5, 3);
	GameEngineTexture::Cut("pontiff_idle_helmet.png", 7, 5);
	GameEngineTexture::Cut("pontiff_idle_torso.png", 7, 5);
	GameEngineTexture::Cut("pontiff_openedIdle_face_DEATH.png", 10, 7);
	GameEngineTexture::Cut("pontiff_openIdle_face.png", 7, 5);
	GameEngineTexture::Cut("pontiff_opening_face.png", 5, 4);
	GameEngineTexture::Cut("pontiff_opening_torso.png", 5, 4);

	//NPC
	GameEngineTexture::Cut("Deosgracias_idle.png", 7, 3);
	GameEngineTexture::Cut("Deosgracias_front.png", 13, 7);

	//Object
	GameEngineTexture::Cut("priedieu_stand_and_liton_anim.png", 7, 1);
}
