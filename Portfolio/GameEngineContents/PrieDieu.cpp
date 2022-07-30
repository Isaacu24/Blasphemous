#include "PreCompile.h"
#include "PrieDieu.h"

PrieDieu::PrieDieu() 
{
}

PrieDieu::~PrieDieu() 
{
}

void PrieDieu::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimation("priedieu_stand_and_liton_anim", { "priedieu_stand_and_liton_anim.png", 1, 6, 0.1f, true });
	Renderer_->ChangeFrameAnimation("priedieu_stand_and_liton_anim");
	Renderer_->GetTransform().SetWorldScale({ 150, 300 });
	Renderer_->GetTransform().SetWorldPosition({ 0, 0, static_cast<int>(ACTORORDER::Object) });
}

void PrieDieu::Update(float _DeltaTime)
{

}

void PrieDieu::End()
{
}
