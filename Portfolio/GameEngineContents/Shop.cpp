#include "PreCompile.h"
#include "Shop.h"
#include "Merchant.h"
#include "Door.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"
#include "ShopObejct.h"

Shop::Shop() {}

Shop::~Shop() {}


void Shop::Start()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("Shop_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0.f, ColmapZ});

    GameEngineTextureRenderer* TileRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    TileRenderer->SetTexture("Shop_Tile.png");
    TileRenderer->ScaleToTexture();
    TileRenderer->GetTransform().SetWorldPosition({0, 0.f, TileZ});
    TileRenderer->GetTransform().SetWorldScale(TileRenderer->GetTransform().GetWorldScale());

    GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterLayerRenderer->SetTexture("Shop_AfterLayer.png");
    AfterLayerRenderer->ScaleToTexture();
    AfterLayerRenderer->GetTransform().SetWorldPosition({100, 75, AfterLayerZ});
    AfterLayerRenderer->GetTransform().SetWorldScale(AfterLayerRenderer->GetTransform().GetWorldScale());

    Door* ShopDoor = CreateActor<Door>();
    ShopDoor->GetTransform().SetWorldPosition({580, -500, ObjectZ});
    ShopDoor->GetDoorRenderer()->Off();
    ShopDoor->SetLinkLevel("Stage12");

    {
        ShopObejct* Object = CreateActor<ShopObejct>();
        Object->GetTransform().SetWorldPosition({500, -170, AfterParallax1Z});
    }

    {
        ShopObejct* Object = CreateActor<ShopObejct>();
        Object->GetTransform().SetWorldPosition({800, -200, AfterParallax1Z});
        Object->GetMetaRenderer()->ChangeMetaAnimation("merchantTent_lamp01");
    }

    {
        ShopObejct* Object = CreateActor<ShopObejct>();
        Object->GetTransform().SetWorldPosition({1000, -180, AfterParallax1Z});
        Object->GetMetaRenderer()->ChangeMetaAnimation("merchantTent_pennant01");
    }

    {
        ShopObejct* Object = CreateActor<ShopObejct>();
        Object->GetTransform().SetWorldPosition({1150, -180, AfterParallax1Z});
        Object->GetMetaRenderer()->ChangeMetaAnimation("merchantTent_pennant02");
    }

    {
        ShopObejct* Object = CreateActor<ShopObejct>();
        Object->GetTransform().SetWorldPosition({1350, -150, AfterParallax1Z});
        Object->GetMetaRenderer()->ChangeMetaAnimation("merchantTent_pennant03");
    }

    Merchant_ = CreateActor<Merchant>();
    Merchant_->GetTransform().SetWorldPosition({1300, -680, NPCZ});
    Merchant_->GetTransform().PixLocalNegativeX();

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{600, -860, PlayerZ};
    PlayerLeftPos_  = float4{600, -860, PlayerZ};

    IsLeftExit_ = true;

    GetMainCameraActor()->GetTransform().SetWorldPosition({925, -500});
}

void Shop::SettingStage() {}

void Shop::Update(float _DeltaTime)
{
    StageBase::Update(_DeltaTime);

    GetMainCameraActor()->GetTransform().SetWorldPosition({925, -500, CameraZPos_});

    if (true == GetLoadingEnd())
    {
        SetLoadingEnd(false);

        if (true == Penitent_->GetIsOutDoor())
        {
            Penitent_->SetIsOutDoor(false);
            Penitent_->GetTransform().SetWorldPosition({580, PlayerRightPos_.y, PlayerZ});
        }
    }
}

void Shop::End() {}


void Shop::LevelStartEvent()
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

        Penitent_->SetLevelOverOn();
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;

    GetMainCameraActor()->GetTransform().SetWorldPosition({925, -500});
}

void Shop::LevelEndEvent() { StageBase::LevelEndEvent(); }
