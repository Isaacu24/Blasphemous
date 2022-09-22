#include "PreCompile.h"
#include "Stage05.h"
#include "Penitent.h"
#include "Deogracias.h"
#include "Door.h"
#include "GlassSwitch.h"
#include "SideFence.h"
#include "Fly.h"
#include "MetaTextureRenderer.h"

Stage05::Stage05() {}

Stage05::~Stage05() {}


void Stage05::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("1_5_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, ColmapZ});

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("1_5_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, TileZ});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    // Deogracias* NewDeogracias = CreateActor<Deogracias>();
    // NewDeogracias->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::) });
    // NewDeogracias->GetTransform().SetLocalMove({ 940, -570 });
    // NewDeogracias->GetTransform().PixLocalNegativeX();

    IronDoor_ = CreateActor<Door>();
    IronDoor_->GetTransform().SetWorldPosition({1107, -520, ObjectZ});
    IronDoor_->SetLinkLevel("Stage11");

    Fence_ = CreateActor<SideFence>();
    Fence_->GetTransform().SetWorldPosition({1390, -530, ObjectZ});

    GlassSwitch* Glass = CreateActor<GlassSwitch>();
    Glass->SetSideFence(Fence_);
    Glass->GetTransform().SetWorldPosition({1350, -490, ObjectZ});

    GameEngineTextureRenderer* DoorRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRendrer->SetTexture("1_5_Door.png");
    DoorRendrer->ScaleToTexture();
    DoorRendrer->GetTransform().SetWorldPosition({0, 0, DoorZ});
    DoorRendrer->GetTransform().SetWorldScale(DoorRendrer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterRendrer->SetTexture("1_5_AfterLayer.png");
    AfterRendrer->ScaleToTexture();
    AfterRendrer->GetTransform().SetWorldPosition({0, 0, AfterLayerZ});
    AfterRendrer->GetTransform().SetWorldScale(AfterRendrer->GetTransform().GetWorldScale() * 2.f);

    {
        Fly* NewFly = CreateActor<Fly>();
        NewFly->GetTransform().SetWorldPosition({650, -550, TileZ});
    }

    {
        Fly* NewFly = CreateActor<Fly>();
        NewFly->GetTransform().SetWorldPosition({850, -600, TileZ});
        NewFly->GetMetaRenderer()->CurAnimationSetStartPivotFrame(5);
    }

    float OffsetX = StageRenderer->GetTransform().GetLocalScale().x / 2;
    float OffsetY = StageRenderer->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    GetMainCameraActor()->GetTransform().SetWorldPosition(float4{950, -550});

    PlayerRightPos_ = float4{1600, -764, PlayerZ};
    PlayerLeftPos_  = float4{480, -764, PlayerZ};

    IsLeftExit_ = true;
}

void Stage05::Start() { SettingStage(); }

void Stage05::Update(float _DeltaTime)
{
    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }

    if (430 > Penitent_->GetTransform().GetWorldPosition().x && false == IsLeftExit_)
    {
        IsLeftExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage04");
    }

    //Ææ½º°¡ ´ÝÇôÀÖ´Ù¸é
    if (true == Fence_->GetIsClose())
    {
        if (1400 < Penitent_->GetTransform().GetWorldPosition().x)
        {
            Penitent_->GetTransform().SetWorldPosition(
                {1400, Penitent_->GetTransform().GetWorldPosition().y, Penitent_->GetTransform().GetWorldPosition().z});
            return;
        }
    }

    if (1650 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage10");
    }

    if (true == GetLoadingEnd())
    {
        SetLoadingEnd(false);

        if (nullptr != GEngine::GetPrevLevel())
        {
            if ("STAGE10" == GEngine::GetPrevLevel()->GetNameConstRef()
                || "STAGE11" == GEngine::GetPrevLevel()->GetNameConstRef())
            {
                Milestone* MilestoneUI = CreateActor<Milestone>();
                MilestoneUI->SetTownName("Brotherhood");
            }
        }

        if (true == Penitent_->GetIsOutDoor())
        {
            Penitent_->SetIsOutDoor(false);
            Penitent_->GetTransform().SetWorldPosition({1107.f, PlayerRightPos_.y});
        }
    }

    // GameEngineDebug::OutPutString("x : " + std::to_string(Penitent_->GetTransform().GetLocalPosition().x));
}

void Stage05::End() {}

void Stage05::LevelStartEvent()
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

        if (true == Penitent_->GetIsOutDoor())
        {
            IronDoor_->GetDoorRenderer()->ChangeFrameAnimation("brotherhood_door_anim_Open");
        }
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;
}

void Stage05::LevelEndEvent() { StageBase::LevelEndEvent(); }
