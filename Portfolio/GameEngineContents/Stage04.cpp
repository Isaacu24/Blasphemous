#include "PreCompile.h"
#include "Stage04.h"
#include "Penitent.h"
#include "ElderBrother.h"

Stage04::Stage04() {}

Stage04::~Stage04() {}

void Stage04::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("1_4_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, ColmapZ});

    GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer->SetTexture("1_4_BeforeParallax_0.png");
    BeforeParallaxRenderer->ScaleToTexture();
    BeforeParallaxRenderer->GetTransform().SetWorldPosition({200, 200, BeforeParallaxZ});
    BeforeParallaxRenderer->GetTransform().SetWorldScale(BeforeParallaxRenderer->GetTransform().GetWorldScale() * 3.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer1->SetTexture("1_4_BeforeParallax_1.png");
    BeforeParallaxRenderer1->ScaleToTexture();
    BeforeParallaxRenderer1->GetTransform().SetWorldPosition({-300, 500, BeforeParallax1Z});
    BeforeParallaxRenderer1->GetTransform().SetWorldScale(BeforeParallaxRenderer1->GetTransform().GetWorldScale()
                                                          * 3.5f);

    GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer2->SetTexture("1_4_BeforeParallax_2.png");
    BeforeParallaxRenderer2->ScaleToTexture();
    BeforeParallaxRenderer2->GetTransform().SetWorldPosition({200, 100, BeforeParallax2Z});
    BeforeParallaxRenderer2->GetTransform().SetWorldScale(BeforeParallaxRenderer2->GetTransform().GetWorldScale()
                                                          * 2.5f);

    GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer3->SetTexture("1_4_BeforeParallax_3.png");
    BeforeParallaxRenderer3->ScaleToTexture();
    BeforeParallaxRenderer3->GetTransform().SetWorldPosition({100, -170, BeforeParallax3Z});
    BeforeParallaxRenderer3->GetTransform().SetWorldScale(BeforeParallaxRenderer3->GetTransform().GetWorldScale()
                                                          * 2.5f);

    GameEngineTextureRenderer* BeforeParallaxRenderer4 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer4->SetTexture("1_4_BeforeParallax_4.png");
    BeforeParallaxRenderer4->ScaleToTexture();
    BeforeParallaxRenderer4->GetTransform().SetWorldPosition({100, -220, BeforeParallax4Z});
    BeforeParallaxRenderer4->GetTransform().SetWorldScale(BeforeParallaxRenderer4->GetTransform().GetWorldScale()
                                                          * 2.5f);

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("1_4_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, TileZ});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRenderer->SetTexture("1_4_Door.png");
    DoorRenderer->ScaleToTexture();
    DoorRenderer->GetTransform().SetWorldPosition({0, 0, DoorZ});
    DoorRenderer->GetTransform().SetWorldScale(DoorRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterLayerRenderer->SetTexture("1_4_AfterLayer_0.png");
    AfterLayerRenderer->ScaleToTexture();
    AfterLayerRenderer->GetTransform().SetWorldPosition({0, -400, AfterLayerZ});
    AfterLayerRenderer->GetTransform().SetWorldScale(AfterLayerRenderer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{2750, -1028, PlayerZ};
    PlayerLeftPos_  = float4{250, -1028, PlayerZ};

    IsLeftExit_ = true;
}

void Stage04::SettingMonster()
{
    ElderBrother_ = CreateActor<ElderBrother>();
    ElderBrother_->GetTransform().SetWorldPosition({2500, -1200, BeforeParallax2Z});
    ElderBrother_->SetGround(ColMap_);
    BossMonster_ = ElderBrother_;
}

void Stage04::Start()
{
    SettingStage();
    SettingMonster();
}

void Stage04::Update(float _DeltaTime)
{
    StageBase::Update(_DeltaTime);

    if (nullptr != LoadingActor_ && 0.f < LoadingActor_->GetAlpha())
    {
        float Ratio = 1.f - LoadingActor_->GetAlpha();
        StageSoundPlayer_.Volume(Ratio);
    }

    StageFlowUpdate(_DeltaTime);
}

void Stage04::End() {}

void Stage04::StageFlowUpdate(float _DeltaTime)
{
    switch (CurrentFlow_)
    {
        case STAGEFLOW::NORMAL:
            PlayerCameraMove(_DeltaTime);

            if (1350 < Penitent_->GetTransform().GetWorldPosition().x)
            {
                Penitent_->ChangeState("Freeze");
                ElderBrother_->EventOn();

                StageSoundPlayer_.Stop();

                CurrentFlow_ = STAGEFLOW::BOSSAPPEAR;
            }
            break;
        case STAGEFLOW::BOSSAPPEAR:
            if (1850.f > GetMainCameraActor()->GetTransform().GetWorldPosition().x)
            {
                GetMainCameraActor()->GetTransform().SetWorldRightMove(75.f, _DeltaTime);
            }

            if (true == ElderBrother_->GetBossEvent())
            {
                Penitent_->SetIsFreezeEnd(true);
                CurrentFlow_ = STAGEFLOW::BOSSCOMBAT;

                StageSoundPlayer_.Stop();
                StageSoundPlayer_ = GameEngineSound::SoundPlayControl("ElderBrother.wav", -1);
                StageSoundPlayer_.Volume(1.0f);
            }
            break;
        case STAGEFLOW::BOSSCOMBAT:
            PlayerCameraMove(_DeltaTime);

            if (400 > Penitent_->GetTransform().GetWorldPosition().x)
            {
                Penitent_->GetTransform().SetWorldPosition(
                    float4{400, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
            }

            else if (2500 < Penitent_->GetTransform().GetWorldPosition().x)
            {
                Penitent_->GetTransform().SetWorldPosition(
                    float4{2500, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
            }

            if (1000 > GetMainCameraActor()->GetTransform().GetLocalPosition().x)
            {
                GetMainCameraActor()->GetTransform().SetWorldPosition(
                    float4{1000, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
            }

            if (1850 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
            {
                GetMainCameraActor()->GetTransform().SetWorldPosition(
                    float4{1850, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
            }

            if (true == ElderBrother_->GetBossDeathEvent())
            {
                StageSoundPlayer_.Stop();

                StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Boss_Zone_Background.wav", -1);
                StageSoundPlayer_.Volume(1.f);

                CurrentFlow_ = STAGEFLOW::BOSSDEAD;
            }
            break;
        case STAGEFLOW::BOSSDEAD:
            PlayerCameraMove(_DeltaTime);
            break;
    }
}

void Stage04::LevelStartEvent()
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

    GetMainCameraActor()->GetTransform().SetWorldPosition(float4{
        Penitent_->GetTransform().GetLocalPosition() + float4{0, CameraOffset_}
    });

    StageSoundPlayer_.Pause(false);

    StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Boss_Zone_Background.wav", -1);
    StageSoundPlayer_.Volume(0.f);
}

void Stage04::LevelEndEvent()
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
            Guilt_->GetTransform().SetLocalPosition(float4{500, -1020, ObjectZ});
        }
    }

    if (false == IsRightExit_ && false == IsLeftExit_)
    {
        IsLeftExit_ = true;
    }

    StageSoundPlayer_.Stop();
}

void Stage04::PlayerCameraMove(float _DeltaTime)
{
    float4 CamPos    = GetMainCameraActor()->GetTransform().GetWorldPosition();
    float4 PlayerPos = Penitent_->GetTransform().GetWorldPosition() + float4{0, CameraOffset_};
    float4 CurPos    = float4::LerpLimit(CamPos, PlayerPos, _DeltaTime * 3);

    GetMainCameraActor()->GetTransform().SetWorldPosition({CurPos.x, CurPos.y, CameraZPos_});

    if (-700 < GetMainCameraActor()->GetTransform().GetLocalPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{GetMainCameraActor()->GetTransform().GetLocalPosition().x, -700, CameraZPos_});
    }

    if (700 > GetMainCameraActor()->GetTransform().GetLocalPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{700, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (2200 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{2200, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (200 > Penitent_->GetTransform().GetWorldPosition().x && false == IsLeftExit_)
    {
        IsLeftExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage03");
    }

    if (2800 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage05");
    }
}
