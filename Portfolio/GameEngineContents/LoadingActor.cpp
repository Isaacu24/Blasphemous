#include "PreCompile.h"
#include "LoadingActor.h"

LoadingActor::LoadingActor() 
{
}

LoadingActor::~LoadingActor() 
{
}

void LoadingActor::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture("LoadingSpinningIco_0.png");
	Renderer_->GetTransform().SetWorldScale({ 200, 200 });
}

void LoadingActor::Update(float _DeltaTime)
{
	RendererTime_ += _DeltaTime;

	if (0.1f <= RendererTime_)
	{
		RendererTime_ -= 0.1f;
		++CurrentFrame_;

		if (25 == CurrentFrame_)
		{
			CurrentFrame_ = 0;
		}

		Renderer_->SetTexture("LoadingSpinningIco_" + std::to_string(CurrentFrame_) + ".png");
	}
}

void LoadingActor::End()
{
}
