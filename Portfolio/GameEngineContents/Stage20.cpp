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

	ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
	ColMap_->SetTexture("12_2_Colmap.png");
	ColMap_->ScaleToTexture();
	ColMap_->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::ColMap) });

	GameEngineTextureRenderer* BeforePrallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforePrallaxRenderer->SetTexture("12_2_BeforeParallax_0.png");
	BeforePrallaxRenderer->ScaleToTexture();
	BeforePrallaxRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax0) });

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("12_2_Tile.png");
	StageRenderer->ScaleToTexture();
	StageRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Tile) });

	Pope* NewPope = CreateActor<Pope>();
	BossMonster_ = NewPope;
	NewPope->GetTransform().SetWorldPosition({ 1750, -1660, static_cast<int>(ACTORORDER::Monster) });

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldPosition({ 300,-1650, static_cast<int>(ACTORORDER::Player) });
	Penitent_->SetGround(ColMap_);

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("12_2_AfterLayer.png");
	AfterLayerRenderer->ScaleToTexture();
	AfterLayerRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::AfterParallax0) });

	float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
	float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);
}

void Stage20::Start()                                                     
{
	SettingStage();
}

void Stage20::Update(float _DeltaTime)
{
	GetMainCameraActor()->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition() + float4{0, 0});

	if (-1510 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ GetMainCameraActor()->GetTransform().GetLocalPosition().x, -1510 });
	}

	if (940 > GetMainCameraActor()->GetTransform().GetLocalPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 940, GetMainCameraActor()->GetTransform().GetLocalPosition().y });
	}

	if (3600 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 3600, GetMainCameraActor()->GetTransform().GetLocalPosition().y });
	}
	
	if (4300 < Penitent_->GetTransform().GetWorldPosition().x)
	{
		GEngine::ChangeLevel("Stage30");
	}
}

void Stage20::End()
{
}

void Stage20::OnEvent()
{
}

void Stage20::OffEvent()
{
}
