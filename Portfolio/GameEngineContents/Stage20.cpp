#include "PreCompile.h"
#include "Stage20.h"
#include "Penitent.h"
#include "Pope.h"
#include "BossUI.h"

Stage20::Stage20() {}

Stage20::~Stage20() {}


void Stage20::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("12_2_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::ColMap)});

    GameEngineTextureRenderer* BeforePrallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforePrallaxRenderer->SetTexture("12_2_BeforeParallax_0.png");
    BeforePrallaxRenderer->ScaleToTexture();
    BeforePrallaxRenderer->GetTransform().SetWorldPosition({0, 390, static_cast<int>(ACTORORDER::BeforeParallax5)});
    BeforePrallaxRenderer->GetTransform().SetWorldScale(BeforePrallaxRenderer->GetTransform().GetWorldScale() * 2.3f);

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("12_2_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Tile)});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterLayerRenderer->SetTexture("12_2_AfterLayer.png");
    AfterLayerRenderer->ScaleToTexture();
    AfterLayerRenderer->GetTransform().SetWorldPosition({0, -550, static_cast<int>(ACTORORDER::AfterLayer5)});
    AfterLayerRenderer->GetTransform().SetWorldScale(AfterLayerRenderer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{4250, -1663, static_cast<int>(ACTORORDER::Player)};
    PlayerLeftPos_  = float4{400, -1663, static_cast<int>(ACTORORDER::Player)};

    IsLeftExit_ = true;
}

void Stage20::SettingMonster()
{
    Pope_ = CreateActor<Pope>();
    Pope_->GetTransform().SetWorldPosition({2500, -1760, static_cast<int>(ACTORORDER::BossMonster)});
    Pope_->GetTransform().SetWorldScale({1.5f, 1.5f});
    Pope_->SetGround(ColMap_);
    BossMonster_ = Pope_;
    Pope_->Off();
}

void Stage20::Start()
{
    SettingStage();
    SettingMonster();
}

void Stage20::Update(float _DeltaTime)
{
    switch (CurrentFlow_)
    {
        case STAGEFLOW::NORMAL:
            PlayerCameraMove();

            if (2000.f <= Penitent_->GetTransform().GetWorldPosition().x && false == IsEvent_)
            {
                Penitent_->ChangeState("Freeze");
                CurrentFlow_ = STAGEFLOW::BOSSAPPEAR;
            }
            break;
        case STAGEFLOW::BOSSAPPEAR:
            if (2275.f > GetMainCameraActor()->GetTransform().GetWorldPosition().x)
            {
                GetMainCameraActor()->GetTransform().SetWorldRightMove(300, _DeltaTime);
            }

            else
            {
                if (nullptr == BossUI_)
                {
                    BossUI_ = CreateActor<BossUI>();

                    Font_ = Stage_->CreateComponent<GameEngineFontRenderer>();
                    Font_->SetColor({0.65f, 0.65f, 0.45f, 1.0f});
                    Font_->SetScreenPostion({470, 590, -100.f});
                    Font_->SetText("에스크리바르 교황 성하", "Neo둥근모");
                    Font_->SetSize(30);
                    Font_->ChangeCamera(CAMERAORDER::UICAMERA);

                    Penitent_->ChangeState("Idle");

                    Pope_->On();
                    Pope_->GetTransform().PixLocalNegativeX();
                    Pope_->ChangeMonsterState("Appear");
                    Pope_->SetTarget(Penitent_);
                }

                if (1660.f > Penitent_->GetTransform().GetLocalPosition().x)
                {
                    Penitent_->GetTransform().SetWorldPosition(
                        {1660.f, Penitent_->GetTransform().GetWorldPosition().y});
                }

                else if (2900.f < Penitent_->GetTransform().GetLocalPosition().x)
                {
                    Penitent_->GetTransform().SetWorldPosition(
                        {2900.f, Penitent_->GetTransform().GetWorldPosition().y});
                }
            }
            break;
        case STAGEFLOW::BOSSCOMBAT:
            break;
        case STAGEFLOW::BOSSDEAD:
            break;
        default:
            break;
    }
}

void Stage20::End() {}

void Stage20::OnEvent()
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

void Stage20::OffEvent() {}

void Stage20::PlayerCameraMove()
{
    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }

    GetMainCameraActor()->GetTransform().SetWorldPosition(
        {Penitent_->GetTransform().GetLocalPosition().x, -1540, CameraZPos_});

    if (940 > GetMainCameraActor()->GetTransform().GetLocalPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{940, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (3600 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{3600, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (350 > Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{350, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player)});
    }

    if (4350 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage30");
    }
}
