#include "PreCompile.h"
#include "Stage21.h"
#include "Penitent.h"
#include "Pontiff.h"
#include "Platform.h"
#include "TwisterBackground.h"
#include "Cloud.h"

Stage21::Stage21() {}

Stage21::~Stage21() {}

void Stage21::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("12_3_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, ColmapZ});

    GameEngineTextureRenderer* BeforeLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeLayerRenderer->SetTexture("12_3_BeforeLayer_0.png");
    BeforeLayerRenderer->ScaleToTexture();
    BeforeLayerRenderer->GetTransform().SetWorldPosition({0, 0, BeforeLayerZ});
    BeforeLayerRenderer->GetTransform().SetWorldScale(BeforeLayerRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* BeforeLayerRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeLayerRenderer1->SetTexture("12_3_BeforeLayer_1.png");
    BeforeLayerRenderer1->ScaleToTexture();
    BeforeLayerRenderer1->GetTransform().SetWorldPosition({0, -5, BeforeLayer2Z});
    BeforeLayerRenderer1->GetTransform().SetWorldScale(BeforeLayerRenderer1->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("12_3_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, AfterLayerZ});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    {
        Cloud* NewCloud = CreateActor<Cloud>();
        NewCloud->SetDirection(float4::RIGHT);
        NewCloud->GetTransform().SetWorldPosition({1260, -670, AfterLayerZ});
    }

    {
        Cloud* NewCloud = CreateActor<Cloud>();
        NewCloud->GetRenderer()->SetTexture("ash-clouds_1.png");
        NewCloud->SetDirection(float4::LEFT);
        NewCloud->GetTransform().SetWorldPosition({1400, -670, AfterLayerZ});
    }

    {
        Cloud* NewCloud = CreateActor<Cloud>();
        NewCloud->GetRenderer()->SetTexture("ash-clouds_2.png");
        NewCloud->SetDirection(float4::RIGHT);
        NewCloud->GetTransform().SetWorldPosition({1100, -670, AfterLayerZ});
    }

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    GetMainCameraActor()->GetTransform().SetWorldPosition({1260, -670});
}

void Stage21::SettingMonster()
{
    Pontiff_ = CreateActor<Pontiff>();
    Pontiff_->GetTransform().SetWorldPosition({1260, -520, BeforeLayer1Z});
    Pontiff_->SetGround(ColMap_);
    Pontiff_->CreateSpawner();
    BossMonster_ = Pontiff_;

    {
        TwisterBackground* Twister = CreateActor<TwisterBackground>();
        Twister->GetTransform().SetWorldPosition({860, -600, BeforeLayerZ});
        Twister->GetRenderer()->GetColorData().MulColor = float4{0.5f, 0.5f, 0.5f, 0.75f};

        TwisterBackground* Twister1 = CreateActor<TwisterBackground>();
        Twister1->GetTransform().SetWorldPosition({1640, -600, BeforeLayerZ});
        Twister1->GetRenderer()->GetColorData().MulColor = float4{0.5f, 0.5f, 0.5f, 0.75f};
    }

    {
        TwisterBackground* Twister = CreateActor<TwisterBackground>();
        Twister->GetRenderer()->SetTexture("pontif-twister-foreground.png");
        Twister->GetTransform().SetWorldPosition({1280, -600, AfterLayerZ});
        Twister->GetTransform().SetWorldScale({2, 2, 1});
    }
}

void Stage21::Start()
{
    StageBase::Start();

    SettingStage();
    SettingMonster();

    StageFlow_.ChangeState("BossAppear");
}

void Stage21::Update(float _DeltaTime)
{
    StageBase::Update(_DeltaTime);

    if (1.f >= SoundRatio_)
    {
        SoundRatio_ += _DeltaTime;
        StageSoundPlayer_.Volume(SoundRatio_);
    }

    PlayerCameraMove(_DeltaTime);
}


void Stage21::PlayerCameraMove(float _DeltaTime)
{
    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }

    float4 CamPos    = GetMainCameraActor()->GetTransform().GetWorldPosition();
    float4 PlayerPos = Penitent_->GetTransform().GetWorldPosition() + float4{0, 275};
    float4 CurPos    = float4::LerpLimit(CamPos, PlayerPos, _DeltaTime * 3);

    GetMainCameraActor()->GetTransform().SetWorldPosition({1250, CurPos.y, CameraZPos_});

    if (-600 < GetMainCameraActor()->GetTransform().GetWorldPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            {GetMainCameraActor()->GetTransform().GetWorldPosition().x, -600, CameraZPos_});
    }

    if (680 > Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{680, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
    }

    else if (1810 < Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{1810, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
    }

    GameEngineDebug::OutPutString("x : " + std::to_string(Penitent_->GetTransform().GetLocalPosition().x));
    GameEngineDebug::OutPutString("y : " + std::to_string(Penitent_->GetTransform().GetLocalPosition().y));
}


void Stage21::End() {}

void Stage21::LevelStartEvent()
{
    if (nullptr == Penitent::GetMainPlayer())
    {
        Penitent_ = CreateActor<Penitent>(ACTORORDER::Player);
        Penitent_->GetTransform().SetWorldPosition({1250, -860, PlayerZ});
        Penitent_->SetGround(ColMap_);

        Penitent_->SetLevelOverOn();
    }

    else if (nullptr != Penitent::GetMainPlayer())
    {
        Penitent_ = Penitent::GetMainPlayer();
        Penitent_->GetTransform().SetWorldPosition({1250, -860, PlayerZ});
        Penitent_->SetGround(ColMap_);
    }

    if (350 > Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{350, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
    }

    if (2000 < Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{2000, Penitent_->GetTransform().GetWorldPosition().y, PlayerZ});
    }

    IsRightExit_ = false;
    IsLeftExit_  = false;

    StageSoundPlayer_.Pause(false);

    StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Final Boss Wind.wav", -1);
    StageSoundPlayer_.Volume(0.f);
}

void Stage21::LevelEndEvent()
{
    StageBase::LevelEndEvent();

    BackgorundPlayer_.Stop();
}

void Stage21::NormallyStart(const StateInfo& _Info) {}

void Stage21::NormallyUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Stage21::NormallyEnd(const StateInfo& _Info) {}


void Stage21::BossAppearStart(const StateInfo& _Info) {}

void Stage21::BossAppearUpdate(float _DeltaTime, const StateInfo& _Info) 
{
    if ("Appear" != Pontiff_->GetState())
    {
        StageFlow_.ChangeState("BossCombat");
    }
}

void Stage21::BossAppearEnd(const StateInfo& _Info) 
{
    BackgorundPlayer_ = GameEngineSound::SoundPlayControl("Pontiff.wav", -1);
    BackgorundPlayer_.Volume(1.f);
}


void Stage21::BossCombatStart(const StateInfo& _Info) {}

void Stage21::BossCombatUpdate(float _DeltaTime, const StateInfo& _Info) 
{
    if (true == Pontiff_->GetBossDeathEvent())
    {
        BackgorundPlayer_.Stop();
    }

    if (true == Pontiff_->GetLose())
    {
        StageFlow_.ChangeState("BossDead");
        BackgorundPlayer_.Stop();
    }
}

void Stage21::BossCombatEnd(const StateInfo& _Info) {}


void Stage21::BossDeadStart(const StateInfo& _Info) {}

void Stage21::BossDeadUpdate(float _DeltaTime, const StateInfo& _Info) 
{
    ChangeTime_ += _DeltaTime;

    if (1.5f <= ChangeTime_)
    {
        ChangeTime_ = 0.f;
        GEngine::ChangeLevel("Stage20");

        StageFlow_.ChangeState("Normally");
    }
}

void Stage21::BossDeadEnd(const StateInfo& _Info) {}
