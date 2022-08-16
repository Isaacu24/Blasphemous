#include "PreCompile.h"
#include "Stage02.h"
#include "Penitent.h"
#include "Fool_knife.h"
#include "WingedFace.h"

Stage02::Stage02() {}

Stage02::~Stage02() {}

void Stage02::SettingStage()
{
    Stage_ = CreateActor<StageActor>();

    ColMap_ = Stage_->CreateComponent<GameEngineTextureRenderer>();
    ColMap_->SetTexture("1_2_Colmap.png");
    ColMap_->ScaleToTexture();
    ColMap_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::ColMap)});

    GameEngineTextureRenderer* BeforeParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer->SetTexture("1_2_BeforeParallax_0.png");
    BeforeParallaxRenderer->ScaleToTexture();
    BeforeParallaxRenderer->GetTransform().SetWorldPosition({-100, 0, static_cast<int>(ACTORORDER::BeforeParallax0)});
    BeforeParallaxRenderer->GetTransform().SetWorldScale(BeforeParallaxRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer1 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer1->SetTexture("1_2_BeforeParallax_1.png");
    BeforeParallaxRenderer1->ScaleToTexture();
    BeforeParallaxRenderer1->GetTransform().SetWorldPosition(
        {-100, 170, static_cast<int>(ACTORORDER::BeforeParallax1)});
    BeforeParallaxRenderer1->GetTransform().SetWorldScale(BeforeParallaxRenderer1->GetTransform().GetWorldScale()
                                                          * 3.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer2 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer2->SetTexture("1_2_BeforeParallax_2.png");
    BeforeParallaxRenderer2->ScaleToTexture();
    BeforeParallaxRenderer2->GetTransform().SetWorldPosition(
        {-150, -290, static_cast<int>(ACTORORDER::BeforeParallax2)});
    BeforeParallaxRenderer2->GetTransform().SetWorldScale(BeforeParallaxRenderer2->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer3 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer3->SetTexture("1_2_BeforeParallax_3.png");
    BeforeParallaxRenderer3->ScaleToTexture();
    BeforeParallaxRenderer3->GetTransform().SetWorldPosition(
        {-100, -50, static_cast<int>(ACTORORDER::BeforeParallax3)});
    BeforeParallaxRenderer3->GetTransform().SetWorldScale(BeforeParallaxRenderer3->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* BeforeParallaxRenderer4 = Stage_->CreateComponent<GameEngineTextureRenderer>();
    BeforeParallaxRenderer4->SetTexture("1_2_BeforeParallax_4.png");
    BeforeParallaxRenderer4->ScaleToTexture();
    BeforeParallaxRenderer4->GetTransform().SetWorldPosition(
        {-150, -500, static_cast<int>(ACTORORDER::BeforeParallax4)});
    BeforeParallaxRenderer4->GetTransform().SetWorldScale(BeforeParallaxRenderer4->GetTransform().GetWorldScale()
                                                          * 2.f);

    GameEngineTextureRenderer* StageRendrer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    StageRendrer->SetTexture("1_2_Tile.png");
    StageRendrer->ScaleToTexture();
    StageRendrer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Tile)});
    StageRendrer->GetTransform().SetWorldScale(StageRendrer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* DoorRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    DoorRenderer->SetTexture("1_2_Door.png");
    DoorRenderer->ScaleToTexture();
    DoorRenderer->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Door)});
    DoorRenderer->GetTransform().SetWorldScale(DoorRenderer->GetTransform().GetWorldScale() * 2.f);

    GameEngineTextureRenderer* AfterParallaxRenderer = Stage_->CreateComponent<GameEngineTextureRenderer>();
    AfterParallaxRenderer->SetTexture("1_2_AfterParallax_0.png");
    AfterParallaxRenderer->ScaleToTexture();
    AfterParallaxRenderer->GetTransform().SetWorldPosition({-50, -150, static_cast<int>(ACTORORDER::AfterParallax0)});
    AfterParallaxRenderer->GetTransform().SetWorldScale(AfterParallaxRenderer->GetTransform().GetWorldScale() * 2.f);

    float OffsetX = ColMap_->GetTransform().GetLocalScale().x / 2;
    float OffsetY = ColMap_->GetTransform().GetLocalScale().y / 2;

    float4 Offset = {OffsetX, -OffsetY};

    Stage_->GetTransform().SetLocalMove(Offset);

    PlayerRightPos_ = float4{4050, -1561, static_cast<int>(ACTORORDER::Player)};
    PlayerLeftPos_  = float4{210, -1425, static_cast<int>(ACTORORDER::Player)};

    IsLeftExit_ = true;
}

