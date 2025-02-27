#include "PreCompile.h"
#include "Stage10.h"
#include "Penitent.h"
#include "Crosscrawler.h"
#include "BreakableTwistedCorpse.h"
#include "ShieldMaiden.h"
#include "LionHead.h"
#include "DeadZone.h"

Stage10::Stage10() {}

Stage10::~Stage10() {}


void Stage10::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("2_1_Colmap.png");
    ColMap_->ScaleToTexture();

    ColMap_->GetTransform().SetWorldPosition({0, 0, ColmapZ});

    GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer->SetTexture("2_1_BeforeParallax_0.png");
    BeforeParallaxRenderer->ScaleToTexture();
    BeforeParallaxRenderer->GetTransform().SetWorldPosition({0, 100, BeforeParallaxZ});
    BeforeParallaxRenderer->GetTransform().SetWorldScale(BeforeParallaxRenderer->GetTransform().GetWorldScale() * 2.0f);

    GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer1->SetTexture("2_1_BeforeParallax_1.png");
    BeforeParallaxRenderer1->ScaleToTexture();
    BeforeParallaxRenderer1->GetTransform().SetWorldPosition({0, 0, BeforeParallax1Z});
    BeforeParallaxRenderer1->GetTransform().SetWorldScale(BeforeParallaxRenderer1->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer2->SetTexture("2_1_BeforeParallax_2.png");
    BeforeParallaxRenderer2->ScaleToTexture();
    BeforeParallaxRenderer2->GetTransform().SetWorldPosition({0, 0, BeforeParallax2Z});
    BeforeParallaxRenderer2->GetTransform().SetWorldScale(BeforeParallaxRenderer2->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer3->SetTexture("2_1_BeforeParallax_3.png");
    BeforeParallaxRenderer3->ScaleToTexture();
    BeforeParallaxRenderer3->GetTransform().SetWorldPosition({0, 0, BeforeParallax3Z});
    BeforeParallaxRenderer3->GetTransform().SetWorldScale(BeforeParallaxRenderer3->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("2_1_Tile.png");
    StageRenderer->ScaleToTexture();
    StageRenderer->GetTransform().SetWorldPosition({0, 0, TileZ});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRenderer->SetTexture("2_1_Door.png");
    DoorRenderer->ScaleToTexture();
    DoorRenderer->GetTransform().SetWorldPosition({0, 0, DoorZ});
    DoorRenderer->GetTransform().SetWorldScale(DoorRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* CrowRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    CrowRenderer->CreateFrameAnimationCutTexture("crow_idle_anim", {"crow_idle_anim.png", 0, 101, 0.1f, true});
    CrowRenderer->ChangeFrameAnimation("crow_idle_anim");
    CrowRenderer->ScaleToCutTexture(1);
    CrowRenderer->GetTransform().SetWorldPosition({-1580, 555, ObjectZ});
    CrowRenderer->GetTransform().SetWorldScale(CrowRenderer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{3950, -682, PlayerZ};
    PlayerLeftPos_  = float4{300, -682, PlayerZ};
    // PlayerLeftPos_  = float4{2500, -682, PlayerZ};
    // PlayerLeftPos_  = float4{1700, -850, PlayerZ};

    IsLeftExit_ = true;

    DeadZone* Zone = CreateActor<DeadZone>();
    Zone->GetTransform().SetWorldPosition({1500, -2500, 0});

    SettingMonster();
}

void Stage10::SettingMonster()
{
    Crosscrawler* CrosscrawlerClone = CreateActor<Crosscrawler>();
    CrosscrawlerClone->GetTransform().SetWorldPosition({2200, -1080, MonsterZ});
    CrosscrawlerClone->SetGround(ColMap_);
    MonsterList_.push_back(CrosscrawlerClone);

    ShieldMaiden* Maiden = CreateActor<ShieldMaiden>();
    Maiden->GetTransform().SetWorldPosition({1300, -682, MonsterZ});
    Maiden->SetGround(ColMap_);
    Maiden->SetSpeed(60.f);
    MonsterList_.push_back(Maiden);

    ShieldMaiden* Maiden1 = CreateActor<ShieldMaiden>();
    Maiden1->GetTransform().SetWorldPosition({2100, -682, MonsterZ});
    Maiden1->SetGround(ColMap_);
    Maiden1->PatrolStartEnd(false, true);
    MonsterList_.push_back(Maiden1);

    LionHead* LionHeadClone = CreateActor<LionHead>();
    LionHeadClone->GetTransform().SetWorldPosition({3600, -682, MonsterZ});
    LionHeadClone->GetTransform().PixLocalNegativeX();
    LionHeadClone->SetGround(ColMap_);
    LionHeadClone->SetStartPos(LionHeadClone->GetTransform().GetWorldPosition());
    MonsterList_.push_back(LionHeadClone);
};

void Stage10::SettingLedge()
{
    //첫번째 줄
    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::RightLedge);
        Collider->GetTransform().SetWorldPosition({975, -825});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.2f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::LeftLedge);
        Collider->GetTransform().SetWorldPosition({1210, -825});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.2f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::RightLedge);
        Collider->GetTransform().SetWorldPosition({2290, -825});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 1.0f, 1.0f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::LeftLedge);
        Collider->GetTransform().SetWorldPosition({2515, -825});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.2f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::RightLedge);
        Collider->GetTransform().SetWorldPosition({975, -960});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 1.0f, 1.0f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    //두번째 줄
    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::LeftLedge);
        Collider->GetTransform().SetWorldPosition({1015, -1225});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{0.5f, 0.21f, 0.6f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::RightLedge);
        Collider->GetTransform().SetWorldPosition({1195, -1225});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{0.5f, 0.21f, 0.6f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::LeftLedge);
        Collider->GetTransform().SetWorldPosition({1340, -1220});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{0.5f, 0.31f, 0.6f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::RightLedge);
        Collider->GetTransform().SetWorldPosition({1630, -1220});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 1.0f, 1.0f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::LeftLedge);
        Collider->GetTransform().SetWorldPosition({2520, -1220});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 1.0f, 1.0f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::RightLedge);
        Collider->GetTransform().SetWorldPosition({2820, -1220});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 1.0f, 1.0f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    //세번쨰 줄
    //{
    //    GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
    //    Collider->ChangeOrder(COLLISIONORDER::Handrail);
    //    Collider->GetTransform().SetWorldPosition({2920, -1350});
    //    Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
    //    Collider->SetDebugSetting(CollisionType::CT_AABB, float4{0.5f, 0.31f, 0.6f, 0.5f});
    //    DangleColiders_.push_back(Collider);
    //}

    //{
    //    GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
    //    Collider->ChangeOrder(COLLISIONORDER::Handrail);
    //    Collider->GetTransform().SetWorldPosition({3070, -1350});
    //    Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
    //    Collider->SetDebugSetting(CollisionType::CT_AABB, float4{0.5f, 0.31f, 0.6f, 0.5f});
    //    DangleColiders_.push_back(Collider);
    //}
}

