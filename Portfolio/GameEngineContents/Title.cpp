#include "Title.h"
#include "PreCompile.h"
#include "TitleLogo.h"
#include "TitleActor.h"

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
	Logo->GetTransform().SetWorldPosition({ 30.f, 100.f, 0.f });
}

void Title::Update(float _DeltaTime)
{

}

void Title::End()
{
}
