#include "PreCompile.h"
#include "Stage04.h"
#include "Penitent.h"
#include "ElderBrother.h"

Stage04::Stage04()
{
}

Stage04::~Stage04()
{
}

void Stage04::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer->SetTexture("1_4_BeforeParallax_0.png");
	BeforeParallaxRenderer->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer1->SetTexture("1_4_BeforeParallax_1.png");
	BeforeParallaxRenderer1->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer2->SetTexture("1_4_BeforeParallax_2.png");
	BeforeParallaxRenderer2->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer3->SetTexture("1_4_BeforeParallax_3.png");
	BeforeParallaxRenderer3->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer4 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer4->SetTexture("1_4_BeforeParallax_4.png");
	BeforeParallaxRenderer4->ScaleToTexture();

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("1_4_Tile.png");
	StageRenderer->ScaleToTexture();

	ElderBrother* NewElderBrother = CreateActor<ElderBrother>();
	NewElderBrother->GetTransform().SetWorldMove({ 2000, -700 });
	NewElderBrother->GetTransform().SetLocalScale({ 1500, 750 });
	NewElderBrother->GetTransform().PixLocalNegativeX();

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldMove({ 280, -925 });

	GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRenderer->SetTexture("1_4_Door.png");
	DoorRenderer->ScaleToTexture();

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("1_4_AfterLayer_0.png");
	AfterLayerRenderer->ScaleToTexture();

	float OffsetX = StageRenderer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRenderer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);
}


void Stage04::Start()
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	SettingStage();
}

void Stage04::Update(float _DeltaTime)
{
	CameraActor_->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition() + float4{0, 100});

	if (-700 < CameraActor_->GetTransform().GetLocalPosition().y)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ CameraActor_->GetTransform().GetLocalPosition().x, -700 });
	}

	if (650 > CameraActor_->GetTransform().GetLocalPosition().x)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ 650, CameraActor_->GetTransform().GetLocalPosition().y });
	}

	if (2000 < CameraActor_->GetTransform().GetLocalPosition().x)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ 2000, CameraActor_->GetTransform().GetLocalPosition().y });
	}

	GameEngineDebug::OutPutString("x : " + std::to_string(CameraActor_->GetTransform().GetLocalPosition().x));
	GameEngineDebug::OutPutString("y : " + std::to_string(CameraActor_->GetTransform().GetLocalPosition().y));
}

void Stage04::End()
{
}
