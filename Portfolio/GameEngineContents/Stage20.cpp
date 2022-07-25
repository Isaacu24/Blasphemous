#include "PreCompile.h"
#include "Stage20.h"
#include "Penitent.h"
#include "Pope.h"

Stage20::Stage20() 
{
}

Stage20::~Stage20() 
{
}


void Stage20::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* BeforePrallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforePrallaxRenderer->SetTexture("12_2_BeforeParallax_0.png");

	BeforePrallaxRenderer->ScaleToTexture();
	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("12_2_Tile.png");
	StageRenderer->ScaleToTexture();

	Pope* NewPope = CreateActor<Pope>();
	NewPope->GetTransform().SetWorldMove({ 1750, -1660, 0.0f });
	BossMonster_ = NewPope;
	MonsterList_.push_back(NewPope);

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldMove({ 300, -1650, 0.0f });

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("12_2_AfterLayer.png");
	AfterLayerRenderer->ScaleToTexture();

	float OffsetX = StageRenderer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRenderer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);
}

void Stage20::Start()                                                     
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	SettingStage();
}

void Stage20::Update(float _DeltaTime)
{
	CameraActor_->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition() + float4{ 0, 0 });

	if (-1510 < CameraActor_->GetTransform().GetLocalPosition().x)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ CameraActor_->GetTransform().GetLocalPosition().x, -1510 });
	}

	if (940 > CameraActor_->GetTransform().GetLocalPosition().x)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ 940, CameraActor_->GetTransform().GetLocalPosition().y });
	}

	if (3600 < CameraActor_->GetTransform().GetLocalPosition().x)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ 3600, CameraActor_->GetTransform().GetLocalPosition().y });
	}

	GameEngineDebug::OutPutString("x : " + std::to_string(CameraActor_->GetTransform().GetLocalPosition().x));
	GameEngineDebug::OutPutString("y : " + std::to_string(CameraActor_->GetTransform().GetLocalPosition().y));

	if (4300 < Penitent_->GetTransform().GetWorldPosition().x)
	{
		GEngine::ChangeLevel("Stage30");
	}
}

void Stage20::End()
{
}
