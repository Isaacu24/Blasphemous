#include "PreCompile.h"
#include "Stage30.h"
#include "CutScenePlayer.h"

Stage30::Stage30() 
{
}

Stage30::~Stage30() 
{
}

void Stage30::Start()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->GetTransform().SetWorldScale({ 3840, 1500 });
	StageRendrer->SetTexture("13-1_Tile.png");

	float OffsetX = StageRendrer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRendrer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	CutScenePlayer* Player = CreateActor<CutScenePlayer>();
}

void Stage30::Update(float _DeltaTime)
{
}

void Stage30::End()
{
}
