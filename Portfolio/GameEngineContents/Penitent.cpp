#include "Penitent.h"
#include "PreCompile.h"
#include "GravityComponent.h"
#include "PlayerUI.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"
#include "MoveEffect.h"
#include "HitEffect.h"
#include "AttackEffect.h"

Penitent* Penitent::MainPlayer_ = nullptr;

Penitent::Penitent()
    : State_{}
    , PlayerUI_(nullptr)
    , Gravity_(nullptr)
    , BodyCollider_(nullptr)
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
        GameEngineInput::GetInst()->CreateKey("PenitentAttack", 'K');
        GameEngineInput::GetInst()->CreateKey("PenitentParry", 'J');
        GameEngineInput::GetInst()->CreateKey("PenitentTelport", 'B');
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

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->GetTransform().SetWorldScale({40.f, 80.f, 1.f});
    BodyCollider_->ChangeOrder(COLLISIONORDER::Player);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldMove({0, 30});

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->GetTransform().SetWorldScale({50.f, 50.f, 1.f});
    AttackCollider_->ChangeOrder(COLLISIONORDER::PlayerAttack);
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    AttackCollider_->Off();

    PlatformCollider_ = CreateComponent<GameEngineCollision>();
    PlatformCollider_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y});
    PlatformCollider_->GetTransform().SetWorldScale({10, 10, 1});
    PlatformCollider_->ChangeOrder(COLLISIONORDER::PlayerFoot);
    PlatformCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 0.0f, 1.f});

    PlatformUpCollider_ = CreateComponent<GameEngineCollision>();
    PlatformUpCollider_->GetTransform().SetWorldPosition(
        {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 1});
    PlatformUpCollider_->GetTransform().SetWorldScale({50, 10, 1});
    PlatformUpCollider_->ChangeOrder(COLLISIONORDER::PlayerFoot);
    PlatformUpCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.0f, 1.0f, 1.f});

    DebugColliders_.resize(10);

    for (size_t i = 0; i < DebugColliders_.size(); i++)
    {
        DebugColliders_[i] = CreateComponent<GameEngineCollision>();
        DebugColliders_[i]->ChangeOrder(COLLISIONORDER::Debug);
        DebugColliders_[i]->SetDebugSetting(CollisionType::CT_AABB, float4{0.0f, 0.0f, 1.0f, 0.5f});
        DebugColliders_[i]->GetTransform().SetWorldScale({5.f, 5.f, 1.f});
        DebugColliders_[i]->Off();
    }

    // DebugColliders_[0]->On();
    // DebugColliders_[0]->GetTransform().SetWorldPosition(
    //     {GetTransform().GetWorldPosition().x,
    //      (GetTransform().GetWorldPosition().y + CilmbY_)});  //사다리 타기 시 땅 감지
    // DebugColliders_[0]->SetDebugSetting(CollisionType::CT_AABB, float4{0.8f, 0.2f, 0.95f, 0.5f});

    // DebugColliders_[1]->On();
    // DebugColliders_[1]->GetTransform().SetWorldPosition(
    //     {GetTransform().GetWorldPosition().x + 20, (GetTransform().GetWorldPosition().y + 30)});
    // DebugColliders_[1]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});

    // DebugColliders_[2]->On();
    // DebugColliders_[2]->GetTransform().SetWorldPosition(
    //     {GetTransform().GetWorldPosition().x - 20, GetTransform().GetWorldPosition().y + 30});
    // DebugColliders_[2]->SetDebugSetting(CollisionType::CT_AABB, float4{1.0f, 0.5f, 0.25f, 0.5f});

    PlayerUI_ = GetLevel()->CreateActor<PlayerUI>();
    PlayerUI_->SetLevelOverOn();
    PlayerUI_->SetTear(Tear_);

    float EffectZ = AO_PLAYEREFFECT;

    MoveEffect_ = GetLevel()->CreateActor<MoveEffect>();
    MoveEffect_->GetTransform().SetWorldScale({2, 2, 1});
    MoveEffect_->GetTransform().SetLocalPosition({0, 0, EffectZ});
    MoveEffect_->SetLevelOverOn();

    AttackEffect_ = GetLevel()->CreateActor<AttackEffect>();
    AttackEffect_->GetTransform().SetWorldScale({2, 2, 1});
    AttackEffect_->GetTransform().SetLocalPosition({0, 0, EffectZ});
    AttackEffect_->SetLevelOverOn();

    HitEffect_ = GetLevel()->CreateActor<HitEffect>();
    HitEffect_->GetTransform().SetWorldScale({2, 2, 1});
    HitEffect_->GetTransform().SetLocalPosition({0, 0, EffectZ});
    HitEffect_->SetLevelOverOn();

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

        GameEngineTime::GetInst()->SetTimeScale(MetaRenderer_->GetOrder(), 0.0f);
        GameEngineTime::GetInst()->SetTimeScale(GetOrder(), 0.0f);
    }

    else if (true == IsOnInventory_ && true == GameEngineInput::GetInst()->IsDownKey("InventoryOn"))
    {
        IsOnInventory_ = false;
        PlayerUI_->Inventory_->Off();
        
        GameEngineTime::GetInst()->SetTimeScale(MetaRenderer_->GetOrder(), 1.0f);
        GameEngineTime::GetInst()->SetTimeScale(GetOrder(), 1.0f);
    }

    GameEngineDebug::OutPutString("PlayerState: " + State_.GetCurStateStateName());

    GameEngineDebug::OutPutString("Player HP: " + std::to_string(GetHP()));

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
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_jum_forward_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_jum_forward_anim",
            {"penitent_jum_forward_anim.png", 0, static_cast<unsigned int>(Data.size() - 4), 0.06f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_jum_forward_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Fall"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_jum_forward_fall_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_jum_forward_fall_anim",
            {"penitent_jum_forward_fall_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_jum_forward_fall_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Fall"); });
    }


    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_jumping_attack_noslashes");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_jumping_attack_noslashes",
            {"penitent_jumping_attack_noslashes.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindFrame("penitent_jumping_attack_noslashes",
                                          [&](const FrameAnimation_DESC& _Info)
                                          {
                                              switch (_Info.CurFrame)
                                              {
                                                  case 2:
                                                      AttackCollider_->On();
                                                      HitStack_ = 0;
                                                      break;
                                                  case 3:
                                                      if (true == IsHit_ || true == IsBossHit_)
                                                      {
                                                          HitEffect_->Renderer_->On();
                                                          IsHit_ = false;
                                                      }
                                                      break;
                                                  case 4:
                                                      AttackCollider_->Off();
                                                      break;
                                                  case 7:
                                                      AttackCollider_->On();
                                                      HitStack_ = 1;
                                                      break;
                                                  case 8:
                                                      if (true == IsHit_ || true == IsBossHit_)
                                                      {
                                                          HitEffect_->Renderer_->On();
                                                          IsHit_ = false;
                                                      }
                                                      break;
                                                  case 9:
                                                      AttackCollider_->Off();
                                                      break;
                                              }
                                          });

        MetaRenderer_->AnimationBindEnd("penitent_jumping_attack_noslashes",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Fall"); });
    }

    //점프 업 공격
    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_upward_attack_jump");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_upward_attack_jump",
            {"penitent_upward_attack_jump.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindFrame(
            "penitent_upward_attack_jump",
            [&](const FrameAnimation_DESC& _Info)
            {
                switch (_Info.CurFrame)
                {
                    case 4:
                        AttackCollider_->On();
                        HitStack_ = 0;
                        break;

                    case 5:
                        if (true == IsHit_ || true == IsBossHit_)
                        {
                            HitEffect_->Renderer_->On();
                            IsHit_ = false;
                        }
                        break;

                    case 6:
                        AttackCollider_->Off();
                        AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_upward_attack_slash_lvl1");
                        break;
                }
            });

        MetaRenderer_->AnimationBindEnd("penitent_upward_attack_jump",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Fall"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penintent_standing_up");

        MetaRenderer_->CreateMetaAnimation(
            "penintent_standing_up",
            {"penintent_standing_up.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penintent_standing_up",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_hardlanding_rocks_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_hardlanding_rocks_anim",
            {"penitent_hardlanding_rocks_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.06f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_hardlanding_rocks_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_dodge_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_dodge_anim",
            {"penitent_dodge_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindEnd(
            "penitent_dodge_anim",
            [&](const FrameAnimation_DESC& _Info)
            {
                if (true == GameEngineInput::GetInst()->IsFreeKey("PenitentRight")
                    && true == GameEngineInput::GetInst()->IsFreeKey("PenitentLeft"))
                {
                    MoveEffect_->Renderer_->On();
                    MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()
                                                                 + float4{RealXDir_ * 50.f, 0});
                    MoveEffect_->Renderer_->ChangeMetaAnimation("penitent_stop_dodge_dust_anim");
                }

                ChangeState("Idle");
            });
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

        MetaRenderer_->AnimationBindFrame(
            "penitent_running_anim",
            [&](const FrameAnimation_DESC& _Info)
            {
                if (0 == _Info.CurFrame || 2 == _Info.CurFrame || 4 == _Info.CurFrame || 6 == _Info.CurFrame)
                {
                    MoveEffect_->Renderer_->On();
                    MoveEffect_->Renderer_->ChangeMetaAnimation("penitent_running_dust_anim");

                    if (1 == RealXDir_)
                    {
                        MoveEffect_->GetTransform().PixLocalPositiveX();
                    }

                    else if (-1 == RealXDir_)
                    {
                        MoveEffect_->GetTransform().PixLocalNegativeX();
                    }

                    MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()
                                                                 + float4{-(RealXDir_ * 50.f), 0});
                }
            });
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
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_sheathedIdle");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_sheathedIdle",
            {"penitent_sheathedIdle.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_sheathedIdle",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
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

        MetaRenderer_->AnimationBindEnd("penitent_climbledge_reviewed",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penintent_ladder_climb_loop_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penintent_ladder_climb_loop_anim",
            {"penintent_ladder_climb_loop_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penintent_ladder_up_from_ground");

        MetaRenderer_->CreateMetaAnimation(
            "penintent_ladder_up_from_ground",
            {"penintent_ladder_up_from_ground.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penintent_ladder_up_from_ground",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_ladder_down_from_ground_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_ladder_down_from_ground_anim",
            {"penitent_ladder_down_from_ground_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_ladder_down_from_ground_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    //스킬
    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_charged_attack_v2_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_charged_attack_v2_anim",
            {"penitent_charged_attack_v2_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, false},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_dodge_attack_LVL3");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_dodge_attack_LVL3",
            {"penitent_dodge_attack_LVL3.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);

        MetaRenderer_->AnimationBindFrame("penitent_dodge_attack_LVL3",
                                          [&](const FrameAnimation_DESC& _Info)
                                          {
                                              switch (_Info.CurFrame)
                                              {
                                                  case 5:
                                                      AttackCollider_->On();
                                                      HitStack_ = 2;
                                                      break;

                                                  case 18:
                                                      AttackCollider_->Off();
                                                      break;
                                              }

                                              if (true == IsHit_ || true == IsBossHit_)
                                              {
                                                  HitEffect_->Renderer_->On();
                                                  IsHit_ = false;
                                              }
                                          });

        MetaRenderer_->AnimationBindEnd("penitent_dodge_attack_LVL3",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            ChangeState("Idle");
                                            HitEffect_->Renderer_->Off();
                                        });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_verticalattack_start_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_verticalattack_start_anim",
            {"penitent_verticalattack_start_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_verticalattack_start_anim",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            ReadySkill_ = true;
                                            MetaRenderer_->ChangeMetaAnimation("penitent_verticalattack_falling_anim");
                                        });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_verticalattack_falling_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_verticalattack_falling_anim",
            {"penitent_verticalattack_falling_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_verticalattack_landing");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_verticalattack_landing",
            {"penitent_verticalattack_landing.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_verticalattack_landing",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            BodyCollider_->On();
                                            ChangeState("Idle");
                                        });
    }


    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_verticalattack_landing_effects_anim");

        MetaRenderer_->CreateMetaAnimation("penitent_verticalattack_landing_effects_anim",
                                           {"penitent_verticalattack_landing_effects_anim.png",
                                            0,
                                            static_cast<unsigned int>(Data.size() - 1),
                                            0.1f,
                                            false},
                                           Data);
    }

    //기본 공격
    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_upward_attack_clamped_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_upward_attack_clamped_anim",
            {"penitent_upward_attack_clamped_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, true},
            Data);

        MetaRenderer_->AnimationBindFrame(
            "penitent_upward_attack_clamped_anim",
            [&](const FrameAnimation_DESC& _Info)
            {
                switch (_Info.CurFrame)
                {
                    case 5:
                        {
                            AttackCollider_->On();
                            HitStack_ = 0;

                            float EffectZ = AO_PLAYEREFFECT;

                            AttackEffect_->Renderer_->On();
                            AttackEffect_->GetTransform().SetWorldPosition(
                                {GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, EffectZ});
                            AttackEffect_->Renderer_->ChangeMetaAnimation("penitent_upward_attack_slash_lvl1");
                        }

                        break;

                    case 6:
                        if (true == IsHit_ || true == IsBossHit_)
                        {
                            HitEffect_->Renderer_->On();
                            IsHit_ = false;
                        }
                        break;

                    case 7:
                        AttackCollider_->Off();
                        break;
                }
            });
        {
            MetaRenderer_->AnimationBindEnd("penitent_upward_attack_clamped_anim",
                                            [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
        }
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_three_hits_attack_combo_no_slashes");

        MetaRenderer_->CreateMetaAnimation("penitent_three_hits_attack_combo_no_slashes",
                                           {"penitent_three_hits_attack_combo_no_slashes.png",
                                            0,
                                            static_cast<unsigned int>(Data.size() - 1),
                                            0.07f,
                                            true},
                                           Data);

        MetaRenderer_->AnimationBindFrame(
            "penitent_three_hits_attack_combo_no_slashes",
            [&](const FrameAnimation_DESC& _Info)
            {
                switch (_Info.CurFrame)
                {
                    case 4:
                        AttackCollider_->On();
                        HitStack_ = 0;

                        AttackEffect_->Renderer_->On();
                        AttackEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
                        AttackEffect_->Renderer_->ChangeMetaAnimation("three_hits_attack_slashes_lvl1_anim_0");
                        break;

                    case 5:
                        if (true == IsHit_ || true == IsBossHit_)
                        {
                            HitEffect_->Renderer_->On();
                            IsHit_ = false;
                        }
                        break;

                    case 7:
                        AttackCollider_->Off();

                        if (true == RightObstacleCheck() || true == LeftObstacleCheck())
                        {
                            ChangeState("Idle");
                            return;
                        }

                        if (0 < AttackStack_)  //유효타 공격 중
                        {
                            AttackStack_ = 0;
                            return;
                        }

                        ChangeState("Idle");
                        break;

                    case 8:
                        AttackEffect_->Renderer_->On();
                        AttackEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
                        AttackEffect_->Renderer_->ChangeMetaAnimation("three_hits_attack_slashes_lvl1_anim_1");
                        break;

                    case 10:
                        AttackCollider_->On();
                        HitStack_ = 1;
                        break;

                    case 11:
                        if (true == IsHit_ || true == IsBossHit_)
                        {
                            HitEffect_->Renderer_->On();
                            IsHit_ = false;
                        }
                        break;

                    case 13:
                        AttackCollider_->Off();

                        if (true == RightObstacleCheck() || true == LeftObstacleCheck())
                        {
                            ChangeState("Idle");
                            return;
                        }

                        if (1 < AttackStack_)  //유효타 공격 중
                        {
                            AttackStack_ = 0;
                            return;
                        }

                        ChangeState("Idle");

                        break;

                    case 18:
                        AttackEffect_->Renderer_->On();
                        AttackEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
                        AttackEffect_->Renderer_->ChangeMetaAnimation("three_hits_attack_slashes_lvl1_anim_2");
                        break;

                    case 19:
                        AttackCollider_->On();
                        HitStack_ = 2;
                        break;

                    case 20:
                        if (true == IsHit_ || true == IsBossHit_)
                        {
                            HitEffect_->Renderer_->On();
                            IsHit_ = false;
                        }
                        break;

                    case 22:
                        AttackCollider_->Off();
                }
            });

        MetaRenderer_->AnimationBindEnd("penitent_three_hits_attack_combo_no_slashes",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_getting_up_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_getting_up_anim",
            {"penitent_getting_up_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_getting_up_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }


    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("Penitent_pushback_grounded");

        MetaRenderer_->CreateMetaAnimation(
            "Penitent_pushback_grounded",
            {"Penitent_pushback_grounded.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);

        MetaRenderer_->AnimationBindFrame(
            "Penitent_pushback_grounded",
            [&](const FrameAnimation_DESC& _Info)
            {
                if (9 == _Info.CurFrame)
                {
                    MoveEffect_->Renderer_->On();
                }

                if (9 <= _Info.CurFrame)
                {
                    MoveEffect_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
                    MoveEffect_->Renderer_->ChangeMetaAnimation("penitent_pushback_grounded_dust_effect_anim");
                }
            });

        MetaRenderer_->AnimationBindEnd("Penitent_pushback_grounded",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_throwback_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_throwback_anim",
            {"penitent_throwback_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_throwback_anim",
                                        [&](const FrameAnimation_DESC& _Info)
                                        { MetaRenderer_->ChangeMetaAnimation("penitent_getting_up_anim"); });
    }

    //패링
    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_parry_failed");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_parry_failed",
            {"penitent_parry_failed.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.06f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_parry_failed",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    //회복
    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_healthpotion_consuming_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_healthpotion_consuming_anim",
            {"penitent_healthpotion_consuming_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.05f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_healthpotion_consuming_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    //죽음
    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("death_anim_blood");

        MetaRenderer_->CreateMetaAnimation(
            "death_anim_blood",
            {"death_anim_blood.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("death_anim_blood",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            if ("" == LastSavePoint_)
                                            {
                                                GEngine::ChangeLevel("Stage01");
                                            }

                                            else
                                            {
                                                GEngine::ChangeLevel(LastSavePoint_);
                                            }
                                            Off();
                                        });
    }

    //리스폰
    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_respawning_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_respawning_anim",
            {"penitent_respawning_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("penitent_respawning_anim",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    //텔레포트
    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("RegresoAPuerto-Prayer");

        MetaRenderer_->CreateMetaAnimation(
            "RegresoAPuerto-Prayer",
            {"RegresoAPuerto-Prayer.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("RegresoAPuerto-Prayer",
                                        [&](const FrameAnimation_DESC& _Info) { ChangeState("Idle"); });
    }

    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);
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

    State_.CreateStateMember("Landing",
                             std::bind(&Penitent::LandingUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::LandingStart, this, std::placeholders::_1),
                             std::bind(&Penitent::LandingEnd, this, std::placeholders::_1));

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

    State_.CreateStateMember("KnockBack",
                             std::bind(&Penitent::KnockBackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::KnockBackStart, this, std::placeholders::_1),
                             std::bind(&Penitent::KnockBackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("JumpAttack",
                             std::bind(&Penitent::JumpAttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::JumpAttackStart, this, std::placeholders::_1),
                             std::bind(&Penitent::JumpAttackEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "DodgeAttack",
        std::bind(&Penitent::DodgeAttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&Penitent::DodgeAttackStart, this, std::placeholders::_1),
        std::bind(&Penitent::DodgeAttackEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "VerticalAttack",
        std::bind(&Penitent::VerticalAttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&Penitent::VerticalAttackStart, this, std::placeholders::_1),
        std::bind(&Penitent::VerticalAttackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Parrying",
                             std::bind(&Penitent::ParryingUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::ParryingStart, this, std::placeholders::_1),
                             std::bind(&Penitent::ParryingEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Recovery",
                             std::bind(&Penitent::RecoveryUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::RecoveryStart, this, std::placeholders::_1),
                             std::bind(&Penitent::RecoveryEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "ReturnToPort",
        std::bind(&Penitent::ReturnToPortUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&Penitent::ReturnToPortStart, this, std::placeholders::_1),
        std::bind(&Penitent::ReturnToPortEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&Penitent::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::DeathStart, this, std::placeholders::_1),
                             std::bind(&Penitent::DeathEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Respawn",
                             std::bind(&Penitent::RespawnUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Penitent::RespawnStart, this, std::placeholders::_1),
                             std::bind(&Penitent::RespawnEnd, this, std::placeholders::_1));

    State_.ChangeState("Idle");
}
