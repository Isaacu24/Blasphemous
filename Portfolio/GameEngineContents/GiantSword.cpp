#include "PreCompile.h"
#include "GiantSword.h"
#include "Pontiff.h"

GiantSword::GiantSword() {}

GiantSword::~GiantSword() {}


void GiantSword::Start()
{
    BossMonster::Start();

    EyeRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    EyeRenderer_->SetTexture("pontiff_giantSword_eyeGlobeSprite.png");
    EyeRenderer_->GetTransform().SetLocalScale({125, 400});
    EyeRenderer_->SetPivot(PIVOTMODE::TOP);
    EyeRenderer_->Off();

    IrisRenderer_ = CreateComponent<GameEngineTextureRenderer>();
    IrisRenderer_->SetTexture("pontiff_giantSword_irisSprite.png");
    IrisRenderer_->GetTransform().SetLocalScale({125, 400});
    IrisRenderer_->SetPivot(PIVOTMODE::TOP);
    IrisRenderer_->Off();

    AttackAfterimage_ = CreateComponent<AfterimageComponent>();

    Renderer_ = CreateComponent<GameEngineTextureRenderer>();

    Renderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_teleportOUT",
                                              {"pontiff_giantSword_teleportOUT.png", 0, 19, 0.1f, false});

    Renderer_->AnimationBindEnd("pontiff_giantSword_teleportOUT",
                                [&](const FrameAnimation_DESC&)
                                {
                                    IrisRenderer_->On();
                                    EyeRenderer_->On();

                                    Renderer_->ChangeFrameAnimation("pontiff_giantSword_swordSprite");

                                    State_.ChangeState("Track");
                                });

    Renderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_teleportIN",
                                              {"pontiff_giantSword_teleportIN.png", 0, 26, 0.1f, false});

    Renderer_->AnimationBindEnd("pontiff_giantSword_teleportIN",
                                [&](const FrameAnimation_DESC&) { State_.ChangeState("Visible"); });

    Renderer_->CreateFrameAnimationCutTexture("pontiff_giantSword_swordSprite",
                                              {"pontiff_giantSword_swordSprite.png", 0, 0, 0.1f, false});

    AttackAfterimage_->CreateOnceAfterimage(
        "pontiff_giantSword_swordSprite", {"pontiff_giantSword_swordSprite.png", 0, 0, 0.1f, false}, 21);

    AttackAfterimage_->SetOnceAfterimageFrame(20);

    Renderer_->GetTransform().SetLocalScale({125, 400});
    Renderer_->SetPivot(PIVOTMODE::TOP);

    DetectCollider_ = CreateComponent<GameEngineCollision>();
    DetectCollider_->ChangeOrder(COLLISIONORDER::MonsterDetect);
    DetectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.9f, 0.0f, 0.25f});
    DetectCollider_->GetTransform().SetWorldScale({1500.f, 1000.f, 1.0f});

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->ChangeOrder(COLLISIONORDER::BossMonsterBody);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.97f, 0.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldScale({50.f, 50.f, 1.0f});
    BodyCollider_->GetTransform().SetWorldMove({0, -100});
    BodyCollider_->Off();

    AttackCollider_ = CreateComponent<GameEngineCollision>();
    AttackCollider_->ChangeOrder(COLLISIONORDER::BossMonsterAttack1);
    AttackCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f, 0.0f, 0.0f, 0.5f});
    AttackCollider_->GetTransform().SetWorldScale({50.f, 200.f, 1.0f});
    AttackCollider_->GetTransform().SetWorldMove({0, -250});
    AttackCollider_->Off();

    State_.CreateStateMember(
        "TeleportIN",
        std::bind(&GiantSword::TeleportINUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&GiantSword::TeleportINStart, this, std::placeholders::_1),
        std::bind(&GiantSword::TeleportINEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "TeleportOut",
        std::bind(&GiantSword::TeleportOutUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&GiantSword::TeleportOutStart, this, std::placeholders::_1),
        std::bind(&GiantSword::TeleportOutEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Visible",
                             std::bind(&GiantSword::VisibleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&GiantSword::VisibleStart, this, std::placeholders::_1),
                             std::bind(&GiantSword::VisibleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Track",
                             std::bind(&GiantSword::TrackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&GiantSword::TrackStart, this, std::placeholders::_1),
                             std::bind(&GiantSword::TrackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Attack",
                             std::bind(&GiantSword::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&GiantSword::AttackStart, this, std::placeholders::_1),
                             std::bind(&GiantSword::AttackEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Dodge",
                             std::bind(&GiantSword::DodgeUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&GiantSword::DodgeStart, this, std::placeholders::_1),
                             std::bind(&GiantSword::DodgeEnd, this, std::placeholders::_1));

    State_.ChangeState("Visible");

    SetSpeed(300.f);
}

void GiantSword::Update(float _DeltaTime)
{
    State_.Update(_DeltaTime);

    // GameEngineDebug::OutPutString("GiantSword : " + State_.GetCurStateStateName());
}

void GiantSword::End() {}


//화면에서 퇴장
void GiantSword::TeleportINStart(const StateInfo& _Info)
{
    EyeRenderer_->Off();
    IrisRenderer_->Off();

    Renderer_->ChangeFrameAnimation("pontiff_giantSword_teleportIN");

    SoundPlayer_ = GameEngineSound::SoundPlayControl("SWORD_DISAPPEAR.wav");
    SoundPlayer_.Volume(0.5f);

    Pontiff_->ChangeMonsterState("Opening");
    BodyCollider_->Off();

    Penitent::GetMainPlayer()->PlusTear(10);
}

void GiantSword::TeleportINUpdate(float _DeltaTime, const StateInfo& _Info) {}

void GiantSword::TeleportINEnd(const StateInfo& _Info) {}


//화면에 등장
void GiantSword::TeleportOutStart(const StateInfo& _Info)
{
    GetTransform().SetWorldRotation({0, 0, 0});

    Renderer_->ChangeFrameAnimation("pontiff_giantSword_teleportOUT");

    SoundPlayer_ = GameEngineSound::SoundPlayControl("SWORD_APPEAR.wav");
    SoundPlayer_.Volume(0.5f);

    if ("CloseIdle" != Pontiff_->GetState() && "Appear" != Pontiff_->GetState())
    {
        Pontiff_->ChangeMonsterState("Closing");
    }

    BodyCollider_->On();
}

void GiantSword::TeleportOutUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV4");
    }

    if (true == BloodEffect_->IsUpdate())
    {
        BloodEffect_->GetTransform().SetWorldPosition({BodyCollider_->GetTransform().GetWorldPosition().x,
                                                       BodyCollider_->GetTransform().GetWorldPosition().y,
                                                       PlayerEffectZ});

        BloodEffect_->GetTransform().SetWorldRotation({BodyCollider_->GetTransform().GetWorldRotation().x,
                                                       BodyCollider_->GetTransform().GetWorldRotation().y,
                                                       PlayerEffectZ});
    }

    MonsterBase::DamageCheck(40.f, "TeleportIN");
}

void GiantSword::TeleportOutEnd(const StateInfo& _Info) {}


void GiantSword::VisibleStart(const StateInfo& _Info)
{
    SetHP(100);
    Renderer_->Off();
}

void GiantSword::VisibleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if ("Death" == Pontiff_->GetState())
    {
        return;
    }

    if (5 < _Info.StateTime)
    {
        State_.ChangeState("TeleportOut");
    }
}

void GiantSword::VisibleEnd(const StateInfo& _Info) { Renderer_->On(); }


void GiantSword::AttackStart(const StateInfo& _Info)
{
    AttSpeed_ = 300.f;
    Dir_.Normalize();

    AttackCollider_->On();

    SoundPlayer_ = GameEngineSound::SoundPlayControl("SWORD_AIR_ATTACK.wav");
    SoundPlayer_.Volume(0.5f);
}

void GiantSword::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (false == IsTrunAttack_)
    {
        if (0.75f <= _Info.StateTime)
        {
            IsTrunAttack_ = true;
            AttackAfterimage_->SetIsDraw(true);
        }

        RotSpeed_ += _DeltaTime * 250.f;

        if (0 > -Dir_.x)
        {
            GetTransform().SetLocalRotate({0, 0, RotSpeed_ * _DeltaTime});
        }

        else if (0 <= -Dir_.x)
        {
            GetTransform().SetLocalRotate({0, 0, -RotSpeed_ * _DeltaTime});
        }
    }

    else
    {
        RotSpeed_ += _DeltaTime * 500.f;
        AttSpeed_ += 1000 * _DeltaTime;
        
        if (500.f <= AttSpeed_)
        {
            AttSpeed_ = 500.f;
        }

        float4 MoveForce;

        if (0 > -Dir_.x)
        {
            MoveForce = float4::LEFT * AttSpeed_ * _DeltaTime;
        }

        else
        {
            MoveForce = float4::RIGHT * AttSpeed_ * _DeltaTime;
        }

        GetTransform().SetWorldMove({MoveForce.x, 0});

        if (0 > -Dir_.x)
        {
            GetTransform().SetLocalRotate({0, 0, -RotSpeed_ * _DeltaTime});

            if (-180.f >= GetTransform().GetLocalRotation().z)
            {
                if (0.f < RotSpeed_)
                {
                    RotSpeed_ -= _DeltaTime * 10.f;
                }
            }

            if (-360.f >= GetTransform().GetLocalRotation().z)
            {
                State_.ChangeState("Track");
            }
        }

        else if (0 <= -Dir_.x)
        {
            GetTransform().SetLocalRotate({0, 0, RotSpeed_ * _DeltaTime});

            if (180.f <= GetTransform().GetLocalRotation().z)
            {
                if (0.f < RotSpeed_)
                {
                    RotSpeed_ -= _DeltaTime * 10.f;
                }
            }

            if (360.f <= GetTransform().GetLocalRotation().z)
            {
                State_.ChangeState("Track");
            }
        }

        /* if (true == Penitent::GetMainPlayer()->GetParryOn())
         {
             Penitent::GetMainPlayer()->ParrySlide();
         }*/
    }
}

