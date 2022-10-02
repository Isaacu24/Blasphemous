#include "PreCompile.h"
#include "Stage12.h"
#include "Door.h"
#include "CherubCaptor.h"

Stage12::Stage12() {}

Stage12::~Stage12() {}

void Stage12::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("2_3_Colmap.png");
    ColMap_->ScaleToTexture();

    ColMap_->GetTransform().SetWorldPosition({0, 0, ColmapZ});

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("2_3_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, TileZ});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRenderer->SetTexture("2_3_Door.png");
    DoorRenderer->ScaleToTexture();
    DoorRenderer->GetTransform().SetWorldPosition({0, 0, DoorZ});
    DoorRenderer->GetTransform().SetWorldScale(DoorRenderer->GetTransform().GetWorldScale() * 2.f);

    Door* ShopDoor = CreateActor<Door>();
    ShopDoor->GetTransform().SetWorldPosition({1300, -800, ObjectZ});
    ShopDoor->GetDoorRenderer()->Off();
    ShopDoor->SetLinkLevel("Shop");

    CherubCaptor* Captor = CreateActor<CherubCaptor>();
    Captor->GetTransform().SetWorldPosition({0, 0, MonsterZ});
    Captor->GetTransform().SetWorldMove({800, -550});
    Captor->SetPatrolPosX(800.f, 1200.f);

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{1970, -1025, PlayerZ};
    PlayerLeftPos_  = float4{600, -1025, PlayerZ};

    IsRightExit_ = true;
}

void Stage12::Start() { SettingStage(); }

void Stage12::Update(float _DeltaTime)
{
    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }

    float4 CamPos    = GetMainCameraActor()->GetTransform().GetWorldPosition();
    float4 PlayerPos = Penitent_->GetTransform().GetWorldPosition() + float4{0, CameraOffset_};
    float4 CurPos    = float4::LerpLimit(CamPos, PlayerPos, _DeltaTime * 3);

    GetMainCameraActor()->GetTransform().SetWorldPosition({CurPos.x, -730, CameraZPos_});

    if (1100 > GetMainCameraActor()->GetTransform().GetLocalPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{1100, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (1450 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{1450, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (550 > Penitent_->GetTransform().GetWorldPosition().x)
    {
        //¹Ì±¸Çö
    }

    if (2000 < Penitent_->GetTransform().GetWorldPosition().x)
    {
        IsRightExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage11");
    }

    if (true == GetLoadingEnd())
    {
        SetLoadingEnd(false);

        StageSoundPlayer_.Volume(0.15f);
        StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Boss_Zone_Background.wav", -1);

        if (true == Penitent_->GetIsOutDoor())
        {
            Penitent_->SetIsOutDoor(false);
            Penitent_->GetTransform().SetWorldPosition({1300, PlayerRightPos_.y, PlayerZ});
        }
    }

    GameEngineDebug::OutPutString("Cam Pos: " + std::to_string(GetMainCamera()->GetTransform().GetWorldPosition().x));
}

void Stage12::End() {}


void Stage12::LevelStartEvent()
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
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;

    if (true == Penitent_->GetIsOutDoor())
    {
        Penitent_->GetTransform().SetWorldPosition({1300, -1025, PlayerZ});
    }
}

void Stage12::LevelEndEvent() { StageBase::LevelEndEvent(); }
