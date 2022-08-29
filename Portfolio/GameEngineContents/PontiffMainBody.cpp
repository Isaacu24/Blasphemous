#include "PreCompile.h"
#include "PontiffMainBody.h"

PontiffMainBody::PontiffMainBody() 
{
}

PontiffMainBody::~PontiffMainBody() 
{
}



void PontiffMainBody::Start() 
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();

    Renderer_->SetTexture("pontiff-boss-fight-spritesheet_8.png");
    Renderer_->GetTransform().SetLocalScale({550, 550});
}

void PontiffMainBody::Update(float _DeltaTime) {}
void PontiffMainBody::End() {}