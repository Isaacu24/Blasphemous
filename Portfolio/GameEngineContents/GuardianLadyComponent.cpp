#include "PreCompile.h"
#include "GuardianLadyComponent.h"
#include "MetaTextureRenderer.h"
#include "MetaSpriteManager.h"
#include "Projectile.h"

GuardianLadyComponent::GuardianLadyComponent() {}

GuardianLadyComponent::~GuardianLadyComponent() {}


void GuardianLadyComponent::Start()
{
    ProtectCollider_ = GetActor()->CreateComponent<GameEngineCollision>();
    ProtectCollider_->GetTransform().SetWorldScale({200.f, 200.f, 1.f});
    ProtectCollider_->ChangeOrder(COLLISIONORDER::Player);
    ProtectCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    ProtectCollider_->Off();

    MetaRenderer_ = GetActor()->CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("guardian_lady_protect_and_vanish");

        MetaRenderer_->CreateMetaAnimation(
            "guardian_lady_protect_and_vanish",
            {"guardian_lady_protect_and_vanish.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.06f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("guardian_lady_protect_and_vanish",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            MetaRenderer_->CurAnimationReset();
                                            MetaRenderer_->Off();

                                            ProtectCollider_->Off();
                                        });
    }

    MetaRenderer_->Off();
}

void GuardianLadyComponent::Update(float _DeltaTime)
{
    if (false == IsProtected_)
    {
        CoolTime_ += _DeltaTime;

        if (10.f <= CoolTime_)
        {
            CoolTime_    = 0.f;
            IsProtected_ = true;
        }
    }

    else
    {
        ProtectCollider_->On();

        ProtectCollider_->IsCollision(
            CollisionType::CT_OBB2D,
            COLLISIONORDER::Projectile,
            CollisionType::CT_OBB2D,
            [&](GameEngineCollision* _This, GameEngineCollision* _Other)
            {
                Projectile* NewProjectile = dynamic_cast<Projectile*>(_Other->GetActor());
                NewProjectile->GetState().ChangeState("Explosion");

                IsProtected_ = false;
                ProtectCollider_->Off();

                MetaRenderer_->On();
                MetaRenderer_->ChangeMetaAnimation("guardian_lady_protect_and_vanish");

                MetaRenderer_->GetTransform().SetWorldScale(GetActor()->GetTransform().GetWorldScale());

                if (0 < GetActor()->GetTransform().GetWorldScale().x)
                {
                    MetaRenderer_->GetTransform().SetWorldPosition(GetActor()->GetTransform().GetWorldPosition()
                                                                   + float4{100, 500});
                }

                else
                {
                    MetaRenderer_->GetTransform().SetWorldPosition(GetActor()->GetTransform().GetWorldPosition()
                                                                   + float4{100, 500});
                }

                return false;
            });
    }
}

void GuardianLadyComponent::End() {}
