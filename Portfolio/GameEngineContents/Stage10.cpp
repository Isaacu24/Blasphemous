#include "PreCompile.h"
#include "Stage10.h"
#include "Penitent.h"
#include "BreakableTwistedCorpse.h"

Stage10::Stage10()
{
}

Stage10::~Stage10()
{
}


void Stage10::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
	ColMap_->SetTexture("2_1_Colmap.png");
	ColMap_->ScaleToTexture();
	ColMap_->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::ColMap) });

	GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer->SetTexture("2_1_BeforeParallax_0.png");
	BeforeParallaxRenderer->ScaleToTexture();
	BeforeParallaxRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax0) });

	GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer1->SetTexture("2_1_BeforeParallax_1.png");
	BeforeParallaxRenderer1->ScaleToTexture();
	BeforeParallaxRenderer1->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax1) });

	GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer2->SetTexture("2_1_BeforeParallax_2.png");
	BeforeParallaxRenderer2->ScaleToTexture();
	BeforeParallaxRenderer2->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax2) });

	GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer3->SetTexture("2_1_BeforeParallax_3.png");
	BeforeParallaxRenderer3->ScaleToTexture();
	BeforeParallaxRenderer3->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax3) });

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("2_1_Tile.png");
	StageRenderer->ScaleToTexture();	
	StageRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Tile) });

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldPosition({ 300, -550, static_cast<int>(ACTORORDER::Player) });
	Penitent_->SetGround(ColMap_);

	GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRenderer->SetTexture("2_1_Door.png");
	DoorRenderer->ScaleToTexture();
	DoorRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::AfterParallax0) });
	
	float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
	float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);
}


void Stage10::Start()
{
	SettingStage();
}

void Stage10::Update(float _DeltaTime)
{
	GetMainCameraActor()->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition() + float4{0, 100});

	if (-450 < GetMainCameraActor()->GetTransform().GetLocalPosition().y)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ GetMainCameraActor()->GetTransform().GetLocalPosition().x, -450 });
	}

	if (-1680 > GetMainCameraActor()->GetTransform().GetLocalPosition().y)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ GetMainCameraActor()->GetTransform().GetLocalPosition().x, -1680 });
	}

	if (780 > GetMainCameraActor()->GetTransform().GetLocalPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 780, GetMainCameraActor()->GetTransform().GetLocalPosition().y });
	}

	if (3480 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 3480, GetMainCameraActor()->GetTransform().GetLocalPosition().y });
	}

	if (250 > Penitent_->GetTransform().GetWorldPosition().x)
	{
		GEngine::ChangeLevel("Stage05");
	}

	if (3900 < Penitent_->GetTransform().GetWorldPosition().x)
	{
		GEngine::ChangeLevel("Stage20");
	}
}

void Stage10::End()
{
}

void Stage10::OnEvent()
{
}

void Stage10::OffEvent()
{
}
