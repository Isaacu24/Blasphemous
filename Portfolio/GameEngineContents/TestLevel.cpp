#include "PreCompile.h"
#include "TestLevel.h"
#include "MetaAnimationWindow.h"

TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start()
{

}

void TestLevel::Update(float _DeltaTime)
{
}

void TestLevel::End()
{
}

void TestLevel::OnEvent() 
{
    MetaAnimationWindow* MetaAnimationGUI_ = GameEngineGUI::CreateGUIWindow<MetaAnimationWindow>("MetaAnimationGUI", this);
}

void TestLevel::OffEvent() 
{

}