void Stage10::Start()
{
    StageBase::Start();

    SettingStage();
    SettingLedge();
}

void Stage10::Update(float _DeltaTime)
{
    StageBase::Update(_DeltaTime);

    if (nullptr != LoadingActor_ && 0.f < LoadingActor_->GetAlpha())
    {
        float Ratio = 1.f - LoadingActor_->GetAlpha();
        StageSoundPlayer_.Volume(Ratio);
    }

    float4 CamPos    = GetMainCameraActor()->GetTransform().GetWorldPosition();
    float4 PlayerPos = Penitent_->GetTransform().GetWorldPosition() + float4{0, CameraOffset_};
    float4 CurPos    = float4::LerpLimit(CamPos, PlayerPos, _DeltaTime * 3);

    GetMainCameraActor()->GetTransform().SetWorldPosition({CurPos.x, CurPos.y, CameraZPos_});

    if (-500 < GetMainCameraActor()->GetTransform().GetLocalPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{GetMainCameraActor()->GetTransform().GetLocalPosition().x, -500, CameraZPos_});
    }

    if (-1650 > GetMainCameraActor()->GetTransform().GetLocalPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{GetMainCameraActor()->GetTransform().GetLocalPosition().x, -1650, CameraZPos_});
    }

    if (780 > GetMainCameraActor()->GetTransform().GetLocalPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{780, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (3450 < GetMainCameraActor()->GetTransform().GetLocalPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{3450, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (250 > Penitent_->GetTransform().GetWorldPosition().x && false == IsLeftExit_)
    {
        IsLeftExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage05");
    }

    if (4000 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        LoadingActor_->On();
        LoadingActor_->IsEntrance(false);
        LoadingActor_->Exit("Stage20");
    }

    if (true == GetLoadingEnd())
    {
        SetLoadingEnd(false);

        if (nullptr != GEngine::GetPrevLevel())
        {
            if ("STAGE05" == GEngine::GetPrevLevel()->GetNameConstRef())
            {
                Milestone* MilestoneUI = CreateActor<Milestone>();
                MilestoneUI->SetTownName("거룩한 금지의 벽");
            }
        }
    }
}

void Stage10::End() {}

void Stage10::LevelStartEvent()
{
    LoadingActor_ = CreateActor<LoadingActor>();
    LoadingActor_->IsEntrance(true);

    if (nullptr == Penitent::GetMainPlayer())
    {
        Penitent_ = CreateActor<Penitent>(ACTORORDER::Player);
        Penitent_->GetTransform().SetWorldPosition(PlayerLeftPos_);
        Penitent_->SetGround(ColMap_);

        Penitent_->SetLevelOverOn();
        Penitent_->SetLastSavePoint("Stage03");
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

    StageSoundPlayer_ = GameEngineSound::SoundPlayControl("Bridge.wav", -1);
    StageSoundPlayer_.Volume(0.f);
}

void Stage10::LevelEndEvent() 
{
    StageBase::LevelEndEvent(); 
}
