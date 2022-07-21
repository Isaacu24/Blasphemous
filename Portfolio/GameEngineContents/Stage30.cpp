#include "PreCompile.h"
#include "Stage30.h"
#include "Penitent.h"
#include "Deogracias.h"

Stage30::Stage30() 
{
}

Stage30::~Stage30() 
{
}

void Stage30::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* BeforeParallaxRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRendrer->SetTexture("13_1_BeforeParallax_1.png");
	BeforeParallaxRendrer->ScaleToTexture();

	GameEngineTextureRenderer* BeforeLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeLayerRenderer->SetTexture("13_1_BeforeLayer.png");
	BeforeLayerRenderer->ScaleToTexture();

	Deogracias* NewDeogracias = CreateActor<Deogracias>();
	NewDeogracias->GetTransform().SetWorldMove({ 800, -870 });
	NewDeogracias->ChangeFrontAnimation();
	NewDeogracias->GetTransform().PixLocalNegativeX();

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldMove({ 660, -960 });

	GameEngineTextureRenderer* StageRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer2->SetTexture("13_1_2_Tile.png");
	StageRenderer2->ScaleToTexture();

	GameEngineTextureRenderer* StageRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer1->SetTexture("13_1_1_Tile.png");
	StageRenderer1->ScaleToTexture();

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("13_1_AfterLayer.png");
	AfterLayerRenderer->ScaleToTexture();

	GameEngineTextureRenderer* ChairRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	ChairRenderer->SetTexture("ash-mountain-spritesheet_9.png");
	ChairRenderer->ScaleToTexture();
	ChairRenderer->GetTransform().SetWorldMove({1060, 920});

	float OffsetX = StageRenderer1->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRenderer1->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);
}

void Stage30::Start()
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	SettingStage();
}

void Stage30::Update(float _DeltaTime)
{
	CameraActor_->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition() + float4{ 0, 100 });
}

void Stage30::End()
{
}

