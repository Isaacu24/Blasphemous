#include "PreCompile.h"
#include "NormalMonster.h"
#include "BloodSplatters.h"
#include "MetaTextureRenderer.h"

NormalMonster::NormalMonster()
    : TrackMinLimit_(0.f)
    , IsPlayerLeft_(false)
    , IsPlayerRight_(false)
{}

NormalMonster::~NormalMonster() {}

void NormalMonster::Start()
{
    HitEffect_ = GetLevel()->CreateActor<MonsterHitEffect>();

    BloodEffect_ = GetLevel()->CreateActor<BloodSplatters>();
    BloodEffect_->GetRenderer()->Off();

    ExecutionCollider_ = CreateComponent<GameEngineCollision>();
    ExecutionCollider_->GetTransform().SetWorldScale({10.f, 50.f, 1.f});
    ExecutionCollider_->ChangeOrder(COLLISIONORDER::MonsterExecution);
    ExecutionCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 0.0f, 0.5f});
    ExecutionCollider_->GetTransform().SetWorldMove({-15.f, 25.f});
    ExecutionCollider_->Off();

    UIRenderer_ = CreateComponent<GameEngineTextureRenderer>();

    if (0 < GameEngineInput::GetInst()->GetInputState().dwPacketNumber)
    {
        UIRenderer_->SetTexture("CT_Y.png");
    }

    else
    {
        UIRenderer_->SetTexture("KB_E.png");
    }

    UIRenderer_->GetTransform().SetWorldScale({15, 15, 1});
    UIRenderer_->GetTransform().SetWorldMove({0.f, 100.f});
    UIRenderer_->Off();
}

void NormalMonster::Update(float _DeltaTime) {}

void NormalMonster::End() {}


bool NormalMonster::LeftObstacleCheck(float _X, float _Y)
{
    float4 LeftColor = ColMap_->GetCurTexture()->GetPixelToFloat4(_X, _Y);

    if (true == LeftColor.CompareInt4D(float4::BLACK))
    {
        return true;
    }

    if (true == LeftColor.CompareInt4D(float4::MAGENTA))
    {
        return true;
    }

    return false;
}

bool NormalMonster::RightObstacleCheck(float _X, float _Y)
{
    float4 RightColor = ColMap_->GetCurTexture()->GetPixelToFloat4(_X, _Y);

    if (true == RightColor.CompareInt4D(float4::BLACK))
    {
        return true;
    }

    if (true == RightColor.CompareInt4D(float4::MAGENTA))
    {
        return true;
    }

    return false;
}

bool NormalMonster::LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
    {
        GetTransform().PixLocalPositiveX();
    }

    else
    {
        GetTransform().PixLocalNegativeX();
    }

    return true;
}


bool NormalMonster::TrackPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    float Distance = abs(_This->GetTransform().GetWorldPosition().x - _Other->GetTransform().GetWorldPosition().x);

    //추격 최소 사정거리보다 작음 -> 추적하지 않음
    if (TrackMinLimit_ > Distance)
    {
        IsPlayerLeft_  = false;
        IsPlayerRight_ = false;

        return false;
    }

    DetectPlayer(_This, _Other);

    return true;
}


bool NormalMonster::DetectPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
    {
        IsPlayerRight_ = true;
        IsPlayerLeft_  = false;
    }

    else
    {
        IsPlayerLeft_  = true;
        IsPlayerRight_ = false;
    }

    return true;
}


bool NormalMonster::CrossroadCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    float Distance = _This->GetTransform().GetWorldPosition().x - _Other->GetTransform().GetWorldPosition().x;

    Distance = abs(Distance);

    if (Crossroad_ >= Distance)
    {
        return true;
    }

    return false;
}


bool NormalMonster::ExecutionCheck()
{
    bool IsCollide = ExecutionCollider_->IsCollision(
        CollisionType::CT_OBB2D,
        COLLISIONORDER::Player,
        CollisionType::CT_OBB2D,
        std::bind(&NormalMonster::DetectPlayer, this, std::placeholders::_1, std::placeholders::_2));

    if (true == IsCollide)
    {
        if (0 < Dir_.x && IsPlayerRight_ || 0 > Dir_.x && IsPlayerLeft_)
        {
            UIRenderer_->On();
            UIRenderer_->GetTransform().PixWorldPositiveX();

            if (0 < GameEngineInput::GetInst()->GetInputState().dwPacketNumber)
            {
                UIRenderer_->SetTexture("CT_Y.png");
            }

            else
            {
                UIRenderer_->SetTexture("KB_E.png");
            }

            return true;
        }
    }

    else
    {
        UIRenderer_->Off();
    }

    return false;
}

bool NormalMonster::ReverseBloodEffect(GameEngineCollision* _This, GameEngineCollision* _Other) 
{
    if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
    {
        BloodEffect_->GetTransform().PixLocalPositiveX();
    }

    else
    {
        BloodEffect_->GetTransform().PixLocalNegativeX();
    }

    return true; 
}


void NormalMonster::DamageCheck(float _Damage, float _Offset)
{
    //스킬 임시 제외
    if (false
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;

        if (nullptr != Renderer_)
        {
            Renderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
        }

        if (nullptr != MetaRenderer_)
        {
            MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
        }
    }

    if (true == IsHit_)
    {
        return;
    }

    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::PlayerAttack,
            CollisionType::CT_OBB2D,
            std::bind(&NormalMonster::ReverseBloodEffect, this, std::placeholders::_1, std::placeholders::_2)))
    {
        MinusHP(_Damage);
        IsHit_ = true;

        float4 HitPos = BodyCollider_->GetTransform().GetWorldPosition();

        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

        HitEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
        HitEffect_->ShowHitEffet();

        if (nullptr != Renderer_)
        {
            Renderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
        }

        if (nullptr != MetaRenderer_)
        {
            MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
        }
    }

    else if (true
             == BodyCollider_->IsCollision(
                 CollisionType::CT_OBB2D, COLLISIONORDER::PlayerRangeAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = true;

        if (nullptr != Renderer_)
        {
            Renderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
        }

        if (nullptr != MetaRenderer_)
        {
            MetaRenderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
        }

        float4 HitPos = BodyCollider_->GetTransform().GetWorldPosition();

        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetTransform().SetWorldPosition({HitPos.x + (Dir_.x * 30.f), HitPos.y, BossMonsterEffectZ});
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

        HitEffect_->GetTransform().SetWorldPosition({HitPos.x + (Dir_.x * 30.f), HitPos.y, BossMonsterEffectZ});
        HitEffect_->ShowRangeHitEffect();

        MinusHP(7.f);
    }

    if (0 >= GetHP())
    {
        State_.ChangeState("Death");
    }
}
