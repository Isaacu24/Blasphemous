#include "Title.h"
#include "PreCompile.h"
#include "TitleLogo.h"
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

	TitleLogo* Logo = CreateActor<TitleLogo>();
	Logo->GetTransform().SetWorldMove({ 0.f, 30.f, 0.f });

	Inventory* NewInventory = CreateActor<Inventory>();
}

void Title::Update(float _DeltaTime)
{

}

void Title::End()
{
}
