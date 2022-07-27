#include "PreCompile.h"
#include "Stage01.h"
#include <GameEngineCore/GameEngineTexture.h>
#include "Penitent.h"
#include "LoadingActor.h"

Stage01::Stage01() 
{
}

Stage01::~Stage01() 
{

}


void Stage01::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
	ColMap_->SetTexture("1_1_Colmap.png");
	ColMap_->ScaleToTexture();

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
	Penitent_->GetTransform().SetWorldMove({ 1225, -940 , 0.0f });
	Penitent_->SetGround(ColMap_);

	GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRenderer->SetTexture("1_1_Door.png");
	DoorRenderer->ScaleToTexture();

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("1_1_AfterLayer.png");
	AfterLayerRenderer->ScaleToTexture();

	// 레벨 체인지 스타트 추가될 때 추가
	PlayerRightPos_ = float4{ 3650, -1350 };

	float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
	float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);
}


void Stage01::Start()
{
	SettingStage();
}

void Stage01::Update(float _DeltaTime)
{
	GetMainCameraActor()->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition() + float4{0, 100});

	if (-700 < GetMainCameraActor()->GetTransform().GetWorldPosition().y)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ Penitent_->GetTransform().GetLocalPosition().x, -700 });
	}

	if (690 > GetMainCameraActor()->GetTransform().GetWorldPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 690, GetMainCameraActor()->GetTransform().GetLocalPosition().y });
	}

	if (3150 < GetMainCameraActor()->GetTransform().GetWorldPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 3150, GetMainCameraActor()->GetTransform().GetLocalPosition().y });
	}

	if (3700 < Penitent_->GetTransform().GetWorldPosition().x)
	{
		GEngine::ChangeLevel("Stage02");
	}
}

void Stage01::End()
{		
}
