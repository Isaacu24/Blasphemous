#include "PreCompile.h"
#include "Shop.h"

Shop::Shop() {}

Shop::~Shop() {}


void Shop::Start()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("Shop_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::ColMap)});

    GameEngineTextureRenderer* TileRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    TileRenderer->SetTexture("Shop_Tile.png");
    TileRenderer->ScaleToTexture();
    TileRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Tile)});
    TileRenderer->GetTransform().SetWorldScale(TileRenderer->GetTransform().GetWorldScale());

    GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterLayerRenderer->SetTexture("Shop_AfterLayer.png");
    AfterLayerRenderer->ScaleToTexture();
    AfterLayerRenderer->GetTransform().SetWorldPosition({100, 75, static_cast<int>(ACTORORDER::AfterLayer0)});
    AfterLayerRenderer->GetTransform().SetWorldScale(AfterLayerRenderer->GetTransform().GetWorldScale());

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    GetMainCameraActor()->GetTransform().SetWorldPosition({925, -500});
}

void Shop::SettingStage() {}

void Shop::Update(float _DeltaTime)
{
    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }
}

void Shop::End() {}


void Shop::LevelStartEvent()
{
    if (nullptr == Penitent::GetMainPlayer())
    {
        Penitent_ = CreateActor<Penitent>(ACTORORDER::Player);
        Penitent_->GetTransform().SetWorldPosition({1250, -860, static_cast<int>(ACTORORDER::Player)});
        Penitent_->SetGround(ColMap_);

        Penitent_->SetLevelOverOn();
    }

    else if (nullptr != Penitent::GetMainPlayer())
    {
        Penitent_ = Penitent::GetMainPlayer();
        Penitent_->GetTransform().SetWorldPosition({1250, -860, static_cast<int>(ACTORORDER::Player)});
        Penitent_->SetGround(ColMap_);

        Penitent_->SetLevelOverOn();
    }

    if (350 > Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{350, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player)});
    }

    if (2000 < Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{2000, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player)});
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;
}

void Shop::LevelEndEvent() {}
