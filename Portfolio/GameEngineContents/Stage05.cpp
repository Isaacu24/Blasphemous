#include "PreCompile.h"
#include "Stage05.h"
#include "Penitent.h"
#include "Deogracias.h"
#include "Door.h"

Stage05::Stage05()
{
}

Stage05::~Stage05()
{
}


void Stage05::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
	ColMap_->SetTexture("1_5_Colmap.png");
	ColMap_->ScaleToTexture();
	ColMap_->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::ColMap) });

	GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRenderer->SetTexture("1_5_Tile.png");
	StageRenderer->ScaleToTexture();
	StageRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Tile) });

	//Deogracias* NewDeogracias = CreateActor<Deogracias>();
	//NewDeogracias->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::) });
	//NewDeogracias->GetTransform().SetLocalMove({ 940, -570 });
	//NewDeogracias->GetTransform().PixLocalNegativeX();

	Door_ = CreateActor<Door>();
	Door_->GetTransform().SetWorldMove({ 1107, -520 });

	GameEngineTextureRenderer* DoorRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRendrer->SetTexture("1_5_Door.png");
	DoorRendrer->ScaleToTexture();
	DoorRendrer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Door) });

	float OffsetX = StageRenderer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRenderer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	GetMainCameraActor()->GetTransform().SetWorldPosition(float4{950, -500});

	PlayerRightPos_ = float4{ 1550, -674, static_cast<int>(ACTORORDER::Player) };
	PlayerLeftPos_ = float4{ 480, -674, static_cast<int>(ACTORORDER::Player) };

	IsLeftExit_ = true;
}

void Stage05::Start()
{
	SettingStage();
}

void Stage05::Update(float _DeltaTime)
{
	if (430 > Penitent_->GetTransform().GetWorldPosition().x)
	{
		IsLeftExit_ = true;
		GEngine::ChangeLevel("Stage04");
	}

	if (1600 < Penitent_->GetTransform().GetWorldPosition().x)
	{
		IsRightExit_ = true;
		GEngine::ChangeLevel("Stage10");
	}

	GameEngineDebug::OutPutString("x : " + std::to_string(Penitent_->GetTransform().GetLocalPosition().x));
}

void Stage05::End()
{
}

void Stage05::OnEvent()
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
}

void Stage05::OffEvent()
{
}