void Stage02::SettingMonster()
{
    Fool_knife* FoolKnife = CreateActor<Fool_knife>();
    FoolKnife->GetTransform().SetWorldPosition({1300, -1289, static_cast<int>(ACTORORDER::Monster)});
    FoolKnife->SetGround(ColMap_);
    MonsterList_.push_back(FoolKnife);

    WingedFace* FlyingEnemy = CreateActor<WingedFace>();
    FlyingEnemy->GetTransform().SetWorldPosition({2150, -1250, static_cast<int>(ACTORORDER::Monster)});
    FlyingEnemy->SetGround(ColMap_);
    FlyingEnemy->SetStartPos(-1150);
    FlyingEnemy->SetEndPos(-1550);
    FlyingEnemy->GetTransform().SetWorldScale({2, 2, 1});
    MonsterList_.push_back(FlyingEnemy);
}

void Stage02::SettingHandrail() 
{
    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::Handrail);
        Collider->GetTransform().SetWorldPosition({1750, -1300});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{0.0f, 0.5f, 0.2f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::Handrail);
        Collider->GetTransform().SetWorldPosition({2000, -1300});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{0.0f, 0.5f, 0.2f, 0.5f});
        DangleColiders_.push_back(Collider);
    }

    {
        GameEngineCollision* Collider = Stage_->CreateComponent<GameEngineCollision>();
        Collider->ChangeOrder(COLLISIONORDER::Handrail);
        Collider->GetTransform().SetWorldPosition({2290, -1300});
        Collider->GetTransform().SetWorldScale({5.0f, 5.0f, 1.0f});
        Collider->SetDebugSetting(CollisionType::CT_AABB, float4{0.0f, 0.5f, 0.2f, 0.5f});
        DangleColiders_.push_back(Collider);
    }
}

void Stage02::Start()
{
    SettingStage();
    SettingHandrail();
    SettingMonster();
}

void Stage02::Update(float _DeltaTime)
{
    if (false == IsChangeCameraPos_)
    {
        GetMainCameraActor()->GetTransform().SetWorldMove({0, 0, CameraZPos_});
        IsChangeCameraPos_ = true;
    }

    GetMainCameraActor()->GetTransform().SetWorldPosition({Penitent_->GetTransform().GetLocalPosition().x,
                                                           Penitent_->GetTransform().GetLocalPosition().y + 200,
                                                           CameraZPos_});

    if (-1285 < GetMainCameraActor()->GetTransform().GetWorldPosition().y)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{Penitent_->GetTransform().GetLocalPosition().x, -1285, CameraZPos_});
    }

    if (700 > GetMainCameraActor()->GetTransform().GetWorldPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{700, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (3550 < GetMainCameraActor()->GetTransform().GetWorldPosition().x)
    {
        GetMainCameraActor()->GetTransform().SetWorldPosition(
            float4{3550, GetMainCameraActor()->GetTransform().GetLocalPosition().y, CameraZPos_});
    }

    if (150 > Penitent_->GetTransform().GetWorldPosition().x && false == IsLeftExit_)
    {
        IsLeftExit_ = true;

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage01");
    }

    if (4100 < Penitent_->GetTransform().GetWorldPosition().x && false == IsRightExit_)
    {
        IsRightExit_ = true;

        if (nullptr != LoadingActor_)
        {
            LoadingActor_->Death();
            LoadingActor_ = nullptr;
        }

        LoadingActor_ = CreateActor<LoadingActor>();
        LoadingActor_->Exit("Stage03");
    }
}

void Stage02::End() {}

void Stage02::OnEvent()
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
        Penitent_->GetTransform().GetLocalPosition() + float4{0, 100}
    });
}

void Stage02::OffEvent() {}
