#include "PreCompile.h"
#include "Stage21.h"
#include "Penitent.h"
#include "Pontiff.h"
#include "GiantSword.h"
#include "Platform.h"

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
	BeforeLayerRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeLayer0) });

	GameEngineTextureRenderer* BeforeLayerRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeLayerRenderer1->SetTexture("12_3_BeforeLayer_1.png");
	BeforeLayerRenderer1->ScaleToTexture();
	BeforeLayerRenderer1->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeLayer2) });

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("12_3_Tile.png");
	StageRenderer->ScaleToTexture();
	StageRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::AfterLayer0) });

	float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
	float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	Platform* NewPlatform = CreateActor<Platform>();
	NewPlatform->GetTransform().SetWorldPosition({ 1250, -600 , static_cast<int>(ACTORORDER::AfterLayer5) });
	NewPlatform->GetTransform().SetWorldScale({2, 2});

	GetMainCameraActor()->GetTransform().SetWorldPosition({ 1250, -670 });
}

void Stage21::SettingMonster()
{
	Pontiff* NewPontiff = CreateActor<Pontiff>();
	NewPontiff->GetTransform().SetWorldPosition({ 1250, -520, static_cast<int>(ACTORORDER::BeforeLayer1) });
	BossMonster_ = NewPontiff;

	GiantSword* NewGiantSword = CreateActor<GiantSword>();
	NewGiantSword->GetTransform().SetWorldPosition({ 1250, -600 , static_cast<int>(ACTORORDER::BossMonster) });
	BossMonster_ = NewGiantSword;
}

void Stage21::Start()
{
	SettingStage();
	SettingMonster();
}

void Stage21::Update(float _DeltaTime)
{
	if (false == IsChangeCameraPos_)
	{
		GetMainCameraActor()->GetTransform().SetWorldMove({ 0, 0, CameraZPos_ });
		IsChangeCameraPos_ = true;
	}

	GameEngineDebug::OutPutString("x : " + std::to_string(Penitent_->GetTransform().GetLocalPosition().x));
	GameEngineDebug::OutPutString("y : " + std::to_string(Penitent_->GetTransform().GetLocalPosition().y));
}


void Stage21::End()
{
}

void Stage21::OnEvent()
{
	if (nullptr == Penitent::GetMainPlayer())
	{
		Penitent_ = CreateActor<Penitent>(ACTORORDER::Player);
		Penitent_->GetTransform().SetWorldPosition({ 1250, -860, static_cast<int>(ACTORORDER::Player) });
		Penitent_->SetGround(ColMap_);

		Penitent_->SetLevelOverOn();
	}

	else if (nullptr != Penitent::GetMainPlayer())
	{
		Penitent_ = Penitent::GetMainPlayer();
		Penitent_->GetTransform().SetWorldPosition({ 1250, -860, static_cast<int>(ACTORORDER::Player) });
		Penitent_->SetGround(ColMap_);

		Penitent_->SetLevelOverOn();
	}

	if (350 > Penitent_->GetTransform().GetWorldPosition().x)
	{
		Penitent_->GetTransform().SetWorldPosition(float4{ 350, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player) });
	}

	if (2000 < Penitent_->GetTransform().GetWorldPosition().x)
	{
		Penitent_->GetTransform().SetWorldPosition(float4{ 2000, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player) });
	}

	IsRightExit_ = false;
	IsLeftExit_ = false;
}

void Stage21::OffEvent()
{
}


