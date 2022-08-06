#include "PreCompile.h"
#include "LeftTopUI.h"

LeftTopUI::LeftTopUI() 
{
}

LeftTopUI::~LeftTopUI() 
{
}

void LeftTopUI::Start()
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
}

void LeftTopUI::Update(float _DeltaTime)
{
}

void LeftTopUI::End()
{
}
