#include "PreCompile.h"
#include "CherubCaptor.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"
#include "CherubPopUp.h"

CherubCaptor::CherubCaptor() {}

CherubCaptor::~CherubCaptor() {}


int CherubCaptor::Count_ = 0;

void CherubCaptor::Start()
{
    GetTransform().SetWorldScale({2.f, 2.f, 1.f});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->GetTransform().SetWorldScale({50.f, 200.f, 1.f});
    Collider_->ChangeOrder(COLLISIONORDER::MonsterBody);
    Collider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.3f, 0.0f, 1.0f, 0.5f});
    Collider_->GetTransform().SetWorldMove({0.f, -50.f, 1.f});

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("cherubCaptor_idle");

        MetaRenderer_->CreateMetaAnimation(
            "cherubCaptor_idle",
            {"cherubCaptor_idle.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.06f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("cherubCaptor_death");

        MetaRenderer_->CreateMetaAnimation(
            "cherubCaptor_death",
            {"cherubCaptor_death.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.06f, true},
            Data);

        MetaRenderer_->AnimationBindEnd("cherubCaptor_death",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            CherubPopUp* UI = GetLevel()->CreateActor<CherubPopUp>();
                                            UI->SetCountFont(Count_);
                                            Death();
                                        });
    }

    MetaRenderer_->ChangeMetaAnimation("cherubCaptor_idle");

    State_.CreateStateMember("Idle",
                             std::bind(&CherubCaptor::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&CherubCaptor::IdleStart, this, std::placeholders::_1),
                             std::bind(&CherubCaptor::IdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&CherubCaptor::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&CherubCaptor::DeathStart, this, std::placeholders::_1),
                             std::bind(&CherubCaptor::DeathEnd, this, std::placeholders::_1));

    State_.ChangeState("Idle");
}


void CherubCaptor::Update(float _DeltaTime) { State_.Update(_DeltaTime); }

void CherubCaptor::End() {}



void CherubCaptor::PatrolXMove(float _DeltaTime)
{
    if (true == PatrolStart_)
    {
        if (GetTransform().GetWorldPosition().x < EndPos_.x - 10.f)
        {
            Alpha_ += _DeltaTime / 15.f;

            float XPos = GameEngineMath::LerpLimit(GetTransform().GetWorldPosition().x, EndPos_.x, Alpha_ / 50.f);
            GetTransform().SetWorldPosition(
                {XPos, GetTransform().GetWorldPosition().y, GetTransform().GetWorldPosition().z});
        }

        else
        {
            Alpha_ = 0.f;

            PatrolStart_ = false;
            PatrolEnd_   = true;

            GetTransform().PixLocalNegativeX();
        }
    }

    else if (true == PatrolEnd_)
    {
        if (GetTransform().GetWorldPosition().x > StartPos_.x + 10.f)  // 근사치 인정
        {
            Alpha_ += _DeltaTime / 15.f;

            float XPos = GameEngineMath::LerpLimit(GetTransform().GetWorldPosition().x, StartPos_.x, Alpha_ / 50.f);
            GetTransform().SetWorldPosition(
                {XPos, GetTransform().GetWorldPosition().y, GetTransform().GetWorldPosition().z});
        }

        else
        {
            Alpha_ = 0.f;

            PatrolStart_ = true;
            PatrolEnd_   = false;

            GetTransform().PixLocalPositiveX();
        }
    }
}


void CherubCaptor::IdleStart(const StateInfo& _Info) {}

void CherubCaptor::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    if (true
        == Collider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        State_.ChangeState("Death");
    }

    if (true == IsPatrolX_)
    {
        PatrolXMove(_DeltaTime);
    }
}

void CherubCaptor::IdleEnd(const StateInfo& _Info) {}


void CherubCaptor::DeathStart(const StateInfo& _Info) 
{
    Count_++;
    MetaRenderer_->ChangeMetaAnimation("cherubCaptor_death"); 
}

void CherubCaptor::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void CherubCaptor::DeathEnd(const StateInfo& _Info) {}