void GiantSword::AttackEnd(const StateInfo& _Info)
{
    AttackCollider_->Off();
    RotSpeed_ = 0.f;

    IsTrunAttack_ = false;
}


void GiantSword::TrackStart(const StateInfo& _Info) {}

void GiantSword::TrackUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        State_.ChangeState("Dodge");

        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetTransform().SetWorldPosition({BodyCollider_->GetTransform().GetWorldPosition().x,
                                                       BodyCollider_->GetTransform().GetWorldPosition().y,
                                                       PlayerEffectZ});
    }

    if (true == BloodEffect_->IsUpdate())
    {
        BloodEffect_->GetTransform().SetWorldPosition({BodyCollider_->GetTransform().GetWorldPosition().x,
                                                       BodyCollider_->GetTransform().GetWorldPosition().y,
                                                       PlayerEffectZ});

        BloodEffect_->GetTransform().SetWorldRotation({BodyCollider_->GetTransform().GetWorldRotation().x,
                                                       BodyCollider_->GetTransform().GetWorldRotation().y,
                                                       PlayerEffectZ});
    }

    BossMonster::DamageCheck(40.f, "TeleportIN");

    TrackToPlayer(_Info.StateTime);

    DetectCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Player,
        CollisionType::CT_OBB2D,
        std::bind(&GiantSword::LookAtPlayer, this, std::placeholders::_1, std::placeholders::_2, _DeltaTime));
}

