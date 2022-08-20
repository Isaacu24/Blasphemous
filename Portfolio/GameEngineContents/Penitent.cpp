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
    , JumpForce_(float4::ZERO)
    , MetaRenderer_(nullptr)
    , ColMap_(nullptr)
    , HP_(100)
    , MP_(100)
    , Speed_(250.0f)
    , Tear_(0)
    , IsGround_(false)
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
        GameEngineInput::GetInst()->CreateKey("PenitenAttack", 'K');
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
    AttackCollider_->GetTransform().SetWorldScale({50.f, 100.f, 1.f});
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
    DebugColliders_[0]->SetDebugSetting(CollisionType::CT_AABB, float4{0.8f, 0.2f, 0.95f, 0.5f});

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
    PlayerUI_->SetTear(Tear_);

    GetTransform().SetLocalScale({2, 2, 1});
    SetAnimation();
    SetPlayerState();
}

void Penitent::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    DebugColliders_[0]->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x,
         (GetTransform().GetWorldPosition().y + CilmbY_)});  //사다리 타기 시 땅 감지

    GroundCheck();
    LadderCheck();
    CollisionCheck();

    if (false == IsOnInventory_ && true == GameEngineInput::GetInst()->IsDownKey("InventoryOn"))
    {
        IsOnInventory_ = true;
        PlayerUI_->Inventory_->On();
    }

    else if (true == IsOnInventory_ && true == GameEngineInput::GetInst()->IsDownKey("InventoryOn"))
    {
        IsOnInventory_ = false;
        PlayerUI_->Inventory_->Off();
    }

    GameEngineDebug::OutPutString("PlayerState: " + State_.GetCurStateStateName());

    GameEngineDebug::OutPutString("PenitentZ: " + std::to_string(GetTransform().GetWorldPosition().z));

    // GameEngineDebug::OutPutString("MousePosX: "
    //                               + std::to_string(GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().x));
    // GameEngineDebug::OutPutString("MousePosY: "
    //                               + std::to_string(GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor().y));
}

void Penitent::End() {}

