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
}

void LeftTopUI::Update(float _DeltaTime)
{
}

void LeftTopUI::End()
{
}
