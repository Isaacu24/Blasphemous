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
	//스테이지 초기화(카메라
	CreateActor<GameEngineCameraActor>();
	Penitent* Player = CreateActor<Penitent>(1);

	GameEngineDefaultRenderer* PlayerRenderer = Player->CreateComponent<GameEngineDefaultRenderer>();
	PlayerRenderer->SetPipeLine("Color");

	GameEngineInput::GetInst()->CreateButton("X", GAMEPAD_X);
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
}

void Pilgrimage::End()
{
}
