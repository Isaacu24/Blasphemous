#include "PreCompile.h"
#include "Stage05.h"

Stage05::Stage05() 
{
}

Stage05::~Stage05() 
{
}

void Stage05::Start()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	Stage_ = CreateActor<StageActor>();
	Stage_->GetTransform().SetLocalPosition({ 700, 300, 0 });
	 
	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->GetTransform().SetWorldScale({ 3840, 2054 });
	StageRendrer->SetTexture("1_5_Tile.png");
}

void Stage05::Update(float _DeltaTime)
{
}

void Stage05::End()
{
}
