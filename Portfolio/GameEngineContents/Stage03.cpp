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
    ColMap_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::ColMap)});

    GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer->SetTexture("1_3_BeforeParallax_0.png");
    BeforeParallaxRenderer->ScaleToTexture();
    BeforeParallaxRenderer->GetTransform().SetWorldPosition({0, 300, static_cast<int>(ACTORORDER::BeforeParallax0)});
    BeforeParallaxRenderer->GetTransform().SetWorldScale(BeforeParallaxRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer1->SetTexture("1_3_BeforeParallax_1.png");
    BeforeParallaxRenderer1->ScaleToTexture();
    BeforeParallaxRenderer1->GetTransform().SetWorldPosition({0, 300, static_cast<int>(ACTORORDER::BeforeParallax1)});
    BeforeParallaxRenderer1->GetTransform().SetWorldScale(BeforeParallaxRenderer1->GetTransform().GetWorldScale()
                                                          * 2.2f);

    GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer2->SetTexture("1_2_BeforeParallax_2.png");
    BeforeParallaxRenderer2->ScaleToTexture();
    BeforeParallaxRenderer2->GetTransform().SetWorldPosition({150, 0, static_cast<int>(ACTORORDER::BeforeParallax2)});
    BeforeParallaxRenderer2->GetTransform().SetWorldScale(BeforeParallaxRenderer2->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer3->SetTexture("1_3_BeforeParallax_3.png");
    BeforeParallaxRenderer3->ScaleToTexture();
    BeforeParallaxRenderer3->GetTransform().SetWorldPosition({150, 150, static_cast<int>(ACTORORDER::BeforeParallax3)});
    BeforeParallaxRenderer3->GetTransform().SetWorldScale(BeforeParallaxRenderer3->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer4 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer4->SetTexture("1_3_BeforeParallax_4.png");
    BeforeParallaxRenderer4->ScaleToTexture();
    BeforeParallaxRenderer4->GetTransform().SetWorldPosition(
        {150, -160, static_cast<int>(ACTORORDER::BeforeParallax4)});
    BeforeParallaxRenderer4->GetTransform().SetWorldScale(BeforeParallaxRenderer4->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRendrer->SetTexture("1_3_Tile.png");
    StageRendrer->ScaleToTexture();
    StageRendrer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Tile)});
    StageRendrer->GetTransform().SetWorldScale(StageRendrer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AltarRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AltarRenderer->SetTexture("penitences-altar-off.png");
    AltarRenderer->ScaleToTexture();
    AltarRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Object)});
    AltarRenderer->GetTransform().SetWorldMove({820, -20});

    PrieDieu_ = CreateActor<PrieDieu>();
    PrieDieu_->GetTransform().SetWorldMove({1800, -1000});

    GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRenderer->SetTexture("1_3_Door.png");
    DoorRenderer->ScaleToTexture();
    DoorRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Door)});
    DoorRenderer->GetTransform().SetWorldScale(DoorRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterLayerRenderer->SetTexture("1_3_AfterLayer_0.png");
    AfterLayerRenderer->ScaleToTexture();
    AfterLayerRenderer->GetTransform().SetWorldPosition({0, -300, static_cast<int>(ACTORORDER::AfterLayer0)});
    AfterLayerRenderer->GetTransform().SetWorldScale(AfterLayerRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterParallaxRenderer->SetTexture("1_3_AfterParallax_0.png");
    AfterParallaxRenderer->ScaleToTexture();
    AfterParallaxRenderer->GetTransform().SetWorldPosition({0, 100, static_cast<int>(ACTORORDER::AfterParallax5)});
    AfterParallaxRenderer->GetTransform().SetWorldScale(AfterParallaxRenderer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{3200, -1067, static_cast<int>(ACTORORDER::Player)};
    PlayerLeftPos_  = float4{150, -1067, static_cast<int>(ACTORORDER::Player)};

    ButtonRenderer_ = CreateActor<GameEngineActor>()->CreateComponent<GameEngineUIRenderer>();
    ButtonRenderer_->GetTransform().SetWorldScale({50, 50, 1});
    ButtonRenderer_->SetTexture("KB_SPACE.png");
    ButtonRenderer_->Off();

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
    float4 CurPos    = float4::LerpLimit(CamPos, PlayerPos, _DeltaTime * 5);

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

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage02");
    }

    if (3250 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage04");
    }
}


void Stage03::End() {}

void Stage03::LevelStartEvent()
{
    if (nullptr == Penitent::GetMainPlayer())
    {
        Penitent_ = CreateActor<Penitent>(ACTORORDER::Player);
        Penitent_->GetTransform().SetWorldPosition(PlayerLeftPos_);
        Penitent_->SetGround(ColMap_);

        Penitent_->SetLevelOverOn();
        Penitent_->ChangeState("Respawn");
        Penitent_->GetTransform().SetWorldPosition({1800, -1067, static_cast<int>(ACTORORDER::Player)});
        Penitent_->On();
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
        Penitent_->ChangeState("Respawn");
        Penitent_->GetTransform().SetWorldPosition({1800, -1067, static_cast<int>(ACTORORDER::Player)});
        Penitent_->On();
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

void Stage03::LevelEndEvent()
{
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

        if (true == Penitent_->GetIsFallDeath())
        {
            Guilt_->GetTransform().SetWorldPosition(float4{});
        }

        else
        {
            Guilt_->GetTransform().SetLocalPosition(Penitent_->GetTransform().GetWorldPosition() + float4{0, 0, -1.0f});
        }
    }
}
