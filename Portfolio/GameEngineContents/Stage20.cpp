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
	BeforePrallaxRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax5) });
	Parallaxs_.push_back(BeforePrallaxRenderer);

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("12_2_Tile.png");
	StageRenderer->ScaleToTexture();
	StageRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Tile) });

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("12_2_AfterLayer.png");
	AfterLayerRenderer->ScaleToTexture();
	AfterLayerRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::AfterParallax0) });

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
}

void Stage20::Update(float _DeltaTime)
{
	PrevPos_ = CurPos_;
	CurPos_ = GetMainCameraActor()->GetTransform().GetWorldPosition();

	float4 Dir = CurPos_ - PrevPos_;

	MoveParallax(Dir, _DeltaTime);

	GetMainCameraActor()->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition() + float4{ 0, 0 });

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

	if (350 > Penitent_->GetTransform().GetWorldPosition().x)
	{
		Penitent_->GetTransform().SetWorldPosition(float4{ 350, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player) });
	}

	if (4350 < Penitent_->GetTransform().GetWorldPosition().x)
	{
		IsRightExit_ = true;
		GEngine::ChangeLevel("Stage30");
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

	IsRightExit_ = false;
	IsLeftExit_ = false;

	GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ Penitent_->GetTransform().GetLocalPosition() + float4{0, 100} });
}

void Stage20::OffEvent()
{
}
