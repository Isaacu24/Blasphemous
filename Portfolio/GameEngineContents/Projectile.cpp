#include "PreCompile.h"
#include "Projectile.h"

Projectile::Projectile() 
{
}

Projectile::~Projectile() 
{
}


//GameEngineTexture::Cut("TakeBackProyectile.png", 6, 2);
//GameEngineTexture::Cut("TakeBackProyectileExplosion.png", 6, 3);
//GameEngineTexture::Cut("TakeBackProyectileHead.png", 6, 2);

void Projectile::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimation("TakeBackProyectile", {"TakeBackProyectile.png", 0, 9, 0.1f, true});
	Renderer_->CreateFrameAnimation("TakeBackProyectileExplosion", { "TakeBackProyectileExplosion.png", 0, 14, 0.1f, true });
	Renderer_->CreateFrameAnimation("TakeBackProyectileHead", { "TakeBackProyectileHead.png", 0, 9, 0.1f, true });
	Renderer_->ChangeFrameAnimation("TakeBackProyectileExplosion");
	Renderer_->GetTransform().SetWorldScale({75.f, 50.f});
}

void Projectile::Update(float _DeltaTime)
{
}

void Projectile::End()
{
}
