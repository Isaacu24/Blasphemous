#include "PreCompile.h"
#include "StageActor.h"

StageActor::StageActor() 
{
}

StageActor::~StageActor() 
{
}

void StageActor::Start()
{
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

void StageActor::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsPressKey("CamLeft"))
	{
		GetLevel()->GetMainCameraActorTransform().SetLocalMove(-GetLevel()->GetMainCameraActorTransform().GetRightVector() * 200 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("CamRight"))
	{
		GetLevel()->GetMainCameraActorTransform().SetLocalMove(GetLevel()->GetMainCameraActorTransform().GetRightVector() * 200 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("CamUp"))
	{
		GetLevel()->GetMainCameraActorTransform().SetLocalMove(GetLevel()->GetMainCameraActorTransform().GetUpVector() * 200 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("CamDown"))
	{
		GetLevel()->GetMainCameraActorTransform().SetLocalMove(-GetLevel()->GetMainCameraActorTransform().GetUpVector() * 200 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("CamForward"))
	{
		GetLevel()->GetMainCameraActorTransform().SetLocalMove(GetLevel()->GetMainCameraActorTransform().GetForwardVector() * 200 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("CamBack"))
	{
		GetLevel()->GetMainCameraActorTransform().SetLocalMove(-GetLevel()->GetMainCameraActorTransform().GetForwardVector() * 200 * _DeltaTime);
	}

	static float4 Rot = { 0.0f, 0.0f, 0.0f };
	if (true == GameEngineInput::GetInst()->IsPressKey("CamRotY+"))
	{
		Rot.y += 360.0f * _DeltaTime;
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("CamRotY-"))
	{
		Rot.y -= 360.0f * _DeltaTime;
	}
}

void StageActor::End()
{
}
