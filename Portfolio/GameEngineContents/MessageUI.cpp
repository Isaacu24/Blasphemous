#include "PreCompile.h"
#include "MessageUI.h"

MessageUI::MessageUI() 
{
}

MessageUI::~MessageUI() 
{
}

void MessageUI::Start() 
{
    GetTransform().SetWorldScale({2, 2, 1});

	Renderer_ = CreateComponent<GameEngineUIRenderer>();
    Renderer_->SetTexture("popup_message_background.png");
    Renderer_->ScaleToTexture();
}

void MessageUI::Update(float _DeltaTime) {}

void MessageUI::End() {}
