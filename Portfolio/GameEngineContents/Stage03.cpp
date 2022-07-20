#include "PreCompile.h"
#include "Stage03.h"
#include "Penitent.h"

Stage03::Stage03() 
{
}

Stage03::~Stage03() 
{
}

void Stage03::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer->SetTexture("1_3_BeforeParallax_0.png");
	BeforeParallaxRenderer->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer1->SetTexture("1_3_BeforeParallax_1.png");
	BeforeParallaxRenderer1->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer2->SetTexture("1_2_BeforeParallax_2.png");
	BeforeParallaxRenderer2->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer3->SetTexture("1_3_BeforeParallax_3.png");
	BeforeParallaxRenderer3->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer4 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer4->SetTexture("1_3_BeforeParallax_4.png");
	BeforeParallaxRenderer4->ScaleToTexture();

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->SetTexture("1_3_Tile.png");
	StageRendrer->ScaleToTexture();

	GameEngineTextureRenderer* AltarRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AltarRenderer->SetTexture("penitences-altar-off.png");
	AltarRenderer->ScaleToTexture();
	AltarRenderer->GetTransform().SetWorldMove({ 780, 0 });

	GameEngineTextureRenderer* SavePointRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	SavePointRenderer->CreateFrameAnimation("priedieu_stand_and_liton_anim", { "priedieu_stand_and_liton_anim.png", 0, 6, 0.1f, true });
	SavePointRenderer->ChangeFrameAnimation("priedieu_stand_and_liton_anim");
	SavePointRenderer->GetTransform().SetLocalScale({ 100, 250 });
	SavePointRenderer->GetTransform().SetWorldMove({ 100, -100 });

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldMove({ 237, -960 });

	GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRenderer->SetTexture("1_3_Door.png");
	DoorRenderer->ScaleToTexture();

	GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterLayerRenderer->SetTexture("1_3_AfterLayer_0.png");
	AfterLayerRenderer->ScaleToTexture();

	GameEngineTextureRenderer* AfterParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterParallaxRenderer->SetTexture("1_3_AfterParallax_0.png");
	AfterParallaxRenderer->ScaleToTexture();

	float OffsetX = StageRendrer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRendrer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);
}

void Stage03::Start()
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	SettingStage();
}

void Stage03::Update(float _DeltaTime)
{
	CameraActor_->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition() + float4{ 0, 100 });
}


void Stage03::End()
{
}
