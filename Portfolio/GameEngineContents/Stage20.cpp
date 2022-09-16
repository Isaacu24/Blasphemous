#include "PreCompile.h"
#include "Stage20.h"
#include "Penitent.h"
#include "Pope.h"

Stage20::Stage20() {}

Stage20::~Stage20() {}


void Stage20::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("12_2_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, ColmapZ});

    GameEngineTextureRenderer* BeforePrallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforePrallaxRenderer->SetTexture("12_2_BeforeParallax_0.png");
    BeforePrallaxRenderer->ScaleToTexture();
    BeforePrallaxRenderer->GetTransform().SetWorldPosition({0, 385, BeforeParallax5Z});
    BeforePrallaxRenderer->GetTransform().SetWorldScale(BeforePrallaxRenderer->GetTransform().GetWorldScale() * 2.3f);

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("12_2_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, TileZ});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterLayerRenderer->SetTexture("12_2_AfterLayer.png");
    AfterLayerRenderer->ScaleToTexture();
    AfterLayerRenderer->GetTransform().SetWorldPosition({0, -775, AfterLayer5Z});
    AfterLayerRenderer->GetTransform().SetWorldScale(AfterLayerRenderer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{4250, -1663, PlayerZ};
    PlayerLeftPos_  = float4{400, -1663, PlayerZ};

    IsLeftExit_ = true;

    UIActor_ = CreateActor<GameEngineActor>();

    ReturnKey_ = UIActor_->CreateComponent<GameEngineTextureRenderer>();
    ReturnKey_->SetTexture("CT_B.png");
    ReturnKey_->GetTransform().SetWorldScale({30, 30, 1});
    UIActor_->Off();
}

void Stage20::SettingMonster()
{
    Pope_ = CreateActor<Pope>();
    Pope_->GetTransform().SetWorldPosition({2500, -1760, BossMonsterZ});
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
            PlayerCameraMove(_DeltaTime);

            if (2000.f <= Penitent_->GetTransform().GetWorldPosition().x)
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
                Pope_->On();
                Pope_->GetTransform().PixLocalNegativeX();
                Pope_->ChangeMonsterState("Appear");
                Pope_->SetTarget(Penitent_);

                CurrentFlow_ = STAGEFLOW::BOSSCOMBAT;
            }
            break;
        case STAGEFLOW::BOSSCOMBAT:
            if (1660.f > Penitent_->GetTransform().GetLocalPosition().x)
            {
                Penitent_->GetTransform().SetWorldPosition({1660.f, Penitent_->GetTransform().GetWorldPosition().y});
            }

            else if (2900.f < Penitent_->GetTransform().GetLocalPosition().x)
            {
                Penitent_->GetTransform().SetWorldPosition({2900.f, Penitent_->GetTransform().GetWorldPosition().y});
            }

            if (true == Pope_->IsDeath())
            {
                Penitent_->SetReturnToPort(true);

                if ("ReturnToPort" == Penitent_->GetPenitentState())
                {
                    UIActor_->Off();
                    return;
                }

                PlayerReturnPos_ = Penitent_->GetTransform().GetWorldPosition();

                UIActor_->On();
                UIActor_->GetTransform().SetWorldPosition({PlayerReturnPos_.x, PlayerReturnPos_.y + 200.f, PlayerZ});
            }
            break;
        case STAGEFLOW::BOSSDEAD:
            PlayerCameraMove(_DeltaTime);
            break;
    }
}

void Stage20::End() {}

void Stage20::LevelStartEvent()
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

        if (STAGEFLOW::BOSSDEAD == CurrentFlow_)
        {
            Penitent_->GetTransform().SetWorldPosition(PlayerReturnPos_);
        }

        Penitent_->SetLevelOverOn();
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;

    GetMainCameraActor()->GetTransform().SetWorldPosition(float4{
        Penitent_->GetTransform().GetLocalPosition() + float4{0, CameraOffset_}
    });

    if (STAGEFLOW::BOSSCOMBAT == CurrentFlow_)
    {
        ReturnKey_->Off();
        CurrentFlow_ = STAGEFLOW::BOSSDEAD;
    }

}

void Stage20::LevelEndEvent()
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
            Guilt_->GetTransform().SetWorldPosition(Penitent_->GetLastJumpPosition());
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

void Stage20::PlayerCameraMove(float _DeltaTime)
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

    if (-1550 < GetMainCameraActor()->GetTransform().GetLocalPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{GetMainCameraActor()->GetTransform().GetLocalPosition().x, -1550, CameraZPos_});
    }

    if (350 > Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{350, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
    }

    if (4350 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage30");
    }
}
