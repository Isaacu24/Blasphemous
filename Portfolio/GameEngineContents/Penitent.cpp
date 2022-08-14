#include "Penitent.h"
#include "PreCompile.h"
#include "GravityComponent.h"
#include "PlayerUI.h"

Penitent* Penitent::MainPlayer_ = nullptr;

Penitent::Penitent()
    : State_{}
    , PlayerUI_(nullptr)
    , Gravity_(nullptr)
    , Collider_(nullptr)
    , ColScale_(80, 150)
    , Renderer_(nullptr)
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
    Collider_->GetTransform().SetWorldScale({100.f, 180.f});
    Collider_->ChangeOrder(COLLISIONORDER::Player);
    Collider_->SetDebugSetting(CollisionType::CT_OBB, float4{0.0f, 0.0f, 1.0f, 0.5f});
    Collider_->GetTransform().SetWorldMove({0, 100});

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->GetTransform().SetWorldScale({100.f, 100.f});
    AttackCollider_->ChangeOrder(COLLISIONORDER::PlayerAttack);
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB, float4{0.3f, 0.0f, 1.0f, 0.5f});
    AttackCollider_->Off();

    DebugColliders_.resize(10);

    for (size_t i = 0; i < DebugColliders_.size(); i++)
    {
        DebugColliders_[i] = CreateComponent<GameEngineCollision>();
        DebugColliders_[i]->ChangeOrder(COLLISIONORDER::Debug);
        DebugColliders_[i]->SetDebugSetting(CollisionType::CT_AABB, float4{0.0f, 0.0f, 1.0f, 0.5f});
        DebugColliders_[i]->GetTransform().SetWorldScale({10.f, 10.f});
        DebugColliders_[i]->Off(); 
    }

    DebugColliders_[0]->On();
    DebugColliders_[0]->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x,
         (GetTransform().GetWorldPosition().y + CilmbY_)});  //사다리 타기 시 땅 감지

     DebugColliders_[1]->On();
     DebugColliders_[1]->GetTransform().SetWorldPosition(
         {GetTransform().GetWorldPosition().x + 20, (GetTransform().GetWorldPosition().y + 125)}); 
     DebugColliders_[1]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});

     DebugColliders_[2]->On();
     DebugColliders_[2]->GetTransform().SetWorldPosition(
         {GetTransform().GetWorldPosition().x - 20, GetTransform().GetWorldPosition().y + 125});
     DebugColliders_[2]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});

    // DebugColliders_[3]->On();
    // DebugColliders_[3]->GetTransform().SetWorldPosition(
    //     {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y - 50});
    // DebugColliders_[3]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});

    PlayerUI_ = GetLevel()->CreateActor<PlayerUI>();
    PlayerUI_->SetLevelOverOn();

    GetTransform().SetLocalScale({1, 1, 1});

    {
        Renderer_ = CreateComponent<GameEngineTextureRenderer>();

        Renderer_->GetTransform().SetWorldScale({250, 250});
        Renderer_->CreateFrameAnimationCutTexture("penintent_idle_anim",
                                                  {"penintent_idle_anim.png", 0, 12, 0.1f, true});
        Renderer_->CreateFrameAnimationCutTexture("penitent_sheathedIdle",
                                                  {"penitent_sheathedIdle.png", 0, 45, 0.1f, true});
        Renderer_->CreateFrameAnimationCutTexture("penitent_verticalattack_LVL3_anim",
                                                  {"penitent_verticalattack_LVL3_anim.png", 0, 23, 0.05f, true});
        Renderer_->CreateFrameAnimationCutTexture("penitent_climbledge_reviewed",
                                                  {"penitent_climbledge_reviewed.png", 0, 11, 0.1f, true});
        Renderer_->CreateFrameAnimationCutTexture("penitent_dodge_attack_LVL3",
                                                  {"penitent_dodge_attack_LVL3.png", 0, 26, 0.1f, true});
        Renderer_->CreateFrameAnimationCutTexture("penitent_falling_ahead_anim 1",
                                                  {"penitent_falling_ahead_anim 1.png", 0, 5, 0.1f, true});
        Renderer_->CreateFrameAnimationCutTexture("penitent_jumpoff_new",
                                                  {"penitent_jumpoff_new.png", 0, 4, 0.1f, true});

        Renderer_->SetPivot(PIVOTMODE::BOT);
    }

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
        GetLevel()->GetMainCameraActor()->FreeCameraModeOnOff();
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

    GameEngineDebug::OutPutString("PlayerState: " + State_.GetCurStateStateName());
}

void Penitent::End() {}

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
