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
	GameEngineTextureRenderer* ButttonShadow = Actor->CreateComponent<GameEngineTextureRenderer>();
	ButttonShadow->SetTexture("PressAnyButttonShadow.png");
	ButttonShadow->GetTransform().SetWorldScale({ 214, 24 });
	ButttonShadow->GetTransform().SetWorldMove({ 0.f, -150.f, 0.f });

	GameEngineTextureRenderer* PressAnyKey = Actor->CreateComponent<GameEngineTextureRenderer>();
	PressAnyKey->SetTexture("PressAnyButton.png");
	PressAnyKey->GetTransform().SetWorldScale({250, 20});
	PressAnyKey->GetTransform().SetWorldMove({ 0.f, -150.f, 0.f });

	TitleLogo* Logo = CreateActor<TitleLogo>();
	Logo->GetTransform().SetWorldMove({ 0.f, 30.f, 0.f });
}

void Title::Update(float _DeltaTime)
{

}

void Title::End()
{
}
