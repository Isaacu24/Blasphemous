#include "PreCompile.h"
#include "Platform.h"

Platform::Platform() 
{
}

Platform::~Platform() 
{
}
//
//float Time_ = 0.0f;
//int Index_ = 0;

void Platform::Start()
{/*
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture("bigpatrollinFlyingEnemy_idle_0.png");
	Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::CENTER);*/
}

void Platform::Update(float _DeltaTime)
{
	//Time_ += _DeltaTime;

	//if (0.15f <= Time_)
	//{
	//	Index_++;
	//	Time_ -= 0.1f;

	//	if (8 == Index_)
	//	{
	//		Index_ = 0;
	//	}

	//	Renderer_->SetTexture("bigpatrollinFlyingEnemy_idle_" + std::to_string(Index_) + ".png");
	//	Renderer_->ScaleToTexture();
	//	Renderer_->SetPivot(PIVOTMODE::CENTER);
	//}
}

void Platform::End()
{
}
