#include "Blasphemous.h"
#include "Title.h"
#include "MainMenu.h"
#include "PreCompile.h"
#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"
#include "Stage04.h"
#include "Stage05.h"

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

	CreateLevel<Title>("Title"); 
	CreateLevel<MainMenu>("MainMenu");

	//형제단 본부
	CreateLevel<Stage01>("Stage01");
	CreateLevel<Stage02>("Stage02");
	CreateLevel<Stage03>("Stage03");
	CreateLevel<Stage04>("Stage04");
	CreateLevel<Stage05>("Stage05");

	ChangeLevel("MainMenu");

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
		//ChangeLevel("Stage06");
	}

	if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage6"))
	{
		//ChangeLevel("Stage07");
	}

	if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage7"))
	{
		//ChangeLevel("Stage08");
	}

	if (true == GameEngineInput::GetInst()->IsDownKey("GotoStage8"))
	{
		//ChangeLevel("Stage09");
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
