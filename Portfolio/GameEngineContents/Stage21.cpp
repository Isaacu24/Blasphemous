#include "PreCompile.h"
#include "Stage21.h"
#include "Penitent.h"
#include "Pontiff.h"
#include "GiantSword.h"

Stage21::Stage21() 
{
}

Stage21::~Stage21() 
{
}

void Stage21::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
	ColMap_->SetTexture("12_3_Colmap.png");
	ColMap_->ScaleToTexture();
	ColMap_->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::ColMap) });

	GameEngineTextureRenderer* BeforeLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeLayerRenderer->SetTexture("12_3_BeforeLayer_0.png");
	BeforeLayerRenderer->ScaleToTexture();
	BeforeLayerRenderer->GetTransform().SetWorldMove({100, 0});
	BeforeLayerRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax0) });

	GameEngineTextureRenderer* BeforeLayerRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeLayerRenderer1->SetTexture("12_3_BeforeLayer_1.png");
	BeforeLayerRenderer1->ScaleToTexture();
	BeforeLayerRenderer1->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax1) });

	Pontiff* NewPontiff = CreateActor<Pontiff>();
	NewPontiff->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Monster) });
	NewPontiff->GetTransform().SetWorldMove({ 1250, -520, 0.0f });
	BossMonster_ = NewPontiff;

	GiantSword* NewGiantSword = CreateActor<GiantSword>();
	NewGiantSword->GetTransform().SetWorldPosition({ 1250, -600 , static_cast<int>(ACTORORDER::AtherMonster) });
	BossMonster_ = NewGiantSword;

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldPosition({ 1250, -860, static_cast<int>(ACTORORDER::Player) });
	Penitent_->SetGround(ColMap_);

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("12_3_Tile.png");
	StageRenderer->ScaleToTexture();
	StageRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::AfterParallax0) });

	float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
	float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	GetMainCameraActor()->GetTransform().SetWorldPosition({1250, -670});
}

void Stage21::Start()
{
	SettingStage();
}

void Stage21::Update(float _DeltaTime)
{
	GameEngineDebug::OutPutString("x : " + std::to_string(Penitent_->GetTransform().GetLocalPosition().x));
	GameEngineDebug::OutPutString("y : " + std::to_string(Penitent_->GetTransform().GetLocalPosition().y));
}


void Stage21::End()
{
}

void Stage21::OnEvent()
{
}

void Stage21::OffEvent()
{
}


