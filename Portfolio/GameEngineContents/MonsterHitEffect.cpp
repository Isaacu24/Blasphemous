#include "PreCompile.h"
#include "MonsterHitEffect.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"

MonsterHitEffect::MonsterHitEffect() {}

MonsterHitEffect::~MonsterHitEffect() {}


void MonsterHitEffect::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    Effect_ = CreateComponent<MetaTextureRenderer>();
    Effect_->Off();

    RangeEffect_ = CreateComponent<MetaTextureRenderer>();
    RangeEffect_->Off();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_attack_spark_1_anim");

        Effect_->CreateMetaAnimation(
            "penitent_attack_spark_1_anim",
            {"penitent_attack_spark_1_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        Effect_->AnimationBindEnd("penitent_attack_spark_1_anim",
                                  [&](const FrameAnimation_DESC& _Info) { Effect_->Off(); });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_attack_spark_1_revision_anim");

        Effect_->CreateMetaAnimation(
            "penitent_attack_spark_1_revision_anim",
            {"penitent_attack_spark_1_revision_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        Effect_->AnimationBindEnd("penitent_attack_spark_1_revision_anim",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      //첫 연속 공격 이후 다시 첫 공격을 시작할 때 애니메이션이 바뀌기 위한 코드
                                      Effect_->CurAnimationReset();
                                      Effect_->Off();
                                  });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_attack_spark_2_revision_anim");

        Effect_->CreateMetaAnimation(
            "penitent_attack_spark_2_revision_anim",
            {"penitent_attack_spark_2_revision_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        Effect_->AnimationBindEnd("penitent_attack_spark_2_revision_anim",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      Effect_->CurAnimationReset();
                                      Effect_->Off();
                                  });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_attack_spark_3_revision_anim");

        Effect_->CreateMetaAnimation(
            "penitent_attack_spark_3_revision_anim",
            {"penitent_attack_spark_3_revision_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        Effect_->AnimationBindEnd("penitent_attack_spark_3_revision_anim",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      Effect_->CurAnimationReset();
                                      Effect_->Off();
                                  });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ranged_attack_hit_effect");

        RangeEffect_->CreateMetaAnimation(
            "ranged_attack_hit_effect",
            {"ranged_attack_hit_effect.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        RangeEffect_->AnimationBindEnd("ranged_attack_hit_effect",
                                       [&](const FrameAnimation_DESC& _Info)
                                       {
                                           RangeEffect_->CurAnimationReset();
                                           RangeEffect_->Off();
                                       });
    }
}

void MonsterHitEffect::Update(float _DeltaTime)
{
    if (0 < HitCount_)
    {
        ResetTime_ += _DeltaTime;

        if (1.5f <= ResetTime_)
        {
            ResetTime_ = 0.f;
            HitCount_  = 0;
        }
    }
}

void MonsterHitEffect::End() {}


void MonsterHitEffect::ShowHitEffet()
{
    Effect_->On();

    switch (HitCount_)
    {
        case 0:
            Effect_->ChangeMetaAnimation("penitent_attack_spark_1_revision_anim");
            break;
        case 1:
            Effect_->ChangeMetaAnimation("penitent_attack_spark_2_revision_anim");
            break;
        case 2:
            Effect_->ChangeMetaAnimation("penitent_attack_spark_3_revision_anim");
            break;
        default:
            Effect_->ChangeMetaAnimation("penitent_attack_spark_1_anim");
            break;
    }

    ++HitCount_;

    if (2 < HitCount_)
    {
        HitCount_ = 2;
    }
}   

void MonsterHitEffect::ShowRangeHitEffect()
{
    RangeEffect_->On();
    RangeEffect_->ChangeMetaAnimation("ranged_attack_hit_effect");
}
