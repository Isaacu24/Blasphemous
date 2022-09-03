#include "PreCompile.h"
#include "Stage10.h"
#include "Penitent.h"
#include "Crosscrawler.h"
#include "BreakableTwistedCorpse.h"
#include "ShieldMaiden.h"
#include "LionHead.h"

Stage10::Stage10() {}

Stage10::~Stage10() {}


void Stage10::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("2_1_Colmap.png");
    ColMap_->ScaleToTexture();

    float ColmapZ = AO_COLMAP;
    ColMap_->GetTransform().SetWorldPosition({0, 0, ColmapZ});

    GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer->SetTexture("2_1_BeforeParallax_0.png");
    BeforeParallaxRenderer->ScaleToTexture();
    float BeforeParallaxZ = AO_BEFOREPARALLAX0;
    BeforeParallaxRenderer->GetTransform().SetWorldPosition({0, 0, BeforeParallaxZ});
    BeforeParallaxRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::BeforeParallax2)});
    BeforeParallaxRenderer->GetTransform().SetWorldScale(BeforeParallaxRenderer->GetTransform().GetWorldScale() * 2.0f);

    GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer1->SetTexture("2_1_BeforeParallax_1.png");
    BeforeParallaxRenderer1->ScaleToTexture();
    float BeforeParalla1Z = AO_BEFOREPARALLAX1;
    BeforeParallaxRenderer1->GetTransform().SetWorldPosition({0, 0, BeforeParalla1Z});
    BeforeParallaxRenderer1->GetTransform().SetWorldScale(BeforeParallaxRenderer1->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer2->SetTexture("2_1_BeforeParallax_2.png");
    BeforeParallaxRenderer2->ScaleToTexture();
    float BeforeParalla2Z = AO_BEFOREPARALLAX2;
    BeforeParallaxRenderer2->GetTransform().SetWorldPosition({0, 0, BeforeParalla2Z});
    BeforeParallaxRenderer2->GetTransform().SetWorldScale(BeforeParallaxRenderer2->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer3->SetTexture("2_1_BeforeParallax_3.png");
    BeforeParallaxRenderer3->ScaleToTexture();
    float BeforeParalla3Z = AO_BEFOREPARALLAX3;
    BeforeParallaxRenderer3->GetTransform().SetWorldPosition({0, 0, BeforeParalla3Z});
    BeforeParallaxRenderer3->GetTransform().SetWorldScale(BeforeParallaxRenderer3->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* StageRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRenderer->SetTexture("2_1_Tile.png");
    StageRenderer->ScaleToTexture();
    float TileZ = AO_TILE;
    StageRenderer->GetTransform().SetWorldPosition({0, 0, TileZ});
    StageRenderer->GetTransform().SetWorldScale(StageRenderer->GetTransform().GetWorldScale() * 2.f);
    
    GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRenderer->SetTexture("2_1_Door.png");
    DoorRenderer->ScaleToTexture();
    float DOORZ = AO_DOOR;
    DoorRenderer->GetTransform().SetWorldPosition({0, 0, DOORZ});
    DoorRenderer->GetTransform().SetWorldScale(DoorRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* CrowRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    CrowRenderer->CreateFrameAnimationCutTexture("crow_idle_anim", {"crow_idle_anim.png", 0, 101, 0.1f, true});
    CrowRenderer->ChangeFrameAnimation("crow_idle_anim");
    CrowRenderer->ScaleToCutTexture(1);
    float ObjectZ = AO_OBJECT;
    CrowRenderer->GetTransform().SetWorldPosition({-1580, 555, ObjectZ});
    CrowRenderer->GetTransform().SetWorldScale(CrowRenderer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    float PlayerZ = AO_PLAYER;

    PlayerRightPos_ = float4{3950, -682, PlayerZ};
    PlayerLeftPos_  = float4{300, -682, PlayerZ};

    IsLeftExit_ = true;
}

void Stage10::SettingMonster()
{
    float MonsterZ = AO_MONSTER;

    Crosscrawler* CrosscrawlerClone = CreateActor<Crosscrawler>();
    CrosscrawlerClone->GetTransform().SetWorldPosition({2200, -1080, MonsterZ});
    CrosscrawlerClone->SetGround(ColMap_);
    MonsterList_.push_back(CrosscrawlerClone);

    ShieldMaiden* Maiden = CreateActor<ShieldMaiden>();
    Maiden->GetTransform().SetWorldPosition({1400, -682, MonsterZ});
    Maiden->SetGround(ColMap_);
    Maiden->SetSpeed(60.f);
    MonsterList_.push_back(Maiden);

    ShieldMaiden* Maiden1 = CreateActor<ShieldMaiden>();
    Maiden1->GetTransform().SetWorldPosition({2200, -682, MonsterZ});
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
        Collider->GetTransform().SetWorldPosition({980, -830});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.2f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::LeftLedge);
        Collider->GetTransform().SetWorldPosition({1210, -830});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.2f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::RightLedge);
        Collider->GetTransform().SetWorldPosition({2290, -830});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 1.0f, 1.0f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::LeftLedge);
        Collider->GetTransform().SetWorldPosition({2510, -830});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.2f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::RightLedge);
        Collider->GetTransform().SetWorldPosition({980, -960});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 1.0f, 1.0f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    //두번째 줄
    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::LeftLedge);
        Collider->GetTransform().SetWorldPosition({1010, -1235});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{0.5f, 0.21f, 0.6f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::RightLedge);
        Collider->GetTransform().SetWorldPosition({1200, -1235});
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
        Collider->GetTransform().SetWorldPosition({2810, -1220});
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
    SettingStage();
    SettingLedge();
}

void Stage10::Update(float _DeltaTime)
{
    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }

    GetMainCameraActor()->GetTransform().SetWorldPosition(
        {Penitent_->GetTransform().GetLocalPosition().x,
         Penitent_->GetTransform().GetLocalPosition().y + CameraOffset_,
         CameraZPos_});

    if (-500 < GetMainCameraActor()->GetTransform().GetLocalPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{GetMainCameraActor()->GetTransform().GetLocalPosition().x, -500, CameraZPos_});
    }

    if (-1680 > GetMainCameraActor()->GetTransform().GetLocalPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{GetMainCameraActor()->GetTransform().GetLocalPosition().x, -1680, CameraZPos_});
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

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage05");
    }

    if (4000 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage20");
    }
}

void Stage10::End() {}

void Stage10::LevelStartEvent()
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

    SettingMonster();
}

void Stage10::LevelEndEvent() {}
