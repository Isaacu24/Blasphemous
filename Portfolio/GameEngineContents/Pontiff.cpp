#include "PreCompile.h"
#include "Pontiff.h"

Pontiff::Pontiff() 
{
}

Pontiff::~Pontiff() 
{
}

//GameEngineTexture::Cut("pontiff_closing_face.png", 5, 3);
//GameEngineTexture::Cut("pontiff_closing_torso.png", 5, 3);
//GameEngineTexture::Cut("pontiff_idle_helmet.png", 7, 5);
//GameEngineTexture::Cut("pontiff_idle_torso.png", 7, 5);
//GameEngineTexture::Cut("pontiff_openedIdle_face_DEATH.png", 10, 7);
//GameEngineTexture::Cut("pontiff_openIdle_face.png", 7, 5);
//GameEngineTexture::Cut("pontiff_opening_face.png", 5, 4);
//GameEngineTexture::Cut("pontiff_opening_torso.png", 5, 4);

void Pontiff::Start()
{
	Helmet_ = CreateComponent<GameEngineTextureRenderer>();
	Body_ = CreateComponent<GameEngineTextureRenderer>();

	Helmet_->CreateFrameAnimation("pontiff_idle_helmet", { "pontiff_idle_helmet.png", 0, 30, 0.1f, true });
	Helmet_->ChangeFrameAnimation("pontiff_idle_helmet");
	Helmet_->GetTransform().SetLocalScale({ 900, 1300 });
	Helmet_->GetTransform().SetLocalMove({ 0, 10 });

	Body_->CreateFrameAnimation("pontiff_idle_torso", { "pontiff_idle_torso.png", 0, 30, 0.1f, true});
	Body_->ChangeFrameAnimation("pontiff_idle_torso");
	Body_->GetTransform().SetLocalScale({ 900, 1100 });
}

void Pontiff::Update(float _DeltaTime)
{
}

void Pontiff::End()
{
}
