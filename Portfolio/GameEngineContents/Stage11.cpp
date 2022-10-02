#include "PreCompile.h"
#include "Stage11.h"
#include "Door.h"
#include "PrieDieu.h"
#include "MetaTextureRenderer.h"

Stage11::Stage11() {}

Stage11::~Stage11() {}

void Stage11::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("2_2_Colmap.png");
    ColMap_->ScaleToTexture();

    ColMap_->GetTransform().SetWorldPosition({0, 0, ColmapZ});

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("2_2_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, TileZ});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRenderer->SetTexture("2_2_Door.png");
    DoorRenderer->ScaleToTexture();
    DoorRenderer->GetTransform().SetWorldPosition({0, 0, DoorZ});
    DoorRenderer->GetTransform().SetWorldScale(DoorRenderer->GetTransform().GetWorldScale() * 2.f);

    IronDoor_ = CreateActor<Door>();
    IronDoor_->GetTransform().SetWorldPosition({1870, -895, ObjectZ});
    IronDoor_->SetLinkLevel("Stage05");

    PrieDieu* NewPrieDieu = CreateActor<PrieDieu>();
    NewPrieDieu->GetTransform().SetWorldPosition({1430, -920, ObjectZ});
    NewPrieDieu->GetMetaRenderer()->ChangeMetaAnimation("priedieu_upgrade2_stand_and_liton_anim");

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{750, -1200, PlayerZ};
    PlayerLeftPos_  = float4{1870, -1200, PlayerZ};

    IsLeftExit_ = true;
}

void Stage11::Start() { SettingStage(); }

void Stage11::Update(float _DeltaTime)
{
    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }

    float4 CamPos    = GetMainCameraActor()->GetTransform().GetWorldPosition();
    float4 PlayerPos = Penitent_->GetTransform().GetWorldPosition() + float4{0, CameraOffset_};
    float4 CurPos    = float4::LerpLimit(CamPos, PlayerPos, _DeltaTime * 3);

    GetMainCameraActor()->GetTransform().SetWorldPosition({CurPos.x, -850, CameraZPos_});

    if (1530 < GetMainCameraActor()->GetTransform().GetWorldPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(float4{1530, -850, CameraZPos_});
    }

    if (1300 > GetMainCameraActor()->GetTransform().GetWorldPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(float4{1300, -850, CameraZPos_});
    }

    if (730 > Penitent_->GetTransform().GetWorldPosition().x)
    {
        IsRightExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage12");
    }

    if (1950 < Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{1950, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
    }

    if (true == GetLoadingEnd())
    {
        SetLoadingEnd(false);

        StageSoundPlayer_.Volume(0.15f);
        StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Brotherhood_Ambient.wav", -1);

        if (false == Penitent_->IsUpdate())
        {
            Penitent_->On();
            Penitent_->ChangeState("Respawn");
        }

        if (true == Penitent_->GetIsOutDoor())
        {
            Penitent_->SetIsOutDoor(false);

            Penitent_->GetTransform().SetWorldPosition({1870, PlayerRightPos_.y, PlayerZ});
        }

        if (nullptr != GEngine::GetPrevLevel())
        {
            if ("STAGE05" == GEngine::GetPrevLevel()->GetNameConstRef())
            {
                Milestone* MilestoneUI = CreateActor<Milestone>();
                MilestoneUI->SetTownName("Mercy Dreams");
            }
        }
    }

    GameEngineDebug::OutPutString("Cam Pos: " + std::to_string(GetMainCamera()->GetTransform().GetWorldPosition().x));
    GameEngineDebug::OutPutString("Cam Pos YYYY: "
                                  + std::to_string(GetMainCamera()->GetTransform().GetWorldPosition().y));
}

void Stage11::End() {}


void Stage11::LevelStartEvent()
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
            Penitent_->GetTransform().SetWorldPosition({1435, -1200, PlayerZ});
        }
    }

    if (true == Penitent_->GetIsOutDoor())
    {
        IronDoor_->SetObjectType(ObjectType::OpenDoor);
        IronDoor_->GetDoorRenderer()->ChangeFrameAnimation("brotherhood_door_anim_Open");
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;
}

void Stage11::LevelEndEvent() { StageBase::LevelEndEvent(); }
