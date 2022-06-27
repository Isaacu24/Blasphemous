#include "MainMenu.h"
#include "PreCompile.h"
#include <GameEngineCore/GameEngineCameraActor.h>

MainMenu::MainMenu() 
{
}

MainMenu::~MainMenu() 
{
}

void MainMenu::Start()
{
	CreateActor<GameEngineCameraActor>();
}

void MainMenu::Update(float _DeltaTime)
{
}

void MainMenu::End()
{
}
