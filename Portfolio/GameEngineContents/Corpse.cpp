#include "PreCompile.h"
#include "Corpse.h"

Corpse::Corpse() {}

Corpse::~Corpse() {}


void Corpse::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("elderBrother_corpse", {"elderBrother_corpse.png", 0, 11, 0.08f, false});
    Renderer_->ChangeFrameAnimation("elderBrother_corpse");
    Renderer_->GetTransform().SetWorldScale({300.f, 300.f});
}

void Corpse::Update(float _DeltaTime)
{
    FloatCorpse(_DeltaTime);

    float4 Distance = GetTransform().GetWorldPosition() - CreatePos_;
    Distance = Distance.ABS3DReturn();

    if (300 <= Distance.y)
    {
        Death();
    }
}

void Corpse::End() {}

void Corpse::FloatCorpse(float _DeltaTime)
{
    if (false == IsSolstice_)
    {
        GetTransform().SetWorldUpMove(300.f, _DeltaTime);
    }

    else
    {
        GetTransform().SetWorldDownMove(350.f, _DeltaTime);
    }

    if (CreatePos_.y + 70.f < GetTransform().GetWorldPosition().y)
    {
        IsSolstice_ = true;
    }
}
