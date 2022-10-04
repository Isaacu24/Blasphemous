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

    MessageUI_ = CreateActor<MessageUI>();
    MessageUI_->SetSpeed(10.f);
    MessageUI_->CreateLine("�� �ӿ��� ���� �ٰ����� �״��� �߼Ҹ��� �����. \n�� �ӿ��� ���� �״뿡�� ���� �ɰ� "
                           "�λ縦 �Ϸ� �ߴ�.");
    MessageUI_->AddSound("DLG_2501_0.wav");
    MessageUI_->CreateLine("������ ��ȣ������, ������ ����� ��Ű�� ��ȣ���� ���� \nū ������ �������� �ƹ����� "
                           "������ ���ϰ� �����̶�.");
    MessageUI_->AddSound("DLG_2501_1.wav");
    MessageUI_->CreateLine("���� �������̷� ���� �� ���̸�, \n������� �ü��� ���ϴ� �� ���̴϶�.");
    MessageUI_->AddSound("DLG_2501_2.wav");
    MessageUI_->CreateLine("�׷��� �� ������ �̸� ���� ��� �ܿ���, �״븦 �𸥴�.");
    MessageUI_->AddSound("DLG_2501_3.wav");
    MessageUI_->CreateLine("�״��� ��ó������ ���� �� ���� ���� ����϶�. \n�״��� ������ ������ ����϶�.");
    MessageUI_->AddSound("DLG_2501_4.wav");
    MessageUI_->CreateLine("�ƴ�, �״븦 �ƴ� �� ���� ���̴�");
    MessageUI_->AddSound("DLG_2501_5.wav");
    MessageUI_->CreateLine("�˸� ���� ������ �״��� Į��, \nȲ�ݿ� ������ ���� Į�� �ºε������� ����.");
    MessageUI_->AddSound("DLG_2503_0.wav");
    MessageUI_->CreateLine("��ó�� ������, �Ȱ� �ϸ���.");
    MessageUI_->AddSound("DLG_2503_1.wav");
    MessageUI_->CreateLine("�״��� �̸��� ���� ������ �����ϸ���.");
    MessageUI_->AddSound("DLG_2503_2.wav");
    MessageUI_->CreateLine("�״��� ������ ���� ������ �ູ�ϸ���.");
    MessageUI_->AddSound("DLG_2503_3.wav");
    MessageUI_->SetFontColor(float4{0.63f, 0.6f, 0.55f});
    MessageUI_->SetBackgroudAlpha(0.5f);
    MessageUI_->SetSpeed(5.f);
    MessageUI_->Off();

    MessageUI_->SetMassageStartEvent(0, [&]() { Penitent_->SetIsFreezeEnd(false); });

    MessageUI_->SetMassageStartEvent(5,
                                     [&]()
                                     {
                                         Pope_->On();
                                         Pope_->GetTransform().PixLocalNegativeX();
                                         Pope_->ChangeMonsterState("AppearEvent");
                                         Pope_->SetTarget(Penitent_);
                                     });

    MessageUI_->SetMassageEndEvent(10,
                                   [&]()
                                   {
                                       Penitent_->SetIsFreezeEnd(true);
                                       Pope_->ChangeMonsterState("Idle");
                                       CurrentFlow_ = STAGEFLOW::BOSSCOMBAT;
                                       MessageUI_->Off();

                                       StageSoundPlayer_.Stop();
                                       StageSoundPlayer_
                                           = GameEngineSound::SoundPlayControl("Final Boss_MASTER.wav", -1);
                                       StageSoundPlayer_.Volume(1.f);
                                   });
}

void Stage20::SettingMonster()
{
    Pope_ = CreateActor<Pope>();
    Pope_->GetTransform().SetWorldPosition({2500, -1755, BossMonsterZ});
    Pope_->SetGround(ColMap_);
    BossMonster_ = Pope_;
    Pope_->Off();
}

void Stage20::Start()
{
    SettingStage();
    SettingMonster();

    CutScenePlayer_ = CreateActor<CutScenePlayer>();
    CutScenePlayer_->SetCutScene("CutScene_05_", 301);
}

void Stage20::Update(float _DeltaTime)
{
    if (nullptr != LoadingActor_ && 0.f < LoadingActor_->GetAlpha())
    {
        float Ratio = 1.f - LoadingActor_->GetAlpha();
        StageSoundPlayer_.Volume(Ratio);
    }

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
                MassageTime_ += _DeltaTime;

                if (2.0f > MassageTime_)
                {
                    return;
                }

                if (false == MessageUI_->IsUpdate())
                {
                    MessageUI_->On();
                    MessageUI_->SpeechStart();
                }
            }
            break;
        case STAGEFLOW::BOSSCOMBAT:
            {
                if (1700.f > Penitent_->GetTransform().GetLocalPosition().x)
                {
                    Penitent_->GetTransform().SetWorldPosition(
                        {1700.f, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
                }

                else if (2900.f < Penitent_->GetTransform().GetLocalPosition().x)
                {
                    Penitent_->GetTransform().SetWorldPosition(
                        {2900.f, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
                }

                float4 CamPos = GetMainCameraActor()->GetTransform().GetLocalPosition();

                if (-1550 < CamPos.y)
                {
                    GetMainCameraActor()->GetTransform().SetWorldPosition({CamPos.x, -1550, CameraZPos_});
                }

                if (true == Pope_->GetLose() && false == IsBGMStop_)
                {
                    IsBGMStop_ = true;
                    StageSoundPlayer_.Stop();

                    StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Prima Church Wind.wav", -1);
                    StageSoundPlayer_.Volume(1.f);
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
                    UIActor_->GetTransform().SetWorldPosition(
                        {PlayerReturnPos_.x, PlayerReturnPos_.y + 200.f, PlayerZ});
                }
            }
            break;
        case STAGEFLOW::BOSSDEAD:
            if (true == GetLoadingEnd())
            {
                SetLoadingEnd(false);
                Penitent::GetMainPlayer()->BossDeathUIOn(0);
            }

            PlayerCameraMove(_DeltaTime);
            break;
    }
}


void Stage20::End() {}

void Stage20::LevelStartEvent()
{
    LoadingActor_ = CreateActor<LoadingActor>();
    LoadingActor_->IsEntrance(true);

    CutScenePlayer_->SetCutScenePlayEnd(
        [&]()
        {
            LoadingActor_->On();
            LoadingActor_->IsEntrance(false);
            LoadingActor_->Exit("Stage30");
        });

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

        if (STAGEFLOW::BOSSCOMBAT == CurrentFlow_)
        {
            CurrentFlow_ = STAGEFLOW::BOSSDEAD;
            SetLoadingEnd(false);
            Penitent_->GetTransform().SetWorldPosition(PlayerReturnPos_);


            StageSoundPlayer_.Pause(false);
            StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Prima Church Wind.wav", -1);
            StageSoundPlayer_.Volume(0.f);
        }
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;


    if (STAGEFLOW::BOSSCOMBAT != CurrentFlow_)
    {
        StageSoundPlayer_.Pause(false);
        StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Prima Church.wav", -1);
        StageSoundPlayer_.Volume(0.f);
    }
}

void Stage20::LevelEndEvent() { StageBase::LevelEndEvent(); }

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
        CutScenePlayer_->CutScenePlay();
    }
}
