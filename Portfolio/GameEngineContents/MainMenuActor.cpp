#include "PreCompile.h"
#include "MainMenuActor.h"

MainMenuActor::MainMenuActor() 
{
}

MainMenuActor::~MainMenuActor() 
{
}

void MainMenuActor::Start()
{
	Background_ = CreateComponent<GameEngineTextureRenderer>();
	Background_->GetTransform().SetWorldScale(GameEngineWindow::GetScale());
	Background_->SetTexture("TitleBackgorund_0.png");
}

void MainMenuActor::Update(float _DeltaTime)
{
	static float Time_ = 0.0f;
	static int Frame = 0;

	Time_ += _DeltaTime;

	if (0.1f <= Time_)
	{
		Time_ = 0.f;
		++Frame;
		Background_->SetTexture("TitleBackgorund_" + std::to_string(Frame) +".png");

		if (14 == Frame)
		{
			Frame = 0;
		}
	}
}

void MainMenuActor::End()
{
}
