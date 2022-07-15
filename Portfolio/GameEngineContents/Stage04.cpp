#include "PreCompile.h"
#include "Stage04.h"

Stage04::Stage04() 
{
}

Stage04::~Stage04() 
{
}

void Stage04::Start()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	Stage_ = CreateActor<StageActor>();
	Stage_->GetTransform().SetLocalPosition({ 700, -200, 0 });

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->GetTransform().SetWorldScale({ 3840, 2054 });
	StageRendrer->SetTexture("1_4_Tile.png");
}

void Stage04::Update(float _DeltaTime)
{
}

void Stage04::End()
{
}
