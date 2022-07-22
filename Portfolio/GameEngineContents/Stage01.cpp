#include "PreCompile.h"
#include "Stage01.h"
#include <GameEngineCore/GameEngineTexture.h>
#include "Penitent.h"

Stage01::Stage01() 
{
}

Stage01::~Stage01() 
{

}


void Stage01::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer->SetTexture("1_1_BeforeParallax_0.png");
	BeforeParallaxRenderer->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer1->SetTexture("1_1_BeforeParallax_1.png");
	BeforeParallaxRenderer1->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer2->SetTexture("1_1_BeforeParallax_2.png");
	BeforeParallaxRenderer2->ScaleToTexture();

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("1_1_Tile.png");
	StageRenderer->ScaleToTexture();

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldMove({ 1225, -940 });

	GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRenderer->SetTexture("1_1_Door.png");
	DoorRenderer->ScaleToTexture();

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("1_1_AfterLayer.png");
	AfterLayerRenderer->ScaleToTexture();

	float OffsetX = StageRenderer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRenderer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);
}


void Stage01::Start()
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	
	SettingStage();
}

void Stage01::Update(float _DeltaTime)
{
	CameraActor_->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition() + float4{0, 100});

	if (-730 < CameraActor_->GetTransform().GetWorldPosition().y)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ Penitent_->GetTransform().GetLocalPosition().x, -730});
	}

	if (690 > CameraActor_->GetTransform().GetWorldPosition().x)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ 690, CameraActor_->GetTransform().GetLocalPosition().y });
	}

	if (3150 < CameraActor_->GetTransform().GetWorldPosition().x)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ 3150, CameraActor_->GetTransform().GetLocalPosition().y });
	}

	GameEngineDebug::OutPutString("x : " + std::to_string(CameraActor_->GetTransform().GetLocalPosition().x));
	GameEngineDebug::OutPutString("y : " + std::to_string(CameraActor_->GetTransform().GetLocalPosition().y));
}

void Stage01::End()
{
}
