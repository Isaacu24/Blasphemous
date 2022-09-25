#include "BossMonster.h"
#include "MetaTextureRenderer.h"

BossMonster::BossMonster()
    : BossEvent_(false)
{}

BossMonster::~BossMonster() {}

void BossMonster::Start()
{
    HitEffect_ = GetLevel()->CreateActor<MonsterHitEffect>();

    BloodEffect_ = GetLevel()->CreateActor<BloodSplatters>();
    BloodEffect_->GetRenderer()->Off();
}

void BossMonster::Update(float _DeltaTime)
{
    if (true == BossDeathEvent_)
    {
        float4 CamPos = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
        Backgorund_->GetTransform().SetWorldPosition({CamPos.x, CamPos.y, -99});

        float4 MyPos = GetTransform().GetWorldPosition();
        GetTransform().SetWorldPosition({MyPos.x, MyPos.y, -150});

        EventTime_ += _DeltaTime;

        if (0.75f <= EventTime_ && false == DeathSlow_)
        {
            GameEngineTime::GetInst()->SetTimeScale(Renderer_->GetOrder(), 1);
            DeathSlow_ = true;
        }

        if (2.f <= EventTime_)
        {
            EventTime_ = 0.f;
            Backgorund_->Death();
            Backgorund_ = nullptr;

            GetTransform().SetWorldPosition({MyPos.x, MyPos.y, BossMonsterZ});
            Penitent::GetMainPlayer()->BossKillEventOff();

            if (nullptr != MetaRenderer_)
            {
                MetaRenderer_->GetColorData().MulColor  = float4::ONE;
                MetaRenderer_->GetColorData().PlusColor = float4::ZERO;
            }

            else if (nullptr != Renderer_)
            {
                Renderer_->GetColorData().MulColor  = float4::ONE;
                Renderer_->GetColorData().PlusColor = float4::ZERO;
            }

            BossDeathEvent_ = false;
        }
    }
}

void BossMonster::End() {}

void BossMonster::DamageCheck(float _Damage)
{
    if (false
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;
    }

    if (true == IsHit_)
    {
        return;
    }

    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = true;

        float4 HitPos = BodyCollider_->GetTransform().GetWorldPosition();

        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

        HitEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
        HitEffect_->ShowHitEffet();

        MinusHP(_Damage);
    }

    if (0 >= GetHP())
    {
        State_.ChangeState("Death");
    }
}


void BossMonster::DamageCheck(float _Damage, const std::string& _State)
{
    if (false
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;
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
            std::bind(&BossMonster::ReverseBloodEffect, this, std::placeholders::_1, std::placeholders::_2)))
    {
        IsHit_ = true;

        float4 HitPos = BodyCollider_->GetTransform().GetWorldPosition();

        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

        HitEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, BossMonsterEffectZ});
        HitEffect_->ShowHitEffet();

        MinusHP(_Damage);
    }

    if (0 >= GetHP())
    {
        State_.ChangeState(_State);
    }
}

void BossMonster::BossDeathEvent()
{
    Backgorund_ = CreateComponent<GameEngineTextureRenderer>();
    Backgorund_->SetTexture("BlackBackground.png");
    Backgorund_->ScaleToTexture();

    float4 CamPos = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
    Backgorund_->GetTransform().SetWorldPosition({CamPos.x, CamPos.y, -99});

    float4 MyPos = GetTransform().GetWorldPosition();
    GetTransform().SetWorldPosition({MyPos.x, MyPos.y, -150});

    Penitent::GetMainPlayer()->BossKillEventOn();

    if (nullptr != MetaRenderer_)
    {
        MetaRenderer_->GetColorData().MulColor  = float4::ZERO;
        MetaRenderer_->GetColorData().PlusColor = float4{0.57f, 0.14f, 0.21f, 1.0f};
        GameEngineTime::GetInst()->SetTimeScale(MetaRenderer_->GetOrder(), 0.5f);
    }

    else if (nullptr != Renderer_)
    {
        Renderer_->GetColorData().MulColor  = float4::ZERO;
        Renderer_->GetColorData().PlusColor = float4{0.57f, 0.14f, 0.21f, 1.0f};
        GameEngineTime::GetInst()->SetTimeScale(Renderer_->GetOrder(), 0.5f);
    }

    BossDeathEvent_ = true;
}


bool BossMonster::ReverseBloodEffect(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    if (_This->GetTransform().GetWorldPosition().x < _Other->GetTransform().GetWorldPosition().x)
    {
        BloodEffect_->GetTransform().PixLocalNegativeX();
    }

    else
    {
        BloodEffect_->GetTransform().PixLocalPositiveX();
    }

    return true;
}
