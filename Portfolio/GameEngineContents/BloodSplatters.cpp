#include "PreCompile.h"
#include "BloodSplatters.h"

BloodSplatters::BloodSplatters() 
{
}

BloodSplatters::~BloodSplatters() 
{
}

// GameEngineTexture::Cut("BloodSplatters.png", 5, 5);
//GameEngineTexture::Cut("BloodSplattersV3.png", 4, 4);
//GameEngineTexture::Cut("BloodSplattersV4.png", 4, 4);



void BloodSplatters::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationCutTexture("BloodSplatters", { "BloodSplatters.png", 0, 23, 0.1f, true});
	Renderer_->CreateFrameAnimationCutTexture("BloodSplattersV3", { "BloodSplattersV3.png", 0, 15, 0.1f, true });
	Renderer_->CreateFrameAnimationCutTexture("BloodSplattersV4", { "BloodSplattersV4.png", 0, 15, 0.1f, true });
	Renderer_->ChangeFrameAnimation("BloodSplattersV3");
	Renderer_->GetTransform().SetWorldScale({100, 100});

	State_.CreateStateMember("Frist", std::bind(&BloodSplatters::FristUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&BloodSplatters::FristStart, this, std::placeholders::_1));
	State_.CreateStateMember("Second", std::bind(&BloodSplatters::SecondUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&BloodSplatters::SecondStart, this, std::placeholders::_1));
	State_.CreateStateMember("Thrid", std::bind(&BloodSplatters::ThridUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&BloodSplatters::ThridStart, this, std::placeholders::_1));
	State_.ChangeState("Frist");
}

void BloodSplatters::Update(float _DeltaTime)
{
}

void BloodSplatters::End()
{
}

void BloodSplatters::FristStart(const StateInfo& _Info)
{
}

void BloodSplatters::FristUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void BloodSplatters::SecondStart(const StateInfo& _Info)
{
}

void BloodSplatters::SecondUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void BloodSplatters::ThridStart(const StateInfo& _Info)
{
}

void BloodSplatters::ThridUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
