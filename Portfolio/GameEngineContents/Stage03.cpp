#include "PreCompile.h"
#include "Stage03.h"
#include "Penitent.h"
#include "PrieDieu.h"

Stage03::Stage03() {}

Stage03::~Stage03() {}

void Stage03::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("1_3_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, ColmapZ});

    GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer->SetTexture("1_3_BeforeParallax_0.png");
    BeforeParallaxRenderer->ScaleToTexture();
    BeforeParallaxRenderer->GetTransform().SetWorldPosition({0, 300, BeforeParallaxZ});
    BeforeParallaxRenderer->GetTransform().SetWorldScale(BeforeParallaxRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer1->SetTexture("1_3_BeforeParallax_1.png");
    BeforeParallaxRenderer1->ScaleToTexture();
    BeforeParallaxRenderer1->GetTransform().SetWorldPosition({0, 300, BeforeParallax1Z});
    BeforeParallaxRenderer1->GetTransform().SetWorldScale(BeforeParallaxRenderer1->GetTransform().GetWorldScale()
                                                          * 2.2f);

    GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer2->SetTexture("1_2_BeforeParallax_2.png");
    BeforeParallaxRenderer2->ScaleToTexture();
    BeforeParallaxRenderer2->GetTransform().SetWorldPosition({150, 0, BeforeParallax2Z});
    BeforeParallaxRenderer2->GetTransform().SetWorldScale(BeforeParallaxRenderer2->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer3->SetTexture("1_3_BeforeParallax_3.png");
    BeforeParallaxRenderer3->ScaleToTexture();
    BeforeParallaxRenderer3->GetTransform().SetWorldPosition({150, 150, BeforeParallax3Z});
    BeforeParallaxRenderer3->GetTransform().SetWorldScale(BeforeParallaxRenderer3->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer4 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer4->SetTexture("1_3_BeforeParallax_4.png");
    BeforeParallaxRenderer4->ScaleToTexture();
    BeforeParallaxRenderer4->GetTransform().SetWorldPosition({150, -160, BeforeParallax4Z});
    BeforeParallaxRenderer4->GetTransform().SetWorldScale(BeforeParallaxRenderer4->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRendrer->SetTexture("1_3_Tile.png");
    StageRendrer->ScaleToTexture();
    StageRendrer->GetTransform().SetWorldPosition({0, 0, TileZ});
    StageRendrer->GetTransform().SetWorldScale(StageRendrer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AltarRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AltarRenderer->SetTexture("penitences-altar-off.png");
    AltarRenderer->ScaleToTexture();
    AltarRenderer->GetTransform().SetWorldPosition({0, 0, ObjectZ});
    AltarRenderer->GetTransform().SetWorldMove({820, -20});

    PrieDieu_ = CreateActor<PrieDieu>();
    PrieDieu_->GetTransform().SetWorldPosition({0, 0, ObjectZ});
    PrieDieu_->GetTransform().SetWorldMove({1800, -1000});

    Lantern* NewLantern = CreateActor<Lantern>();
    NewLantern->GetTransform().SetWorldPosition({0, 0, ObjectZ});
    NewLantern->GetTransform().SetWorldMove({2840, -900});

    GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRenderer->SetTexture("1_3_Door.png");
    DoorRenderer->ScaleToTexture();
    DoorRenderer->GetTransform().SetWorldPosition({0, 0, DoorZ});
    DoorRenderer->GetTransform().SetWorldScale(DoorRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterLayerRenderer->SetTexture("1_3_AfterLayer_0.png");
    AfterLayerRenderer->ScaleToTexture();
    AfterLayerRenderer->GetTransform().SetWorldPosition({0, -300, AfterParallax4Z});
    AfterLayerRenderer->GetTransform().SetWorldScale(AfterLayerRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterParallaxRenderer->SetTexture("1_3_AfterParallax_0.png");
    AfterParallaxRenderer->ScaleToTexture();
    AfterParallaxRenderer->GetTransform().SetWorldPosition({0, 100, AfterParallax5Z});
    AfterParallaxRenderer->GetTransform().SetWorldScale(AfterParallaxRenderer->GetTransform().GetWorldScale() * 2.f);
    
    {
        Cemetry* NewCemetry = CreateActor<Cemetry>();
        NewCemetry->GetTransform().SetWorldPosition({550, -1150, TileZ});
    }

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{3200, -1067, PlayerZ};
    PlayerLeftPos_  = float4{150, -1067, PlayerZ};

    IsLeftExit_ = true;
}

void Stage03::Start() { SettingStage(); }

void Stage03::Update(float _DeltaTime)
{
    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }

    float4 CamPos    = GetMainCameraActor()->GetTransform().GetWorldPosition();
    float4 PlayerPos = Penitent_->GetTransform().GetWorldPosition() + float4{0, CameraOffset_};
    float4 CurPos    = float4::LerpLimit(CamPos, PlayerPos, _DeltaTime * 3);

    GetMainCameraActor()->GetTransform().SetWorldPosition({CurPos.x, CurPos.y, CameraZPos_});

    if (-500 < GetMainCameraActor()->GetTransform().GetWorldPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{GetMainCameraActor()->GetTransform().GetLocalPosition().x, -500, CameraZPos_});
    }

    if (670 > GetMainCameraActor()->GetTransform().GetWorldPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{670, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (2700 < GetMainCameraActor()->GetTransform().GetWorldPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{2700, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (100 > Penitent_->GetTransform().GetWorldPosition().x && false == IsLeftExit_)
    {
        IsLeftExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage02");
    }

    if (3250 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage04");
    }

    if (true == GetLoadingEnd())
    {
        SetLoadingEnd(false);

        if (false == Penitent_->IsUpdate())
        {
            Penitent_->On();
            Penitent_->ChangeState("Respawn");
        }
    }
}

void Stage03::End() {}


void Stage03::LevelStartEvent()
{
    LoadingActor_ = CreateActor<LoadingActor>();
    LoadingActor_->IsEntrance(true);

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

        if (false == Penitent_->IsUpdate())
        {
            Penitent_->GetTransform().SetWorldPosition({1800, -1067, PlayerZ});
        }
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;

    GetMainCameraActor()->GetTransform().SetWorldPosition(float4{
        Penitent_->GetTransform().GetLocalPosition() + float4{0, CameraOffset_}
    });
}

void Stage03::LevelEndEvent() { StageBase::LevelEndEvent(); }
