#include "PreCompile.h"
#include "Stage02.h"
#include "Penitent.h"

Stage02::Stage02() 
{
}

Stage02::~Stage02() 
{
}

void Stage02::SettingStage()
{
	Stage_ = CreateActor<StageActor>();

	GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer->SetTexture("1_2_BeforeParallax_0.png");
	BeforeParallaxRenderer->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer1->SetTexture("1_2_BeforeParallax_1.png");
	BeforeParallaxRenderer1->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer2->SetTexture("1_2_BeforeParallax_2.png");
	BeforeParallaxRenderer2->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer3->SetTexture("1_2_BeforeParallax_3.png");
	BeforeParallaxRenderer3->ScaleToTexture();

	GameEngineTextureRenderer* BeforeParallaxRenderer4 = Stage_->CreateComponent<GameEngineTextureRenderer>();
	BeforeParallaxRenderer4->SetTexture("1_2_BeforeParallax_4.png");
	BeforeParallaxRenderer4->ScaleToTexture();

	GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	StageRendrer->SetTexture("1_2_Tile.png");
	StageRendrer->ScaleToTexture();

	Penitent_ = CreateActor<Penitent>();
	Penitent_->GetTransform().SetWorldMove({ 205, -1285 });

	GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	DoorRenderer->SetTexture("1_2_Door.png");
	DoorRenderer->ScaleToTexture();

	GameEngineTextureRenderer* AfterParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
	AfterParallaxRenderer->SetTexture("1_2_AfterParallax_0.png");
	AfterParallaxRenderer->ScaleToTexture();

	float OffsetX = StageRendrer->GetTransform().GetLocalScale().x / 2;
	float OffsetY = StageRendrer->GetTransform().GetLocalScale().y / 2;

	float4 Offset = { OffsetX , -OffsetY };

	Stage_->GetTransform().SetLocalMove(Offset);

}

void Stage02::Start()
{
	CameraActor_ = CreateActor<GameEngineCameraActor>();
	CameraActor_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	SettingStage();

	CameraActor_->GetTransform().SetWorldPosition(Penitent_->GetTransform().GetLocalPosition());
}

void Stage02::Update(float _DeltaTime)
{
	CameraActor_->GetTransform().SetWorldPosition(float4{ Penitent_->GetTransform().GetLocalPosition().x, -1250 });

	if (640 > CameraActor_->GetTransform().GetLocalPosition().x)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ 640, -1250 });
	}

	if (3200 < CameraActor_->GetTransform().GetLocalPosition().x)
	{
		CameraActor_->GetTransform().SetWorldPosition(float4{ 3200, -1250 });
	}

	GameEngineDebug::OutPutString("x : " + std::to_string(CameraActor_->GetTransform().GetLocalPosition().x));
	GameEngineDebug::OutPutString("y : " + std::to_string(CameraActor_->GetTransform().GetLocalPosition().y));
}

void Stage02::End()
{

}