#include "Penitent.h"
#include "PreCompile.h"
#include "GravityComponent.h"
#include "PlayerUI.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

Penitent* Penitent::MainPlayer_ = nullptr;

Penitent::Penitent()
    : State_{}
    , PlayerUI_(nullptr)
    , Gravity_(nullptr)
    , Collider_(nullptr)
    , ColScale_(80, 150)
    , MetaRenderer_(nullptr)
    , ColMap_(nullptr)
    , HP_(100)
    , MP_(100)
    , Speed_(250.0f)
    , Tear_(0)
    , IsGround_(false)
    , IsJump_(false)
    , Flasks_{}
    , JumpTime_(0.0f)
{
    MainPlayer_ = this;
}

Penitent::~Penitent() {}

void Penitent::Start()
{
    if (false == GameEngineInput::GetInst()->IsButton("PenitentA"))
    {
        GameEngineInput::GetInst()->CreateButton("PenitentA", GAMEPAD_A);
        GameEngineInput::GetInst()->CreateButton("PenitentX", GAMEPAD_X);
        GameEngineInput::GetInst()->CreateButton("PenitentB", GAMEPAD_B);
        GameEngineInput::GetInst()->CreateButton("PenitentY", GAMEPAD_Y);

        GameEngineInput::GetInst()->CreateButton("PenitentLeftShoulder", GAMEPAD_LEFT_SHOULDER);  // LB
        GameEngineInput::GetInst()->CreateButton("PenitentRightShoulder", GAMEPAD_RIGHT_SHOULDER);

        GameEngineInput::GetInst()->CreateButton("PenitentLeftThumb", GAMEPAD_LEFT_THUMB);
        GameEngineInput::GetInst()->CreateButton("PenitentRightThumb", GAMEPAD_RIGHT_THUMB);
    }

    if (false == GameEngineInput::GetInst()->IsKey("PenitentLeft"))
    {
        GameEngineInput::GetInst()->CreateKey("PenitentLeft", 'A');
        GameEngineInput::GetInst()->CreateKey("PenitentRight", 'D');
        GameEngineInput::GetInst()->CreateKey("PenitentUp", 'W');
        GameEngineInput::GetInst()->CreateKey("PenitentDown", 'S');
        GameEngineInput::GetInst()->CreateKey("PenitentJump", VK_SPACE);
        GameEngineInput::GetInst()->CreateKey("PenitentSlide", VK_LSHIFT);
        GameEngineInput::GetInst()->CreateKey("PenitentRecovery", 'F');
        GameEngineInput::GetInst()->CreateKey("FreeCamera", 'O');

        GameEngineInput::GetInst()->CreateKey("PenitentAnimation", '1');
        GameEngineInput::GetInst()->CreateKey("InventoryOn", 'I');
    }

    Flasks_.resize(3);

    for (size_t i = 0; i < Flasks_.size(); i++)
    {
        Flasks_[i] = true;
    }

    Gravity_ = CreateComponent<GravityComponent>();

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->GetTransform().SetWorldScale({50.f, 90.f, 1.f});
    Collider_->ChangeOrder(COLLISIONORDER::Player);
    Collider_->SetDebugSetting(CollisionType::CT_OBB, float4{0.0f, 0.0f, 1.0f, 0.5f});
    Collider_->GetTransform().SetWorldMove({0, 30, 1.f});

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->GetTransform().SetWorldScale({50.f, 50.f, 1.f});
    AttackCollider_->ChangeOrder(COLLISIONORDER::PlayerAttack);
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB, float4{0.3f, 0.0f, 1.0f, 0.5f});
    AttackCollider_->Off();

    DebugColliders_.resize(10);

    for (size_t i = 0; i < DebugColliders_.size(); i++)
    {
        DebugColliders_[i] = CreateComponent<GameEngineCollision>();
        DebugColliders_[i]->ChangeOrder(COLLISIONORDER::Debug);
        DebugColliders_[i]->SetDebugSetting(CollisionType::CT_AABB, float4{0.0f, 0.0f, 1.0f, 0.5f});
        DebugColliders_[i]->GetTransform().SetWorldScale({5.f, 5.f, 1.f});
        DebugColliders_[i]->Off();
    }

    DebugColliders_[0]->On();
    DebugColliders_[0]->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x,
         (GetTransform().GetWorldPosition().y + CilmbY_)});  //사다리 타기 시 땅 감지

    DebugColliders_[1]->On();
    DebugColliders_[1]->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x + 20, (GetTransform().GetWorldPosition().y + 30)});
    DebugColliders_[1]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});

    DebugColliders_[2]->On();
    DebugColliders_[2]->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x - 20, GetTransform().GetWorldPosition().y + 30});
    DebugColliders_[2]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});

    // DebugColliders_[3]->On();
    // DebugColliders_[3]->GetTransform().SetWorldPosition(
    //     {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y - 50});
    // DebugColliders_[3]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});

    PlayerUI_ = GetLevel()->CreateActor<PlayerUI>();
    PlayerUI_->SetLevelOverOn();

    SetAnimation();

    GetTransform().SetLocalScale({2, 2, 1});

    State_.CreateStateMember("Freeze",
                             std::bind(&Penitent::FreezeUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::FreezeStart, this, std::placeholders::_1));
    State_.CreateStateMember("Idle",
                             std::bind(&Penitent::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::IdleStart, this, std::placeholders::_1));
    State_.CreateStateMember(
        "LadderClimb",
        std::bind(&Penitent::LadderClimbUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&Penitent::LadderClimbStart, this, std::placeholders::_1));
    State_.CreateStateMember("Jump",
                             std::bind(&Penitent::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::JumpStart, this, std::placeholders::_1));
    State_.CreateStateMember("Slide",
                             std::bind(&Penitent::SlideUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::SlideStart, this, std::placeholders::_1),
                             std::bind(&Penitent::SlideEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Crouch",
                             std::bind(&Penitent::CrouchUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::CrouchStart, this, std::placeholders::_1),
                             std::bind(&Penitent::CrouchEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Dangle",
                             std::bind(&Penitent::DangleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::DangleStart, this, std::placeholders::_1),
                             std::bind(&Penitent::DangleEnd, this, std::placeholders::_1));
    State_.CreateStateMember("Recovery",
                             std::bind(&Penitent::RecoveryUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::RecoveryStart, this, std::placeholders::_1));
    State_.CreateStateMember("Hit",
                             std::bind(&Penitent::HitUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::HitStart, this, std::placeholders::_1));
    State_.CreateStateMember("Death",
                             std::bind(&Penitent::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::DeathStart, this, std::placeholders::_1));

    State_.ChangeState("Idle");

    PlayerUI_->SetTear(Tear_);
}

void Penitent::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    DebugColliders_[0]->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x,
         (GetTransform().GetWorldPosition().y + CilmbY_)});  //사다리 타기 시 땅 감지

    if (false == HealthCheck())
    {
        return;
    }

    GroundCheck();
    LadderCheck();
    CollisionCheck();

    if (true == GameEngineInput::GetInst()->IsDownKey("FreeCamera"))
    {
        // GetLevel()->GetMainCameraActor()->FreeCameraModeOnOff();
    }

    if (false == IsInventory_ && true == GameEngineInput::GetInst()->IsDownKey("InventoryOn"))
    {
        IsInventory_ = true;
        PlayerUI_->Inventory_->On();
    }

    else if (true == IsInventory_ && true == GameEngineInput::GetInst()->IsDownKey("InventoryOn"))
    {
        IsInventory_ = false;
        PlayerUI_->Inventory_->Off();
    }

    // GameEngineDebug::OutPutString("PlayerState: " + State_.GetCurStateStateName());

    GameEngineDebug::OutPutString("MousePosX: "
                                  + std::to_string(GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().x));
    GameEngineDebug::OutPutString("MousePosY: "
                                  + std::to_string(GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().y));
}

void Penitent::End() {}

void Penitent::SetAnimation()
{
    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penintent_idle_anim 1");

        MetaRenderer_->CreateMetaAnimation(
            "penintent_idle_anim 1",
            {"penintent_idle_anim 1.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_aura_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_aura_anim",
            {"penitent_aura_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_jump_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_jump_anim",
            {"penitent_jump_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_dodge_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_dodge_anim",
            {"penitent_dodge_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_dodge_anim",
                                        std::bind(&Penitent::ChangeIdleState, this, std::placeholders::_1));
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_running_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_running_anim",
            {"penitent_running_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("death_anim_blood");

        MetaRenderer_->CreateMetaAnimation(
            "death_anim_blood",
            {"death_anim_blood.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, true},
            Data);
    }

    MetaRenderer_->SetPivot(PIVOTMODE::BOT);
}

bool Penitent::HealthCheck()
{
    if (0 >= HP_)
    {
        HP_ = 0;
        ChangeState("Death");

        return false;
    }

    return true;
}
