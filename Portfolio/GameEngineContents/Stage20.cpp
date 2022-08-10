#include "PreCompile.h"
#include "Stage20.h"
#include "Penitent.h"
#include "Pope.h"
#include "BossUI.h"

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
	BeforePrallaxRenderer->GetTransform().SetWorldPosition({ 0, 500, static_cast<int>(ACTORORDER::BeforeParallax5) });
	BeforePrallaxRenderer->GetTransform().SetWorldScale(BeforePrallaxRenderer->GetTransform().GetWorldScale() * 1.3f);

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("12_2_Tile.png");
	StageRenderer->ScaleToTexture();
	StageRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Tile) });

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("12_2_AfterLayer.png");
	AfterLayerRenderer->ScaleToTexture();
	AfterLayerRenderer->GetTransform().SetWorldPosition({ 0, -550, static_cast<int>(ACTORORDER::AfterLayer5) });

	float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
	float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	PlayerRightPos_ = float4{ 4250, -1663, static_cast<int>(ACTORORDER::Player) };
	PlayerLeftPos_ = float4{ 400, -1663, static_cast<int>(ACTORORDER::Player) };

	IsLeftExit_ = true;
}

void Stage20::SettingMonster()
{
	Pope* NewPope = CreateActor<Pope>();
	NewPope->GetTransform().SetWorldPosition({ 1800, -1760, static_cast<int>(ACTORORDER::BossMonster) });
	NewPope->SetGround(ColMap_);
	BossMonster_ = NewPope;
}

void Stage20::Start()
{
	SettingStage();
	SettingMonster();

	BossUI_ = CreateActor<BossUI>();

	Font_ = Stage_->CreateComponent<GameEngineFontRenderer>();
	Font_->SetColor({ 0.65f, 0.65f, 0.45f, 1.0f });
	Font_->SetScreenPostion({ 450, 590, -100.f });
	Font_->SetText("에스크리바르 교황 성하", "Neo둥근모");
	Font_->SetSize(30);
	Font_->ChangeCamera(CAMERAORDER::UICAMERA);
}

void Stage20::Update(float _DeltaTime)
{
	if (false == IsChangeCameraPos_)
	{
		GetMainCameraActor()->GetTransform().SetWorldMove({ 0, 0, CameraZPos_ });
		IsChangeCameraPos_ = true;
	}

	GetMainCameraActor()->GetTransform().SetWorldPosition({ Penitent_->GetTransform().GetLocalPosition().x, -1540, CameraZPos_ });

	if (940 > GetMainCameraActor()->GetTransform().GetLocalPosition ().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 940, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_ });
	}

	if (3600 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 3600, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_ });
	}

	if (350 > Penitent_->GetTransform().GetWorldPosition().x)
	{
		Penitent_->GetTransform().SetWorldPosition(float4{ 350, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player) });
	}

	if (4350 < Penitent_->GetTransform().GetWorldPosition().x
		&& false == IsRightExit_)
	{
		IsRightExit_ = true;

		if (nullptr != LoadingActor_)
		{
			LoadingActor_->Death();
			LoadingActor_ = nullptr;
		}

		LoadingActor_ = CreateActor<LoadingActor>();
		LoadingActor_->Exit("Stage30");
	}
}

void Stage20::End()
{
}

void Stage20::OnEvent()
{
	if (nullptr == Penitent::GetMainPlayer())
	{
		Penitent_ = CreateActor<Penitent>(ACTORORDER::Player);
		Penitent_->GetTransform().SetWorldPosition(PlayerLeftPos_);
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

		else if (true == IsLeftExit_)
		{
			Penitent_->GetTransform().SetWorldPosition(PlayerLeftPos_);
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

void Stage20::OffEvent()
{
}
