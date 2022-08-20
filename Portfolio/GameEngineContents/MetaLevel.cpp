#include "PreCompile.h"
#include "MetaLevel.h"
#include "MetaSpriteWindow.h"

MetaLevel::MetaLevel() {}

MetaLevel::~MetaLevel() {}

void MetaLevel::Start()
{
    MetaAnimationGUI_ = GameEngineGUI::CreateGUIWindow<MetaSpriteWindow>("MetaSpriteGUI", this);

    MetaAnimationGUI_->MetaDir.MoveParentToExitsChildDirectory("ContentsResources");
    MetaAnimationGUI_->MetaDir.Move("ContentsResources");
    MetaAnimationGUI_->MetaDir.Move("Resources");
    MetaAnimationGUI_->MetaDir.Move("MetaAtlas");           

    MetaAnimationGUI_->Off();
}

void MetaLevel::Update(float _DeltaTime) 
{ 
}

void MetaLevel::End() {}

void MetaLevel::LevelStartEvent() 
{ 
    MetaAnimationGUI_->On(); 
}

void MetaLevel::LevelEndEvent() 
{
    MetaAnimationGUI_->Off(); 
}
