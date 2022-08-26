#include "PreCompile.h"
#include "Stage04.h"
#include "Penitent.h"
#include "ElderBrother.h"

Stage04::Stage04() {}

Stage04::~Stage04() {}

void Stage04::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("1_4_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::ColMap)});

    GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer->SetTexture("1_4_BeforeParallax_0.png");
    BeforeParallaxRenderer->ScaleToTexture();
    BeforeParallaxRenderer->GetTransform().SetWorldPosition({200, 200, static_cast<int>(ACTORORDER::BeforeParallax0)});
    BeforeParallaxRenderer->GetTransform().SetWorldScale(BeforeParallaxRenderer->GetTransform().GetWorldScale() * 3.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer1->SetTexture("1_4_BeforeParallax_1.png");
    BeforeParallaxRenderer1->ScaleToTexture();
    BeforeParallaxRenderer1->GetTransform().SetWorldPosition(
        {-300, 500, static_cast<int>(ACTORORDER::BeforeParallax1)});
    BeforeParallaxRenderer1->GetTransform().SetWorldScale(BeforeParallaxRenderer1->GetTransform().GetWorldScale()
                                                          * 3.25f);

    GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer2->SetTexture("1_4_BeforeParallax_2.png");
    BeforeParallaxRenderer2->ScaleToTexture();
    BeforeParallaxRenderer2->GetTransform().SetWorldPosition({0, 30, static_cast<int>(ACTORORDER::BeforeParallax2)});
    BeforeParallaxRenderer2->GetTransform().SetWorldScale(BeforeParallaxRenderer2->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer3->SetTexture("1_4_BeforeParallax_3.png");
    BeforeParallaxRenderer3->ScaleToTexture();
    BeforeParallaxRenderer3->GetTransform().SetWorldPosition({50, -220, static_cast<int>(ACTORORDER::BeforeParallax3)});
    BeforeParallaxRenderer3->GetTransform().SetWorldScale(BeforeParallaxRenderer3->GetTransform().GetWorldScale()
                                                          * 2.5f);

    GameEngineTextureRenderer* BeforeParallaxRenderer4 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer4->SetTexture("1_4_BeforeParallax_4.png");
    BeforeParallaxRenderer4->ScaleToTexture();
    BeforeParallaxRenderer4->GetTransform().SetWorldPosition({50, -400, static_cast<int>(ACTORORDER::BeforeParallax4)});
    BeforeParallaxRenderer4->GetTransform().SetWorldScale(BeforeParallaxRenderer4->GetTransform().GetWorldScale()
                                                          * 2.5f);

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("1_4_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Tile)});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRenderer->SetTexture("1_4_Door.png");
    DoorRenderer->ScaleToTexture();
    DoorRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Door)});
    DoorRenderer->GetTransform().SetWorldScale(DoorRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterLayerRenderer->SetTexture("1_4_AfterLayer_0.png");
    AfterLayerRenderer->ScaleToTexture();
    AfterLayerRenderer->GetTransform().SetWorldPosition({0, -400, static_cast<int>(ACTORORDER::AfterLayer0)});
    AfterLayerRenderer->GetTransform().SetWorldScale(AfterLayerRenderer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{2750, -1028, static_cast<int>(ACTORORDER::Player)};
    PlayerLeftPos_  = float4{250, -1028, static_cast<int>(ACTORORDER::Player)};

    IsLeftExit_ = true;
}

void Stage04::SettingMonster()
{
    ElderBrother_ = CreateActor<ElderBrother>();
    ElderBrother_->GetTransform().SetWorldPosition({2300, -1200, static_cast<int>(ACTORORDER::BeforeParallax2)});
    ElderBrother_->SetGround(ColMap_);
    BossMonster_ = ElderBrother_;
}

void Stage04::Start()
{
    SettingStage();
    SettingMonster();
}

void Stage04::Update(float _DeltaTime)
{
    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }

    StageFlowUpdate(_DeltaTime);
}

void Stage04::BossStateCheck()
{
    if (nullptr == BossMonster_)
    {
        return;
    }
}


void Stage04::End() {}

void Stage04::StageFlowUpdate(float _DeltaTime)
{
    switch (CurrentFlow_)
    {
        case STAGEFLOW::NORMAL:
            PlayerCameraMove();

            if (1300 < Penitent_->GetTransform().GetWorldPosition().x)
            {
                Penitent_->ChangeState("Freeze");
                ElderBrother_->EventOn();

                CurrentFlow_ = STAGEFLOW::BOSSAPPEAR;
            }
            break;
        case STAGEFLOW::BOSSAPPEAR:
            GetMainCameraActor()->GetTransform().SetWorldRightMove(50.f, _DeltaTime);

            if (true == ElderBrother_->GetBossEvent())
            {
                Penitent_->ChangeState("Idle");

                Font_ = Stage_->CreateComponent<GameEngineFontRenderer>();
                Font_->SetColor({0.65f, 0.65f, 0.45f, 1.0f});
                Font_->SetScreenPostion({450, 590, -100.f});
                Font_->SetText("Ä§¹¬ÇÏ´Â ºñÅºÀÇ ÆÄ¼ö²Û", "NeoµÕ±Ù¸ð");
                Font_->SetSize(30);
                Font_->ChangeCamera(CAMERAORDER::UICAMERA);

                CurrentFlow_ = STAGEFLOW::BOSSCOMBAT;
            }
            break;
        case STAGEFLOW::BOSSCOMBAT:
            PlayerCameraMove();

            if (400 > Penitent_->GetTransform().GetWorldPosition().x)
            {
                Penitent_->GetTransform().SetWorldPosition(
                    float4{400, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player)});
            }

            else if (2500 < Penitent_->GetTransform().GetWorldPosition().x)
            {
                Penitent_->GetTransform().SetWorldPosition(
                    float4{2500, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player)});
            }


            if (1000 > GetMainCameraActor()->GetTransform().GetLocalPosition().x)
            {
                GetMainCameraActor()->GetTransform().SetWorldPosition(
                    float4{1000, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
            }

            if (1850 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
            {
                GetMainCameraActor()->GetTransform().SetWorldPosition(
                    float4{1850, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
            }

            break;
        case STAGEFLOW::BOSSDEAD:
            PlayerCameraMove();
            break;
        default:
            PlayerCameraMove();
            break;
    }
}

void Stage04::LevelStartEvent()
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
    IsLeftExit_  = false;

    GetMainCameraActor()->GetTransform().SetWorldPosition(float4{
        Penitent_->GetTransform().GetLocalPosition() + float4{0, CameraOffset_}
    });
}

void Stage04::LevelEndEvent() {}

void Stage04::PlayerCameraMove()
{
    GetMainCameraActor()->GetTransform().SetWorldPosition(
        {Penitent_->GetTransform().GetLocalPosition().x,
         Penitent_->GetTransform().GetLocalPosition().y + CameraOffset_,
         CameraZPos_});

    if (-700 < GetMainCameraActor()->GetTransform().GetLocalPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{GetMainCameraActor()->GetTransform().GetLocalPosition().x, -700, CameraZPos_});
    }

    if (700 > GetMainCameraActor()->GetTransform().GetLocalPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{700, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (2200 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{2200, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (200 > Penitent_->GetTransform().GetWorldPosition().x && false == IsLeftExit_)
    {
        IsLeftExit_ = true;

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage03");
    }

    if (2800 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage05");
    }
}
