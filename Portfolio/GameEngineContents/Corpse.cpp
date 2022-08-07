#include "PreCompile.h"
#include "Corpse.h"

Corpse::Corpse() 
{
}

Corpse::~Corpse() 
{
}


void Corpse::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationCutTexture("elderBrother_corpse", { "elderBrother_corpse.png", 0, 11, 0.07f, false });
	Renderer_->ChangeFrameAnimation("elderBrother_corpse");
	Renderer_->GetTransform().SetWorldScale({ 370.f, 370.f });

	Renderer_->AnimationBindEnd("elderBrother_corpse", std::bind(&Corpse::CorpseEnd, this, std::placeholders::_1, this));
}

void Corpse::Update(float _DeltaTime)
{
	FloatCorpse(_DeltaTime);
}

void Corpse::End()
{
}

void Corpse::FloatCorpse(float _DeltaTime)
{
	if (false == IsSolstice_)
	{
		GetTransform().SetWorldUpMove(100.f, _DeltaTime);
	}

	else
	{
		GetTransform().SetWorldDownMove(100.f, _DeltaTime);
	}

	if (CreatePos_.y + 50.f < GetTransform().GetWorldPosition().y)
	{
		IsSolstice_ = true;
	}
}
