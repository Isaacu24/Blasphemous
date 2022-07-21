#include "PreCompile.h"
#include "Stage05.h"
#include "Penitent.h"
#include "Deogracias.h"

Stage05::Stage05()
{
}

Stage05::~Stage05()
{
}


void Stage05::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("1_5_Tile.png");
	StageRenderer->ScaleToTexture();

	Deogracias* NewDeogracias = CreateActor<Deogracias>();
	NewDeogracias->GetTransform().SetLocalMove({ 940, -570 });
	NewDeogracias->GetTransform().PixLocalNegativeX();

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldMove({ 522, -670 });

	GameEngineTextureRenderer* DoorRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRendrer->SetTexture("1_5_Door.png");
	DoorRendrer->ScaleToTexture();

	float OffsetX = StageRenderer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRenderer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	CameraActor_->GetTransform().SetWorldPosition(float4{ 950, -570});
}

void Stage05::Start()
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	SettingStage();
}

void Stage05::Update(float _DeltaTime)
{
	CameraActor_->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition());

	if (-550 < CameraActor_->GetTransform().GetLocalPosition().y)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ Penitent_->GetTransform().GetLocalPosition().x, -550 });
	}
}

void Stage05::End()
{
}
