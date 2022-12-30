#include "PreCompile.h"
#include "TwisterBackground.h"

TwisterBackground::TwisterBackground() {}

TwisterBackground::~TwisterBackground() {}

void TwisterBackground::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->SetTexture("pontif-twister-background.png");
    Renderer_->GetTransform().SetWorldScale(float4{780, 780, 1});
    Renderer_->SetSamplingModePointMirror();
}

void TwisterBackground::Update(float _DeltaTime) 
{
    Renderer_->PlusTimeData(_DeltaTime * 1.5f); 
}

void TwisterBackground::End() {}