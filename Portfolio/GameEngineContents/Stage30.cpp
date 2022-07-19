#include "PreCompile.h"
#include "Stage30.h"
#include "Penitent.h"

Stage30::Stage30() 
{
}

Stage30::~Stage30() 
{
}

void Stage30::Start()
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->SetTexture("13-1_Tile.png");
	StageRendrer->ScaleToTexture();

	float OffsetX = StageRendrer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRendrer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	CutScenePlayer* Player = CreateActor<CutScenePlayer>();

	Penitent_ = CreateActor<Penitent>();

	Penitent_->GetTransform().SetWorldMove({ 0, 0 });
}

void Stage30::Update(float _DeltaTime)
{
	CameraActor_->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition());
}

void Stage30::End()
{
}
