#include "PreCompile.h"
#include "Stage02.h"

Stage02::Stage02() 
{
}

Stage02::~Stage02() 
{
}

void Stage02::Start()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	Stage_ = CreateActor<StageActor>();
	Stage_->GetTransform().SetLocalPosition({ 1300, 100, 0 });

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->GetTransform().SetWorldScale({ 3840, 2054 });
	StageRendrer->SetTexture("1-2_Tile.png");
}

void Stage02::Update(float _DeltaTime)
{
}

void Stage02::End()
{
}
