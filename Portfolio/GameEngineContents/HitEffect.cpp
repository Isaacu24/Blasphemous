#include "PreCompile.h"
#include "HitEffect.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"

HitEffect::HitEffect() {}

HitEffect::~HitEffect() {}

void HitEffect::Start()
{
    Renderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_attack_spark_1_anim");

        Renderer_->CreateMetaAnimation(
            "penitent_attack_spark_1_anim",
            {"penitent_attack_spark_1_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        Renderer_->AnimationBindEnd("penitent_attack_spark_1_anim",
                                    [&](const FrameAnimation_DESC& _Info) 
            { 
                //ù ���� ���� ���� �ٽ� ù ������ ������ �� �ִϸ��̼��� �ٲ�� ���� �ڵ�
                Renderer_->ChangeMetaAnimation("penitent_attack_spark_1_anim");
                Renderer_->Off(); 
            });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_attack_spark_1_revision_anim");

        Renderer_->CreateMetaAnimation(
            "penitent_attack_spark_1_revision_anim",
            {"penitent_attack_spark_1_revision_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        Renderer_->AnimationBindEnd("penitent_attack_spark_1_revision_anim",
                                    [&](const FrameAnimation_DESC& _Info) 
            { 
                Renderer_->ChangeMetaAnimation("penitent_attack_spark_1_anim");
                Renderer_->Off(); 
            });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_attack_spark_2_revision_anim");

        Renderer_->CreateMetaAnimation(
            "penitent_attack_spark_2_revision_anim",
            {"penitent_attack_spark_2_revision_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        Renderer_->AnimationBindEnd("penitent_attack_spark_2_revision_anim",
                                    [&](const FrameAnimation_DESC& _Info) 
            { 
                Renderer_->ChangeMetaAnimation("penitent_attack_spark_1_anim");
                Renderer_->Off(); 
            });
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("penitent_attack_spark_3_revision_anim");

        Renderer_->CreateMetaAnimation(
            "penitent_attack_spark_3_revision_anim",
            {"penitent_attack_spark_3_revision_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.07f, false},
            Data);

        Renderer_->AnimationBindEnd("penitent_attack_spark_3_revision_anim",
                                    [&](const FrameAnimation_DESC& _Info) 
            { 
                Renderer_->ChangeMetaAnimation("penitent_attack_spark_1_anim");
                Renderer_->Off(); 
            });
    }

    Renderer_->SetPivot(PIVOTMODE::METABOT);
}

void HitEffect::Update(float _DeltaTime) {}

void HitEffect::End() {}
