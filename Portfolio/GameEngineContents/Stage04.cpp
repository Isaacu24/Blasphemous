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

	ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
	ColMap_->SetTexture("1_4_Colmap.png");
	ColMap_->ScaleToTexture();
	ColMap_->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::ColMap) });

	GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer->SetTexture("1_4_BeforeParallax_0.png");
	BeforeParallaxRenderer->ScaleToTexture();
	BeforeParallaxRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax0) });

	GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer1->SetTexture("1_4_BeforeParallax_1.png");
	BeforeParallaxRenderer1->ScaleToTexture();
	BeforeParallaxRenderer1->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax1) });


	GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer2->SetTexture("1_4_BeforeParallax_2.png");
	BeforeParallaxRenderer2->ScaleToTexture();
	BeforeParallaxRenderer2->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax2) });


	GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer3->SetTexture("1_4_BeforeParallax_3.png");
	BeforeParallaxRenderer3->ScaleToTexture();
	BeforeParallaxRenderer3->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax3) });

	GameEngineTextureRenderer* BeforeParallaxRenderer4 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer4->SetTexture("1_4_BeforeParallax_4.png");
	BeforeParallaxRenderer4->ScaleToTexture();
	BeforeParallaxRenderer4->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax4) });

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("1_4_Tile.png");
	StageRenderer->ScaleToTexture();
	StageRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Tile) });

	ElderBrother* NewElderBrother = CreateActor<ElderBrother>();
	NewElderBrother->GetTransform().SetWorldPosition({ 2000, -800, static_cast<int>(ACTORORDER::Monster) });
	NewElderBrother->GetTransform().SetLocalScale({ 1500, 750 });
	NewElderBrother->GetTransform().PixLocalNegativeX();

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldPosition({ 300, 1000, static_cast<int>(ACTORORDER::Player) });
	Penitent_->SetGround(ColMap_);

	GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRenderer->SetTexture("1_4_Door.png");
	DoorRenderer->ScaleToTexture();
	DoorRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Door) });

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("1_4_AfterLayer_0.png");
	AfterLayerRenderer->ScaleToTexture();
	AfterLayerRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::AfterParallax0) });

	float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
	float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);
}


void Stage04::Start()
{
	SettingStage();
}

void Stage04::Update(float _DeltaTime)
{
	GetMainCameraActor()->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition() + float4{0, 100});

	if (-700 < GetMainCameraActor()->GetTransform().GetLocalPosition().y)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ GetMainCameraActor()->GetTransform().GetLocalPosition().x, -700 });
	}

	if (650 > GetMainCameraActor()->GetTransform().GetLocalPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 650, GetMainCameraActor()->GetTransform().GetLocalPosition().y });
	}

	if (2300 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 2300, GetMainCameraActor()->GetTransform().GetLocalPosition().y });
	}

	if (200 > Penitent_->GetTransform().GetWorldPosition().x)
	{
		GEngine::ChangeLevel("Stage03");
	}

	if (2500 < Penitent_->GetTransform().GetWorldPosition().x)
	{
		GEngine::ChangeLevel("Stage05");
	}
}

void Stage04::End()
{
}

void Stage04::OnEvent()
{
}

void Stage04::OffEvent()
{
}