void GiantSword::TrackEnd(const StateInfo& _Info) {}


void GiantSword::DodgeStart(const StateInfo& _Info) { DodgeSpeed_ = 500.f; }

void GiantSword::DodgeUpdate(float _DeltaTime, const StateInfo& _Info)
{
    DodgeSpeed_ -= _DeltaTime * 700.f;

    Dir_.Normalize();
    GetTransform().SetWorldMove(float4{Dir_.x, Dir_.y} * DodgeSpeed_ * _DeltaTime);

    if (0.f >= DodgeSpeed_)
    {
        State_.ChangeState("Track");
    }

    if (true == BloodEffect_->IsUpdate())
    {
        BloodEffect_->GetTransform().SetWorldPosition({BodyCollider_->GetTransform().GetWorldPosition().x,
                                                       BodyCollider_->GetTransform().GetWorldPosition().y,
                                                       PlayerEffectZ});

        BloodEffect_->GetTransform().SetWorldRotation({BodyCollider_->GetTransform().GetWorldRotation().x,
                                                       BodyCollider_->GetTransform().GetWorldRotation().y,
                                                       PlayerEffectZ});
    }

    BossMonster::DamageCheck(40.f, "TeleportIN");

    DetectCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Player,
        CollisionType::CT_OBB2D,
        std::bind(&GiantSword::LookAtPlayer, this, std::placeholders::_1, std::placeholders::_2, _DeltaTime));
}

