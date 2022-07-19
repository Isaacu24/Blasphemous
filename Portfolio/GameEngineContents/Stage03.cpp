#include "PreCompile.h"
#include "Stage03.h"
#include "Penitent.h"

Stage03::Stage03() 
{
}

Stage03::~Stage03() 
{
}

void Stage03::Start()
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->SetTexture("1_3_Tile.png");
	StageRendrer->ScaleToTexture();

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldMove({ 237, -960 });

	GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRenderer->SetTexture("1_3_Door.png");
	DoorRenderer->ScaleToTexture();

	float OffsetX = StageRendrer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRendrer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);
}

void Stage03::Update(float _DeltaTime)
{
	CameraActor_->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition());
}


void Stage03::End()
{
}
