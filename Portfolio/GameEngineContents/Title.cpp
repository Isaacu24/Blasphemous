#include "Title.h"
#include "PreCompile.h"
#include "TitleActor.h"
#include "Inventory.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Start()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	TitleActor* Actor = CreateActor<TitleActor>();
}

void Title::Update(float _DeltaTime)
{


}

void Title::End()
{
}
