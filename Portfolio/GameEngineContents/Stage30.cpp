#include "PreCompile.h"
#include "Stage30.h"
#include "Penitent.h"
#include "Deogracias.h"

Stage30::Stage30() {}

Stage30::~Stage30() {}

void Stage30::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("13_1_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, ColmapZ});

    GameEngineTextureRenderer* BeforeParallaxRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRendrer->SetTexture("13_1_BeforeParallax_0.png");
    BeforeParallaxRendrer->ScaleToTexture();
    BeforeParallaxRendrer->GetTransform().SetWorldPosition({-800, 0, BeforeParallax4Z});
    BeforeParallaxRendrer->GetTransform().SetWorldScale(BeforeParallaxRendrer->GetTransform().GetWorldScale() * 2.2f);

    GameEngineTextureRenderer* BeforeParallaxRendrer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRendrer1->SetTexture("13_1_BeforeParallax_1.png");
    BeforeParallaxRendrer1->ScaleToTexture();
    BeforeParallaxRendrer1->GetTransform().SetWorldPosition({-800, 500, BeforeParallax5Z});
    BeforeParallaxRendrer1->GetTransform().SetWorldScale(BeforeParallaxRendrer1->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* BeforeLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeLayerRenderer->SetTexture("13_1_BeforeLayer.png");
    BeforeLayerRenderer->ScaleToTexture();
    BeforeLayerRenderer->GetTransform().SetWorldPosition({0, 0, BeforeLayerZ});
    BeforeLayerRenderer->GetTransform().SetWorldScale(BeforeLayerRenderer->GetTransform().GetWorldScale() * 2.f);

    Deogracias* NewDeogracias = CreateActor<Deogracias>();
    NewDeogracias->GetTransform().SetWorldPosition({800, -870, NPCZ});
    NewDeogracias->ChangeFrontAnimation();
    NewDeogracias->GetTransform().PixLocalNegativeX();

    GameEngineTextureRenderer* StageRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer2->SetTexture("13_1_2_Tile.png");
    StageRenderer2->ScaleToTexture();
    StageRenderer2->GetTransform().SetWorldPosition({0, 0, AfterLayerZ});
    StageRenderer2->GetTransform().SetWorldScale(StageRenderer2->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* StageRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer1->SetTexture("13_1_1_Tile.png");
    StageRenderer1->ScaleToTexture();
    StageRenderer1->GetTransform().SetWorldPosition({0, 0, AfterLayer1Z});
    StageRenderer1->GetTransform().SetWorldScale(StageRenderer1->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterLayerRenderer->SetTexture("13_1_AfterLayer.png");
    AfterLayerRenderer->ScaleToTexture();
    AfterLayerRenderer->GetTransform().SetWorldPosition({0, 0, AfterLayer2Z});
    AfterLayerRenderer->GetTransform().SetWorldScale(AfterLayerRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* ChairRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ChairRenderer->SetTexture("ash-mountain-spritesheet_9.png");
    ChairRenderer->ScaleToTexture();
    ChairRenderer->GetTransform().SetWorldPosition({0, 0, AfterLayer3Z});
    ChairRenderer->GetTransform().SetWorldMove({1060, 920, 0.0f});

    GameEngineTextureRenderer* AfterParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterParallaxRenderer->SetTexture("13_1_AfterParallax_0.png");
    AfterParallaxRenderer->ScaleToTexture();
    AfterParallaxRenderer->GetTransform().SetWorldPosition({500, 500, AfterParallax5Z});
    AfterParallaxRenderer->GetTransform().SetWorldScale(AfterParallaxRenderer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = StageRenderer2->GetTransform().GetLocalScale().x / 2;
    float OffsetY = StageRenderer2->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);


}

void Stage30::Start() { SettingStage(); }

void Stage30::Update(float _DeltaTime)
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

    if (-50 < GetMainCameraActor()->GetTransform().GetWorldPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{GetMainCameraActor()->GetTransform().GetWorldPosition().x, -50, CameraZPos_});
    }

    if (680 > GetMainCameraActor()->GetTransform().GetWorldPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{680, GetMainCameraActor()->GetTransform().GetWorldPosition().y, CameraZPos_});
    }

    if (2850 < GetMainCameraActor()->GetTransform().GetWorldPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{2850, GetMainCameraActor()->GetTransform().GetWorldPosition().y, CameraZPos_});
    }

    if (100 > Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{100, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
    }
}

void Stage30::End() {}

void Stage30::LevelStartEvent()
{
    LoadingActor_ = CreateActor<LoadingActor>();
    LoadingActor_->IsEntrance(true);

    if (nullptr == Penitent::GetMainPlayer())
    {
        Penitent_ = CreateActor<Penitent>();
        Penitent_->GetTransform().SetWorldPosition({150, -963, PlayerZ});
        Penitent_->SetGround(ColMap_);

        Penitent_->SetLevelOverOn();
    }

    else if (nullptr != Penitent::GetMainPlayer())
    {
        Penitent_ = Penitent::GetMainPlayer();
        Penitent_->GetTransform().SetWorldPosition({150, -963, PlayerZ});
        Penitent_->SetGround(ColMap_);

        Penitent_->SetLevelOverOn();
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;

    GetMainCameraActor()->GetTransform().SetWorldPosition(float4{
        Penitent_->GetTransform().GetLocalPosition() + float4{0, CameraOffset_}
    });
}

void Stage30::LevelEndEvent() 
{
    if (nullptr != LoadingActor_)
    {
        LoadingActor_->Death();
        LoadingActor_ = nullptr;
    }

    if (false == Penitent_->IsUpdate())
    {
        if (nullptr == Guilt_)
        {
            Guilt_ = CreateActor<PenitentGuilt>();
        }

        else
        {
            return;
        }

        if (true == Penitent_->GetIsPlayerDeath())
        {
            Guilt_->GetTransform().SetWorldPosition(Penitent_->GetLastJumpPosition());
        }

        else
        {
            Guilt_->GetTransform().SetLocalPosition({Penitent_->GetTransform().GetWorldPosition().x,
                                                     Penitent_->GetTransform().GetWorldPosition().y,
                                                     ObjectZ});
        }
    }
}
