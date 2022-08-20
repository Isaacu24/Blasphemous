#include "PreCompile.h"
#include "Stage05.h"
#include "Penitent.h"
#include "Deogracias.h"
#include "Door.h"
#include "GlassSwitch.h"
#include "SideFence.h"

Stage05::Stage05() {}

Stage05::~Stage05() {}


void Stage05::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("1_5_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::ColMap)});

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("1_5_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Tile)});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    // Deogracias* NewDeogracias = CreateActor<Deogracias>();
    // NewDeogracias->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::) });
    // NewDeogracias->GetTransform().SetLocalMove({ 940, -570 });
    // NewDeogracias->GetTransform().PixLocalNegativeX();

    Door* IronDoor = CreateActor<Door>();
    IronDoor->GetTransform().SetWorldMove({1107, -520});

    GlassSwitch* Glass = CreateActor<GlassSwitch>();
    Glass->GetTransform().SetWorldMove({1350, -490});

    SideFence* Fence = CreateActor<SideFence>();
    Fence->GetTransform().SetWorldMove({1390, -535});

    GameEngineTextureRenderer* DoorRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRendrer->SetTexture("1_5_Door.png");
    DoorRendrer->ScaleToTexture();
    DoorRendrer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Door)});
    DoorRendrer->GetTransform().SetWorldScale(DoorRendrer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = StageRenderer->GetTransform().GetLocalScale().x / 2;
    float OffsetY = StageRenderer->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    GetMainCameraActor()->GetTransform().SetWorldPosition(float4{950, -500});

    PlayerRightPos_ = float4{1600, -674, static_cast<int>(ACTORORDER::Player)};
    PlayerLeftPos_  = float4{480, -674, static_cast<int>(ACTORORDER::Player)};

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

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage04");
    }

    if (1650 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage10");
    }

    // GameEngineDebug::OutPutString("x : " + std::to_string(Penitent_->GetTransform().GetLocalPosition().x));
}

void Stage05::End() {}

void Stage05::LevelStartEvent()
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
}

void Stage05::LevelEndEvent() {}
