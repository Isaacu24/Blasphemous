#include "MainMenu.h"
#include "PreCompile.h"
#include "MainMenuActor.h"

MainMenu::MainMenu() 
{
}

MainMenu::~MainMenu() 
{
}

void MainMenu::Start()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	
	CreateActor<MainMenuActor>();
}

void MainMenu::Update(float _DeltaTime)
{
}

void MainMenu::End()
{
}
