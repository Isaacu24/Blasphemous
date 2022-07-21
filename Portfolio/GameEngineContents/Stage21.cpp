#include "PreCompile.h"
#include "Stage21.h"
#include "Penitent.h"
#include "Pontiff.h"

Stage21::Stage21() 
{
}

Stage21::~Stage21() 
{
}

void Stage21::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* BeforeLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeLayerRenderer->SetTexture("12_3_BeforeLayer_0.png");
	BeforeLayerRenderer->ScaleToTexture();
	BeforeLayerRenderer->GetTransform().SetWorldMove({100, 0});

	GameEngineTextureRenderer* BeforeLayerRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeLayerRenderer1->SetTexture("12_3_BeforeLayer_1.png");
	BeforeLayerRenderer1->ScaleToTexture();

	Pontiff* NewPontiff = CreateActor<Pontiff>();
	NewPontiff->GetTransform().SetWorldMove({ 1250, -520 });
	BossMonster_ = NewPontiff;
	MonsterList_.push_back(NewPontiff);

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldMove({ 1250, -860 });

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("12_3_Tile.png");
	StageRenderer->ScaleToTexture();

	float OffsetX = StageRenderer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRenderer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	CameraActor_->GetTransform().SetWorldPosition({ 1250, -670 });
}

void Stage21::Start()
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	SettingStage();
}

void Stage21::Update(float _DeltaTime)
{
}


void Stage21::End()
{
}


