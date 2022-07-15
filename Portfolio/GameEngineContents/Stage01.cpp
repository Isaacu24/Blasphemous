#include "PreCompile.h"
#include "Stage01.h"

Stage01::Stage01() 
{
}

Stage01::~Stage01() 
{
}

void Stage01::Start()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	
	Stage_ = CreateActor<StageActor>();
	Stage_->GetTransform().SetLocalPosition({ 700, -200, 0 });

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->GetTransform().SetWorldScale({ 3840, 2054 });
	StageRendrer->SetTexture("1_1_Tile.png");
}

void Stage01::Update(float _DeltaTime)
{
}

void Stage01::End()
{
}
