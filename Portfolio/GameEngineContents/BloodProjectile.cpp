#include "PreCompile.h"
#include "BloodProjectile.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"
#include "NormalMonster.h"
#include "ShieldMaiden.h"
#include "BossMonster.h"

BloodProjectile::BloodProjectile() {}

BloodProjectile::~BloodProjectile() {}

void BloodProjectile::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->GetTransform().SetWorldScale({100.f, 50.f, 1.f});
    Collider_->ChangeOrder(COLLISIONORDER::PlayerRangeAttack);
    Collider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_rangeAttack_projectile_anim");

        MetaRenderer_->CreateMetaAnimation(
            "penitent_rangeAttack_projectile_anim",
            {"penitent_rangeAttack_projectile_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.08f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_rangeAttack_projectile_explode_anim");

        MetaRenderer_->CreateMetaAnimation("penitent_rangeAttack_projectile_explode_anim",
                                           {"penitent_rangeAttack_projectile_explode_anim.png",
                                            0,
                                            static_cast<unsigned int>(Data.size() - 1),
                                            0.08f,
                                            true},
                                           Data);

        MetaRenderer_->AnimationBindEnd("penitent_rangeAttack_projectile_explode_anim",
                                        [&](const FrameAnimation_DESC& _Info) { Death(); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_rangeAttack_projectile_vanish_anim");

        MetaRenderer_->CreateMetaAnimation("penitent_rangeAttack_projectile_vanish_anim",
                                           {"penitent_rangeAttack_projectile_vanish_anim.png",
                                            0,
                                            static_cast<unsigned int>(Data.size() - 1),
                                            0.08f,
                                            true},
                                           Data);


        MetaRenderer_->AnimationBindEnd("penitent_rangeAttack_projectile_vanish_anim",
                                        [&](const FrameAnimation_DESC& _Info) { Death(); });
    }

    State_.CreateStateMember(
        "Shoot",
        std::bind(&BloodProjectile::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&BloodProjectile::ShootStart, this, std::placeholders::_1),
        std::bind(&BloodProjectile::ShootEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "Explode",
        std::bind(&BloodProjectile::ExplodeUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&BloodProjectile::ExplodeStart, this, std::placeholders::_1),
        std::bind(&BloodProjectile::ExplodeEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "Vanish",
        std::bind(&BloodProjectile::VanishUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&BloodProjectile::VanishStart, this, std::placeholders::_1),
        std::bind(&BloodProjectile::VanishEnd, this, std::placeholders::_1));

    State_.ChangeState("Shoot");
}

void BloodProjectile::Update(float _DeltaTime) { State_.Update(_DeltaTime); }

void BloodProjectile::End() {}


void BloodProjectile::ShootStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("penitent_rangeAttack_projectile_anim");
    SoundPlayer_ = GameEngineSound::SoundPlayControl("RANGE_ATTACK_FLY.wav");
}

void BloodProjectile::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
    float4 Distance = StartPos_ - GetTransform().GetWorldPosition();

    if (500.f < abs(Distance.x))
    {
        State_.ChangeState("Vanish");
        return;
    }

    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                              -(GetTransform().GetWorldPosition().y));

    if (Color.CompareInt4D(float4::BLACK) || Color.CompareInt4D(float4::MAGENTA))
    {
        State_.ChangeState("Explode");
        return;
    }

    float4 MovePos = Dir_.x * 500 * _DeltaTime;
    GetTransform().SetWorldMove({MovePos.x, 0.f});

    MonsterCheck();
}

void BloodProjectile::ShootEnd(const StateInfo& _Info) {}


void BloodProjectile::ExplodeStart(const StateInfo& _Info)
{
    Collider_->Death();

    SoundPlayer_ = GameEngineSound::SoundPlayControl("RANGE_ATTACK_EXPLODE.wav");
    MetaRenderer_->ChangeMetaAnimation("penitent_rangeAttack_projectile_explode_anim");
}

void BloodProjectile::ExplodeUpdate(float _DeltaTime, const StateInfo& _Info) {}

void BloodProjectile::ExplodeEnd(const StateInfo& _Info) {}


void BloodProjectile::VanishStart(const StateInfo& _Info)
{
    Collider_->Death();

    SoundPlayer_ = GameEngineSound::SoundPlayControl("RANGE_ATTACK_DISSAPEAR.wav");
    MetaRenderer_->ChangeMetaAnimation("penitent_rangeAttack_projectile_vanish_anim");
}

void BloodProjectile::VanishUpdate(float _DeltaTime, const StateInfo& _Info) {}

void BloodProjectile::VanishEnd(const StateInfo& _Info) {}


void BloodProjectile::MonsterCheck()
{
    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::Monster,
                           CollisionType::CT_OBB2D,
                           [&](GameEngineCollision* _This, GameEngineCollision* _Other)
                           {
                               NormalMonster* Monster = dynamic_cast<NormalMonster*>(_Other->GetActor());

                               if (nullptr != Monster)
                               {
                                   ShieldMaiden* Maiden = dynamic_cast<ShieldMaiden*>(_Other->GetActor());

                                   if (nullptr != Maiden && Maiden->)
                                   {

                                   }

                                   Monster->MinusHP(30.f);
                                   Monster->PlayerRangeAttackHit();
                               }

                               State_.ChangeState("Explode");
                               return false;
                           });


    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::MonsterBody,
                           CollisionType::CT_OBB2D,
                           [&](GameEngineCollision* _This, GameEngineCollision* _Other)
                           {
                               NormalMonster* Monster = dynamic_cast<NormalMonster*>(_Other->GetActor());

                               if (nullptr != Monster)
                               {
                                   Monster->MinusHP(30.f);
                                   Monster->PlayerRangeAttackHit();
                               }

                               State_.ChangeState("Explode");
                               return false;
                           });


    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::BossMonster,
                           CollisionType::CT_OBB2D,
                           [&](GameEngineCollision* _This, GameEngineCollision* _Other)
                           {
                               BossMonster* Monster = dynamic_cast<BossMonster*>(_Other->GetActor());

                               if (nullptr != Monster)
                               {
                                   Monster->MinusHP(30.f);
                                   Monster->PlayerRangeAttackHit();
                               }

                               State_.ChangeState("Explode");
                               return false;
                           });


    Collider_->IsCollision(CollisionType::CT_OBB2D,
                           COLLISIONORDER::BossMonsterBody,
                           CollisionType::CT_OBB2D,
                           [&](GameEngineCollision* _This, GameEngineCollision* _Other)
                           {
                               BossMonster* Monster = dynamic_cast<BossMonster*>(_Other->GetActor());

                               if (nullptr != Monster)
                               {
                                   Monster->MinusHP(30.f);
                               }

                               State_.ChangeState("Explode");
                               return false;
                           });
}
