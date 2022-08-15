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

	ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
	ColMap_->SetTexture("1_1_Colmap.png");
	ColMap_->ScaleToTexture();
	ColMap_->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::ColMap) });

	GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer->SetTexture("1_1_BeforeParallax_0.png");
	BeforeParallaxRenderer->ScaleToTexture();
	BeforeParallaxRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax0)});
	BeforeParallaxRenderer->GetTransform().SetWorldScale(BeforeParallaxRenderer->GetTransform().GetWorldScale() * 2.5f);

	GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer1->SetTexture("1_1_BeforeParallax_1.png");
	BeforeParallaxRenderer1->ScaleToTexture();
	BeforeParallaxRenderer1->GetTransform().SetWorldPosition({ -100, 1000, static_cast<int>(ACTORORDER::BeforeParallax1)});
	BeforeParallaxRenderer1->GetTransform().SetWorldScale(BeforeParallaxRenderer1->GetTransform().GetWorldScale() * 3.0f);

	GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer2->SetTexture("1_1_BeforeParallax_2.png");
	BeforeParallaxRenderer2->ScaleToTexture();
	BeforeParallaxRenderer2->GetTransform().SetWorldPosition({ 100, 100, static_cast<int>(ACTORORDER::BeforeParallax2)});
	BeforeParallaxRenderer2->GetTransform().SetWorldScale(BeforeParallaxRenderer2->GetTransform().GetWorldScale() * 2.5f);

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("1_1_Tile.png");
	StageRenderer->ScaleToTexture();
	StageRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Tile) });
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

	GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRenderer->SetTexture("1_1_Door.png");
	DoorRenderer->ScaleToTexture();
	DoorRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Door) });
    DoorRenderer->GetTransform().SetWorldScale(DoorRenderer->GetTransform().GetWorldScale() * 2.f);

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("1_1_AfterLayer.png");
	AfterLayerRenderer->ScaleToTexture();
	AfterLayerRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::AfterLayer0) });
    AfterLayerRenderer->GetTransform().SetWorldScale(AfterLayerRenderer->GetTransform().GetWorldScale()
                                                                  * 2.f);

	float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
	float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	PlayerRightPos_ = float4{ 3600, -1730, static_cast<int>(ACTORORDER::Player) };
}

void Stage01::Start()
{
	SettingStage();
}

void Stage01::Update(float _DeltaTime)
{
	if (false == IsChangeCameraPos_)
	{
		GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
		IsChangeCameraPos_ = true;
	}

	GetMainCameraActor()->GetTransform().SetWorldPosition({ Penitent_->GetTransform().GetLocalPosition().x, Penitent_->GetTransform().GetLocalPosition().y + CameraOffset_, CameraZPos_ });

	if (-700 < GetMainCameraActor()->GetTransform().GetWorldPosition().y)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ Penitent_->GetTransform().GetLocalPosition().x, -700, CameraZPos_ });
	}

	if (690 > GetMainCameraActor()->GetTransform().GetWorldPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 690, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_ });
	}

	if (3150 < GetMainCameraActor()->GetTransform().GetWorldPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 3150, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_ });
	}

	if (3650 < Penitent_->GetTransform().GetWorldPosition().x
		&& false == IsRightExit_)
	{
		IsRightExit_ = true;

		if (nullptr != LoadingActor_)
		{
			LoadingActor_->Death();
			LoadingActor_ = nullptr;
		}

		LoadingActor_ = CreateActor<LoadingActor>();
		LoadingActor_->Exit("Stage02");
	}
}

void Stage01::End()
{		
}

void Stage01::OnEvent()
{
	if (nullptr == Penitent::GetMainPlayer())
	{
		Penitent_ = CreateActor<Penitent>();
		Penitent_->GetTransform().SetWorldPosition({ 1230, -940 , static_cast<int>(ACTORORDER::Player) });
		Penitent_->SetGround(ColMap_);

		Penitent_->SetLevelOverOn();
	}

	else if (nullptr != Penitent::GetMainPlayer())
	{
		Penitent_ = Penitent::GetMainPlayer();
		Penitent_->SetGround(ColMap_);

		if (true == IsRightExit_)
		{
			Penitent_->GetTransform().SetWorldPosition(PlayerRightPos_);
		}

		else
		{
			Penitent_->GetTransform().SetWorldPosition({ 1230, -940 , static_cast<int>(ACTORORDER::Player) });
		}

		Penitent_->SetLevelOverOn();
	}

	if (nullptr == LoadingActor_)
	{
		LoadingActor_ = CreateActor<LoadingActor>();
		LoadingActor_->IsEntrance(true);
	}

	else if (nullptr != LoadingActor_)
	{
		LoadingActor_->Death();
		LoadingActor_ = nullptr;

		LoadingActor_ = CreateActor<LoadingActor>();
		LoadingActor_->IsEntrance(true);
	}

	IsRightExit_ = false;
	IsLeftExit_ = false;

	GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ Penitent_->GetTransform().GetLocalPosition() + float4{0, CameraOffset_} });
}

void Stage01::OffEvent()
{
}
