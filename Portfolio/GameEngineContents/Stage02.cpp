#include "PreCompile.h"
#include "Stage02.h"
#include "Penitent.h"
#include "Fool_knife.h"
#include "WingedFace.h"

Stage02::Stage02() 
{
}

Stage02::~Stage02() 
{
}

void Stage02::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
	ColMap_->SetTexture("1_2_Colmap.png");
	ColMap_->ScaleToTexture();
	ColMap_->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::ColMap) });

	GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer->SetTexture("1_2_BeforeParallax_0.png");
	BeforeParallaxRenderer->ScaleToTexture();
	BeforeParallaxRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax0) });
	Parallaxs_.push_back(BeforeParallaxRenderer);

	GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer1->SetTexture("1_2_BeforeParallax_1.png");
	BeforeParallaxRenderer1->ScaleToTexture();
	BeforeParallaxRenderer1->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax1) });
	Parallaxs_.push_back(BeforeParallaxRenderer1);

	GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer2->SetTexture("1_2_BeforeParallax_2.png");
	BeforeParallaxRenderer2->ScaleToTexture();
	BeforeParallaxRenderer2->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax2) });
	Parallaxs_.push_back(BeforeParallaxRenderer2);

	GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer3->SetTexture("1_2_BeforeParallax_3.png");
	BeforeParallaxRenderer3->ScaleToTexture();
	BeforeParallaxRenderer3->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax3) });
	Parallaxs_.push_back(BeforeParallaxRenderer3);

	GameEngineTextureRenderer* BeforeParallaxRenderer4 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer4->SetTexture("1_2_BeforeParallax_4.png");
	BeforeParallaxRenderer4->ScaleToTexture();
	BeforeParallaxRenderer4->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::BeforeParallax4) });
	Parallaxs_.push_back(BeforeParallaxRenderer4);

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->SetTexture("1_2_Tile.png");
	StageRendrer->ScaleToTexture();
	StageRendrer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Tile) });

	GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRenderer->SetTexture("1_2_Door.png");
	DoorRenderer->ScaleToTexture();
	DoorRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Door) });

	GameEngineTextureRenderer* AfterParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterParallaxRenderer->SetTexture("1_2_AfterParallax_0.png");
	AfterParallaxRenderer->ScaleToTexture();
	AfterParallaxRenderer->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::AfterParallax0) });
	Parallaxs_.push_back(AfterParallaxRenderer);

	float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
	float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

	PlayerRightPos_ = float4{ 4050, -1561, static_cast<int>(ACTORORDER::Player) };
	PlayerLeftPos_ = float4{ 210, -1425, static_cast<int>(ACTORORDER::Player) };

	IsLeftExit_ = true;
}

void Stage02::SettingMonster()
{
	Fool_knife* FoolKnife = CreateActor<Fool_knife>();
	FoolKnife->GetTransform().SetWorldPosition({ 1300, -1289, static_cast<int>(ACTORORDER::Monster) });
	FoolKnife->SetGround(ColMap_);
	MonsterList_.push_back(FoolKnife);

	WingedFace* FlyingEnemy = CreateActor<WingedFace>();
	FlyingEnemy->GetTransform().SetWorldPosition({ 2150, -1250, static_cast<int>(ACTORORDER::Monster) });
	FlyingEnemy->SetGround(ColMap_);
	FlyingEnemy->SetStartPos(-1150);
	FlyingEnemy->SetEndPos(-1550);
	FlyingEnemy->GetTransform().SetWorldScale({2, 2});
	MonsterList_.push_back(FlyingEnemy);

	//Crosscrawler* NewCrosscrawler = CreateActor<Crosscrawler>();
	//NewCrosscrawler->GetTransform().SetWorldPosition({ 1050, -1250, static_cast<int>(ACTORORDER::Monster) });
	//NewCrosscrawler->SetGround(ColMap_);
	//NewCrosscrawler->GetTransform().SetWorldScale({ 2, 2 });
	//MonsterList_.push_back(FlyingEnemy);
}

void Stage02::Start()
{
	SettingStage();
	SettingMonster();
}

void Stage02::Update(float _DeltaTime)
{
	PrevPos_ = CurPos_;
	CurPos_ = GetMainCameraActor()->GetTransform().GetWorldPosition();

	float4 Dir = CurPos_ - PrevPos_;

	MoveParallax(Dir, _DeltaTime);

	GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ Penitent_->GetTransform().GetLocalPosition() + float4{0, 100} });

	if (-1285 < GetMainCameraActor()->GetTransform().GetWorldPosition().y)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ Penitent_->GetTransform().GetLocalPosition().x, -1285 });
	}

	if (640 > GetMainCameraActor()->GetTransform().GetWorldPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 640, GetMainCameraActor()->GetTransform().GetLocalPosition().y });
	}

	if (3550 < GetMainCameraActor()->GetTransform().GetWorldPosition().x)
	{
		GetMainCameraActor()->GetTransform().SetWorldPosition(float4{ 3550, GetMainCameraActor()->GetTransform().GetLocalPosition().y });
	}

	if (150 > Penitent_->GetTransform().GetWorldPosition().x)
	{
		IsLeftExit_ = true;
		GEngine::ChangeLevel("Stage01");
	}

	if (4100 < Penitent_->GetTransform().GetWorldPosition().x)
	{
		IsRightExit_ = true;
		GEngine::ChangeLevel("Stage03");
	}
}

void Stage02::End()
{

}

void Stage02::OnEvent()
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

void Stage02::OffEvent()
{
}
