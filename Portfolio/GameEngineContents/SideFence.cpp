#include "PreCompile.h"
#include "SideFence.h"

SideFence::SideFence() 
    : IsClose_(true)
{}

SideFence::~SideFence() {}

void SideFence::Start()
{
    Rendrerer_ = CreateComponent<GameEngineTextureRenderer>();

    std::vector<unsigned int> Order = {};

    for (int i = 19; i >= 0; i--)
    {
        Order.push_back(i);
    }

    Rendrerer_->CreateFrameAnimationCutTexture("reja_lateral_invertedBell_Close",
                                               {"reja_lateral_invertedBell_descending.png", 19, 19, 0.1f, false});

    Rendrerer_->CreateFrameAnimationCutTexture("reja_lateral_invertedBell_descending",
                                               {"reja_lateral_invertedBell_descending.png", Order, 0.1f, true});

    Rendrerer_->AnimationBindEnd("reja_lateral_invertedBell_descending",
                                 [&](const FrameAnimation_DESC& _Info)
                                 {
                                     State_.ChangeState("Open");
                                 });

    Rendrerer_->CreateFrameAnimationCutTexture("reja_lateral_invertedBell_Open",
                                               {"reja_lateral_invertedBell_descending.png", 0, 0, 0.1f, false});

    Rendrerer_->ChangeFrameAnimation("reja_lateral_invertedBell_Close");
    Rendrerer_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Object)});
    Rendrerer_->GetTransform().SetWorldScale({100, 250, 1});
    Rendrerer_->SetPivot(PIVOTMODE::LEFTTOP);

    State_.CreateStateMember("Open",
                             std::bind(&SideFence::OpenUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&SideFence::OpenStart, this, std::placeholders::_1),
                             std::bind(&SideFence::OpenEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Close",
                             std::bind(&SideFence::CloseUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&SideFence::CloseStart, this, std::placeholders::_1),
                             std::bind(&SideFence::CloseEnd, this, std::placeholders::_1));

    State_.CreateStateMember(
        "Descending",
        std::bind(&SideFence::DescendingUpdate, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&SideFence::DescendingStart, this, std::placeholders::_1),
        std::bind(&SideFence::DescendingEnd, this, std::placeholders::_1));

    State_.ChangeState("Close");
}

void SideFence::Update(float _DeltaTime) { State_.Update(_DeltaTime); }


void SideFence::End() {}


void SideFence::OpenStart(const StateInfo& _Info)
{
    IsClose_ = false;
    Rendrerer_->ChangeFrameAnimation("reja_lateral_invertedBell_Open");
}

void SideFence::OpenUpdate(float _DeltaTime, const StateInfo& _Info) {}

void SideFence::OpenEnd(const StateInfo& _Info) {}

void SideFence::CloseStart(const StateInfo& _Info)
{
    IsClose_ = true;
    Rendrerer_->ChangeFrameAnimation("reja_lateral_invertedBell_Close");
}

void SideFence::CloseUpdate(float _DeltaTime, const StateInfo& _Info) {}

void SideFence::CloseEnd(const StateInfo& _Info) {}


void SideFence::DescendingStart(const StateInfo& _Info)
{
    //PrevState_ = _Info.PrevState;
    Rendrerer_->ChangeFrameAnimation("reja_lateral_invertedBell_descending");
}
void SideFence::DescendingUpdate(float _DeltaTime, const StateInfo& _Info) {}

void SideFence::DescendingEnd(const StateInfo& _Info) {}



