#include "PreCompile.h"
#include "SymbolEffect.h"

SymbolEffect::SymbolEffect() {}

SymbolEffect::~SymbolEffect() {}


void SymbolEffect::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_twistedOne_symbol",
                                            {"pope_twistedOne_symbol.png", 0, 23, 0.1f, true});

    Renderer_->SetScaleModeImage();
    Renderer_->SetPivot(PIVOTMODE::BOT);
    Renderer_->ChangeFrameAnimation("pope_twistedOne_symbol");
}

void SymbolEffect::Update(float _DeltaTime) {}
void SymbolEffect::End() {}

void SymbolEffect::SetColor(COLORTYPE _Type)
{
    switch (_Type)
    {
        case COLORTYPE::RED:
            Renderer_->GetColorData().MulColor = float4::ONE;
            break;
        case COLORTYPE::BLUE:
            Renderer_->GetColorData().MulColor = float4{0.1f, 0.75f, 1.0f, 1.f};
            break;
        case COLORTYPE::GREEN:
            Renderer_->GetColorData().MulColor = float4{0.1f, 0.95f, 0.3f, 1.f};
            break;
        case COLORTYPE::PURPLE:
            Renderer_->GetColorData().MulColor = float4{0.46f, 0.0f, 1.0f, 1.f};
            break;
        default:
            Renderer_->GetColorData().MulColor = float4::ONE;
            break;
    }


}