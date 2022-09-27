#include "PreCompile.h"
#include "Cloud.h"

Cloud::Cloud() {}

Cloud::~Cloud() {}


void Cloud::Start()
{ 
	Renderer_ = CreateComponent<GameEngineTextureRenderer>(); 
	Renderer_->SetTexture("ash-clouds_0.png");
    Renderer_->ScaleToTexture();
    Renderer_->GetTransform().SetWorldScale(Renderer_->GetTransform().GetWorldScale() * 2);

    AccSpeed_ = 350.f;
}

void Cloud::Update(float _DeltaTime) 
{
    AccSpeed_ += _DeltaTime;

    GetTransform().SetWorldMove(Dir_ * _DeltaTime * AccSpeed_);

    if (10.f < GetAccTime())
    {
        Death();
    }
}

void Cloud::End() {}