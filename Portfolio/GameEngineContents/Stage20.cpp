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
    ReturnKey_->Off();

    LineUIActor_ = CreateActor<LineUIActor>();
    LineUIActor_->SetSpeed(10.f);
    LineUIActor_->AddLine("�� �ӿ��� ���� �ٰ����� �״��� �߼Ҹ��� �����. \n�� �ӿ��� ���� �״뿡�� ���� �ɰ� "
                          "�λ縦 �Ϸ� �ߴ�.",
                          "DLG_2501_0.wav");
    LineUIActor_->AddLine("������ ��ȣ������, ������ ����� ��Ű�� ��ȣ���� ���� \nū ������ �������� �ƹ����� "
                          "������ ���ϰ� �����̶�.",
                          "DLG_2501_1.wav");
    LineUIActor_->AddLine("���� �������̷� ���� �� ���̸�, \n������� �ü��� ���ϴ� �� ���̴϶�.", "DLG_2501_2.wav");
    LineUIActor_->AddLine("�׷��� �� ������ �̸� ���� ��� �ܿ���, �״븦 �𸥴�.", "DLG_2501_3.wav");
    LineUIActor_->AddLine("�״��� ��ó������ ���� �� ���� ���� ����϶�. \n�״��� ������ ������ ����϶�.",
                          "DLG_2501_4.wav");
    LineUIActor_->AddLine("�ƴ�, �״븦 �ƴ� �� ���� ���̴�", "DLG_2501_5.wav");
    LineUIActor_->AddLine("�˸� ���� ������ �״��� Į��, \nȲ�ݿ� ������ ���� Į�� �ºε������� ����.",
                          "DLG_2503_0.wav");
    LineUIActor_->AddLine("��ó�� ������, �Ȱ� �ϸ���.", "DLG_2503_1.wav");
    LineUIActor_->AddLine("�״��� �̸��� ���� ������ �����ϸ���.", "DLG_2503_2.wav");
    LineUIActor_->AddLine("�״��� ������ ���� ������ �ູ�ϸ���.", "DLG_2503_3.wav");
    LineUIActor_->SetFontColor(float4{0.63f, 0.6f, 0.55f});
    LineUIActor_->SetBackgroudAlpha(0.5f);
    LineUIActor_->SetSpeed(5.f);
    LineUIActor_->Off();

    LineUIActor_->SetLineStartEvent(0, [&]() { Penitent_->SetIsFreezeEnd(false); });

    LineUIActor_->SetLineStartEvent(5,
                                       [&]()
                                       {
                                           Pope_->On();
                                           Pope_->GetTransform().PixLocalNegativeX();
                                           Pope_->ChangeMonsterState("AppearEvent");
                                           Pope_->SetTarget(Penitent_);
                                       });

    LineUIActor_->SetLineEndEvent(10,
                                     [&]()
                                     {
                                         StageFlow_.ChangeState("BossCombat");

                                         Penitent_->SetIsFreezeEnd(true);
                                         Pope_->ChangeMonsterState("Idle");
                                         LineUIActor_->Off();

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
    StageBase::Start();

    SettingStage();
    SettingMonster();

    CutScenePlayer_ = CreateActor<CutScenePlayer>();
    CutScenePlayer_->SetCutScene("CutScene_05_", 301);
    CutScenePlayer_->Off();
}

void Stage20::Update(float _DeltaTime)
{
    StageBase::Update(_DeltaTime);

    if (nullptr != LoadingActor_ && 0.f < LoadingActor_->GetAlpha())
    {
        float Ratio = 1.f - LoadingActor_->GetAlpha();
        StageSoundPlayer_.Volume(Ratio);
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

        if (StageFlow_.GetCurStateStateName() == "BossCombat")
        {
            StageFlow_.ChangeState("BossDead");
            SetLoadingEnd(false);
            Penitent_->GetTransform().SetWorldPosition(PlayerReturnPos_);


            StageSoundPlayer_.Pause(false);
            StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Prima Church.wav", -1);
            StageSoundPlayer_.Volume(0.f);
        }
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;

    if (StageFlow_.GetCurStateStateName() != "BossCombat")
    {
        StageSoundPlayer_.Pause(false);
        StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Prima Church Wind.wav", -1);
        StageSoundPlayer_.Volume(0.f);
    }
}

void Stage20::LevelEndEvent() { StageBase::LevelEndEvent(); }

void Stage20::PlayerCameraMove(float _DeltaTime)
{
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

        CutScenePlayer_->On();
        CutScenePlayer_->CutScenePlay();
    }
}


void Stage20::NormallyStart(const StateInfo& _Info) {}

void Stage20::NormallyUpdate(float _DeltaTime, const StateInfo& _Info)
{
    PlayerCameraMove(_DeltaTime);

    if (2000.f <= Penitent_->GetTransform().GetWorldPosition().x)
    {
        StageFlow_.ChangeState("BossAppear");
    }
}

void Stage20::NormallyEnd(const StateInfo& _Info) { Penitent_->ChangeState("Freeze"); }


void Stage20::BossAppearStart(const StateInfo& _Info) {}

void Stage20::BossAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
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

        if (false == LineUIActor_->IsUpdate())
        {
            LineUIActor_->On();
            LineUIActor_->SpeechStart();
        }
    }
}

void Stage20::BossAppearEnd(const StateInfo& _Info) {}


void Stage20::BossCombatStart(const StateInfo& _Info) {}

void Stage20::BossCombatUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (1700.f > Penitent_->GetTransform().GetLocalPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition({1700.f, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
    }

    else if (2900.f < Penitent_->GetTransform().GetLocalPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition({2900.f, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
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

        Penitent_->SetReturnToPort(true);
    }

    if (true == Pope_->IsDeath())
    {
        if ("ReturnToPort" == Penitent_->GetPenitentState())
        {
            ReturnKey_->Off();
            return;
        }

        PlayerReturnPos_ = Penitent_->GetTransform().GetWorldPosition();

        ReturnKey_->On();
        UIActor_->GetTransform().SetWorldPosition({PlayerReturnPos_.x, PlayerReturnPos_.y + 200.f, PlayerZ});
    }
}

void Stage20::BossCombatEnd(const StateInfo& _Info) {}


void Stage20::BossDeadStart(const StateInfo& _Info) {}

void Stage20::BossDeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
    PlayerCameraMove(_DeltaTime);

    if (true == GetLoadingEnd())
    {
        SetLoadingEnd(false);
        Penitent::GetMainPlayer()->BossDeathUIOn(0);
    }
}

void Stage20::BossDeadEnd(const StateInfo& _Info) {}