void Penitent::SetAnimation()
{
    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penintent_idle_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penintent_idle_anim",
            {"penintent_idle_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_jump_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_jump_anim",
            {"penitent_jump_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_jump_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Fall"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penintent_standing_up");

        MetaRenderer_->CreateMetaAnimation(
            "penintent_standing_up",
            {"penintent_standing_up.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penintent_standing_up",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_dodge_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_dodge_anim",
            {"penitent_dodge_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_dodge_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penintent_start_run_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penintent_start_run_anim",
            {"penintent_start_run_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penintent_start_run_anim",
                                        [&](const FrameAnimation_DESC& _Info)
                                        { MetaRenderer_->ChangeMetaAnimation("penitent_running_anim"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_running_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_running_anim",
            {"penitent_running_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penintent_stop_run_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penintent_stop_run_anim",
            {"penintent_stop_run_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);

        MetaRenderer_->AnimationBindFrame(
            "penintent_stop_run_anim",
            [&](const FrameAnimation_DESC& _Info)
            {
                if (true == LeftObstacleCheck() || true == RightObstacleCheck())
                {
                    return;
                }

                GetTransform().SetWorldMove(Dir_ * 300.f * GameEngineTime::GetDeltaTime());
            });

        MetaRenderer_->AnimationBindEnd("penintent_stop_run_anim",
                                        [&](const FrameAnimation_DESC& _Info) 
            { 
                ChangeState("Idle"); 
            });
    }


    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("death_anim_blood");

        MetaRenderer_->CreateMetaAnimation(
            "death_anim_blood",
            {"death_anim_blood.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, false},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_sheathedIdle");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_sheathedIdle",
            {"penitent_sheathedIdle.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, false},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_falling_loop_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_falling_loop_anim",
            {"penitent_falling_loop_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_crouch_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_crouch_anim",
            {"penitent_crouch_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_crouch_up_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_crouch_up_anim",
            {"penitent_crouch_up_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_crouch_up_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_hangonledge_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_hangonledge_anim",
            {"penitent_hangonledge_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_climbledge_reviewed");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_climbledge_reviewed",
            {"penitent_climbledge_reviewed.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindFrame("penitent_climbledge_reviewed",
                                          [&](const FrameAnimation_DESC& _Info)
                                          {
                                              // if (5 > _Info.CurFrame)
                                              //{
                                              //     return;
                                              // }

                                              // if (0 < Dir_.x) //오른쪽
                                              //{
                                              //     GetTransform().SetWorldRightMove(200.f,
                                              //     GameEngineTime::GetDeltaTime());
                                              // }

                                              // else if (0 > Dir_.x)  //왼쪽
                                              //{
                                              //     GetTransform().SetWorldLeftMove(200.f,
                                              //     GameEngineTime::GetDeltaTime());
                                              // }
                                          });

        MetaRenderer_->AnimationBindEnd("penitent_climbledge_reviewed",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penintent_ladder_climb_loop_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penintent_ladder_climb_loop_anim",
            {"penintent_ladder_climb_loop_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penintent_ladder_up_from_ground");

        MetaRenderer_->CreateMetaAnimation(
            "penintent_ladder_up_from_ground",
            {"penintent_ladder_up_from_ground.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penintent_ladder_up_from_ground",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_ladder_down_from_ground_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_ladder_down_from_ground_anim",
            {"penitent_ladder_down_from_ground_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_ladder_down_from_ground_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    //스킬
    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_aura_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_aura_anim",
            {"penitent_aura_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, false},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_charged_attack_v2_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_charged_attack_v2_anim",
            {"penitent_charged_attack_v2_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, false},
            Data);
    }

    //공격
    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_attack_combo_1");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_attack_combo_1",
            {"penitent_attack_combo_1.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_attack_combo_1",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    MetaRenderer_->SetPivot(PIVOTMODE::BOT);    
}

void Penitent::SetPlayerState()
{
    State_.CreateStateMember("Freeze",
                             std::bind(&Penitent::FreezeUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::FreezeStart, this, std::placeholders::_1),
                             std::bind(&Penitent::FreezeEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Idle",
                             std::bind(&Penitent::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::IdleStart, this, std::placeholders::_1),
                             std::bind(&Penitent::IdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Move",
                             std::bind(&Penitent::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::MoveStart, this, std::placeholders::_1),
                             std::bind(&Penitent::MoveEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Jump",
                             std::bind(&Penitent::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::JumpStart, this, std::placeholders::_1),
                             std::bind(&Penitent::JumpEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Fall",
                             std::bind(&Penitent::FallUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::FallStart, this, std::placeholders::_1),
                             std::bind(&Penitent::FallEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Crouch",
                             std::bind(&Penitent::CrouchUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::CrouchStart, this, std::placeholders::_1),
                             std::bind(&Penitent::CrouchEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Slide",
                             std::bind(&Penitent::SlideUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::SlideStart, this, std::placeholders::_1),
                             std::bind(&Penitent::SlideEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Dangle",
                             std::bind(&Penitent::DangleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::DangleStart, this, std::placeholders::_1),
                             std::bind(&Penitent::DangleEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "LadderClimb",
        std::bind(&Penitent::LadderClimbUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&Penitent::LadderClimbStart, this, std::placeholders::_1),
        std::bind(&Penitent::LadderClimbEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Attack",
                             std::bind(&Penitent::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::AttackStart, this, std::placeholders::_1),
                             std::bind(&Penitent::AttackEnd, this, std::placeholders::_1));

    /*
    State_.CreateStateMember("Recovery",
                             std::bind(&Penitent::RecoveryUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::RecoveryStart, this, std::placeholders::_1));

    State_.CreateStateMember("Hit",
                             std::bind(&Penitent::HitUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::HitStart, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&Penitent::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::DeathStart, this, std::placeholders::_1));*/

    State_.ChangeState("Idle");
}
