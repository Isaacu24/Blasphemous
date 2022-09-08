#include "PreCompile.h"
#include "Stage21.h"
#include "Penitent.h"
#include "Pontiff.h"
#include "Platform.h"

Stage21::Stage21() {}

Stage21::~Stage21() {}

void Stage21::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("12_3_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::ColMap)});

    GameEngineTextureRenderer* BeforeLayerRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeLayerRenderer->SetTexture("12_3_BeforeLayer_0.png");
    BeforeLayerRenderer->ScaleToTexture();
    BeforeLayerRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::BeforeLayer0)});
    BeforeLayerRenderer->GetTransform().SetWorldScale(BeforeLayerRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* BeforeLayerRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeLayerRenderer1->SetTexture("12_3_BeforeLayer_1.png");
    BeforeLayerRenderer1->ScaleToTexture();
    BeforeLayerRenderer1->GetTransform().SetWorldPosition({0, -5, static_cast<int>(ACTORORDER::BeforeLayer2)});
    BeforeLayerRenderer1->GetTransform().SetWorldScale(BeforeLayerRenderer1->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("12_3_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::AfterLayer0)});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    GetMainCameraActor()->GetTransform().SetWorldPosition({1260, -670});
}

void Stage21::SettingMonster()
{
    Pontiff_ = CreateActor<Pontiff>();
    Pontiff_->GetTransform().SetWorldPosition({1260, -520, static_cast<int>(ACTORORDER::BeforeLayer1)});
    Pontiff_->SetGround(ColMap_);
    Pontiff_->CreateSpawner();
    BossMonster_ = Pontiff_;
}

void Stage21::Start()
{
    SettingStage();
    SettingMonster();

    CurrentFlow_ = STAGEFLOW::BOSSAPPEAR;
}

void Stage21::Update(float _DeltaTime)
{
    switch (CurrentFlow_)
    {
        case STAGEFLOW::NORMAL:
            break;
        case STAGEFLOW::BOSSAPPEAR:
            if ("Appear" != Pontiff_->GetState())
            {
                CurrentFlow_ = STAGEFLOW::BOSSCOMBAT;
            }
            break;
        case STAGEFLOW::BOSSCOMBAT:
            if (true == Pontiff_->GetLose())
            {
                CurrentFlow_ = STAGEFLOW::BOSSDEAD;
            }
            break;
        case STAGEFLOW::BOSSDEAD:
            GEngine::ChangeLevel("Stage20");
            break;
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
    float4 PlayerPos = Penitent_->GetTransform().GetWorldPosition() + float4{0, 300};
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
            float4{680, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player)});
    }

    else if (1810 < Penitent_->GetTransform().GetWorldPosition().x)
    {
        Penitent_->GetTransform().SetWorldPosition(
            float4{1810, Penitent_->GetTransform().GetWorldPosition().y, static_cast<int>(ACTORORDER::Player)});
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

void Stage21::LevelEndEvent() 
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
            Guilt_->GetTransform().SetLocalPosition({Penitent_->GetTransform().GetWorldPosition().x,
                                                     Penitent_->GetTransform().GetWorldPosition().y,
                                                     static_cast<int>(ACTORORDER::Object)});
        }
    }
}