void GiantSword::DodgeEnd(const StateInfo& _Info) {}


bool GiantSword::LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other, float _DeltaTime)
{
    float4 Center = EyeRenderer_->GetTransform().GetWorldPosition();

    float4 EyeDir = Penitent::GetMainPlayer()->GetTransform().GetWorldPosition()
                  - EyeRenderer_->GetTransform().GetWorldPosition();

    EyeDir.Normalize();

    float4 IrisPos = IrisRenderer_->GetTransform().GetWorldPosition();

    float4 EndPos = Center + (EyeDir * 7.5f);

    Alpha_ += _DeltaTime;
    float4 Lerp = float4::LerpLimit(IrisPos, EndPos, Alpha_);

    float Length = (Lerp - Center).Length();

    float4 IrisEndPos;

    IrisEndPos = float4{Lerp.x, Lerp.y, IrisPos.z};

    IrisRenderer_->GetTransform().SetWorldPosition(IrisEndPos);

    return true;
}

bool GiantSword::TrackToPlayer(float _StateTime)
{
    Dir_ = GetTransform().GetWorldPosition() - Penitent::GetMainPlayer()->GetTransform().GetWorldPosition();

    float DistanceX = abs(Dir_.x);
    float DistanceY = abs(Dir_.y);

    float4 NormalDir = Dir_.NormalizeReturn();

    NormalDir.x <= 1.0f ? GetTransform().PixLocalPositiveX() : GetTransform().PixLocalNegativeX();

    float Angle = Dir_.x / 10.f;

    GetTransform().SetWorldRotation({0, 0, Angle});

    if (DistanceX <= 200)
    {
        SetSpeed(200.f);
        GetTransform().SetWorldMove({NormalDir.x * Speed_ * GameEngineTime::GetDeltaTime(), 0});
    }

    if (DistanceY <= 200)
    {
        SetSpeed(200.f);
        GetTransform().SetWorldMove({0, NormalDir.y * Speed_ * GameEngineTime::GetDeltaTime()});
    }

    if (DistanceX > 300)
    {
        SetSpeed(350.f);
        GetTransform().SetWorldMove({-NormalDir.x * Speed_ * GameEngineTime::GetDeltaTime(), 0});
    }

    //최대 사정거리보다 짧고 최소 사정거리보다 길어야 함
    else if (DistanceX > 200 && DistanceX <= 300 && 5.f <= _StateTime)
    {
        State_.ChangeState("Attack");
    }

    if (DistanceY > 300)
    {
        SetSpeed(350.f);
        GetTransform().SetWorldMove({0, -NormalDir.y * Speed_ * GameEngineTime::GetDeltaTime()});
    }

    else if (DistanceY > 200 && DistanceY <= 300 && 5.f <= _StateTime)
    {
        State_.ChangeState("Attack");
    }

    return false;
}
