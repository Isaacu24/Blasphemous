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

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->GetTransform().SetWorldScale({ 3840, 2054 });
	StageRendrer->SetTexture("1-2_Tile.png");

	float OffsetX = StageRendrer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRendrer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

}

void Stage02::Update(float _DeltaTime)
{
}

void Stage02::End()
{
}
