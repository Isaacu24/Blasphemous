#include "Pilgrimage.h"
#include "PreCompile.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include "Penitent.h"
#include "Stage01.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

Pilgrimage::Pilgrimage() 
{

}

Pilgrimage::~Pilgrimage() 
{
}
void Pilgrimage::Start()
{
	//스테이지 초기화(카메라)
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 0.0f });

	Penitent* Player = CreateActor<Penitent>(1);

	GameEngineInput::GetInst()->CreateButton("X", GAMEPAD_X);

	if (false == GameEngineInput::GetInst()->IsKey("CamLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("CamLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("CamRight", 'D');
		GameEngineInput::GetInst()->CreateKey("CamUp", 'Q');
		GameEngineInput::GetInst()->CreateKey("CamDown", 'E');
		GameEngineInput::GetInst()->CreateKey("CamForward", 'W');
		GameEngineInput::GetInst()->CreateKey("CamBack", 'S');

		GameEngineInput::GetInst()->CreateKey("CamRotY+", 'R');
		GameEngineInput::GetInst()->CreateKey("CamRotY-", 'T');
	}
}

void Pilgrimage::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsUpButton("X"))
	{
		GameEngineInput::GetInst()->VibrationOn();
	}

	if (32767 <= GameEngineInput::GetInst()->GetMagnitudeL())
	{
		int a = 0;
	}

	if (255 <= GameEngineInput::GetInst()->GetLeftTrigger())
	{
		int a = 0;
	}

	if (true == GameEngineInput::GetInst()->IsPress("CamLeft"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetRightVector() * 100 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("CamRight"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetRightVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamUp"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetUpVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamDown"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetUpVector() * 100 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("CamForward"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetForwardVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamBack"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetForwardVector() * 100 * _DeltaTime);
	}

	static float4 Rot = { 0.0f, 0.0f, 0.0f };
	if (true == GameEngineInput::GetInst()->IsPress("CamRotY+"))
	{
		Rot.y += 360.0f * _DeltaTime;
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamRotY-"))
	{
		Rot.y -= 360.0f * _DeltaTime;
	}
}

void Pilgrimage::End()
{
}
