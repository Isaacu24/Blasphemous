#include "PreCompile.h"
#include "SideFence.h"

SideFence::SideFence() {}

SideFence::~SideFence() {}

void SideFence::Start()
{
    Rendrerer_                      = CreateComponent<GameEngineTextureRenderer>();
    std::vector<unsigned int> Order = {};

    for (int i = 19; i >= 0; i--)
    {
        Order.push_back(i);
    }

    Rendrerer_->CreateFrameAnimationCutTexture("reja_lateral_invertedBell_Close",
                                               {"reja_lateral_invertedBell_descending.png", 19, 19, 0.1f, false});

    Rendrerer_->CreateFrameAnimationCutTexture("reja_lateral_invertedBell_descending",
                                               {"reja_lateral_invertedBell_descending.png", Order, 0.1f, true});
    
    Rendrerer_->CreateFrameAnimationCutTexture("reja_lateral_invertedBell_Open",
                                               {"reja_lateral_invertedBell_descending.png", 0, 0, 0.1f, false});

    Rendrerer_->ChangeFrameAnimation("reja_lateral_invertedBell_Close");
    Rendrerer_->GetTransform().SetWorldPosition({0, 0, static_cast<int>(ACTORORDER::Object)});
    Rendrerer_->GetTransform().SetWorldScale({100, 250, 1});
    Rendrerer_->SetPivot(PIVOTMODE::LEFTTOP);
}

void SideFence::Update(float _DeltaTime) 
{

}

void SideFence::End() 
{

}
