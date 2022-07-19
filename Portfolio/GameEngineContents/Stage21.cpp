#include "PreCompile.h"
#include "Stage21.h"
#include "Penitent.h"

Stage21::Stage21() 
{
}

Stage21::~Stage21() 
{
}

void Stage21::Start()
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->SetTexture("12_3_Tile.png");
	StageRendrer->ScaleToTexture();

	float OffsetX = StageRendrer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRendrer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	Penitent_ = CreateActor<Penitent>();

	Penitent_->GetTransform().SetWorldMove({ 0, 0 });
}

void Stage21::Update(float _DeltaTime)
{
	CameraActor_->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition());
}


void Stage21::End()
{
}
