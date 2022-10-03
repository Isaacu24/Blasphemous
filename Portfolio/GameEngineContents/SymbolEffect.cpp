#include "PreCompile.h"
#include "SymbolEffect.h"

SymbolEffect::SymbolEffect() {}

SymbolEffect::~SymbolEffect() {}


void SymbolEffect::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_twistedOne_symbol_appear",
                                              {"pope_twistedOne_symbol.png", 0, 5, 0.06f, false});


    Renderer_->AnimationBindFrame("pope_twistedOne_symbol_appear",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      if (1 == _Info.CurFrame)
                                      {
                                          SoundPlayer_.Pause(false);
                                          SoundPlayer_.Volume(0.03f);
                                      }
                                  });

    Renderer_->AnimationBindEnd("pope_twistedOne_symbol_appear",
                                [&](const FrameAnimation_DESC& _Info)
                                {
                                    Renderer_->CurAnimationReset();
                                    Renderer_->ChangeFrameAnimation("pope_twistedOne_symbol_loop");
                                });


    Renderer_->CreateFrameAnimationCutTexture("pope_twistedOne_symbol_loop",
                                              {"pope_twistedOne_symbol.png", 6, 17, 0.06f, true});

    Renderer_->AnimationBindFrame("pope_twistedOne_symbol_loop",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      if (1 == _Info.CurFrame)
                                      {
                                          SoundPlayer_.Pause(false);
                                          SoundPlayer_.Volume(0.03f);
                                      }
                                  });


    Renderer_->CreateFrameAnimationCutTexture("pope_twistedOne_symbol_disAppear",
                                              {"pope_twistedOne_symbol.png", 18, 23, 0.06f, false});

    Renderer_->AnimationBindEnd("pope_twistedOne_symbol_disAppear",
                                [&](const FrameAnimation_DESC& _Info) { Renderer_->Off(); });


    Renderer_->CreateFrameAnimationCutTexture("pope_twistedOne_symbol",
                                              {"pope_twistedOne_symbol.png", 0, 23, 0.06f, false});


    Renderer_->AnimationBindFrame("pope_twistedOne_symbol",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      if (1 == _Info.CurFrame)
                                      {
                                          SoundPlayer_.Pause(false);
                                          SoundPlayer_.Volume(0.03f);
                                      }
                                  });


    Renderer_->AnimationBindEnd("pope_twistedOne_symbol",
                                [&](const FrameAnimation_DESC& _Info)
                                {
                                    Renderer_->CurAnimationReset();
                                    Renderer_->Off();
                                });

    Renderer_->SetScaleModeImage();
    Renderer_->SetPivot(PIVOTMODE::BOT);
    Renderer_->ChangeFrameAnimation("pope_twistedOne_symbol_appear");
    Renderer_->Off();
}

void SymbolEffect::Update(float _DeltaTime) {}
void SymbolEffect::End() {}

void SymbolEffect::SetColor(COLORTYPE _Type)
{
    switch (_Type)
    {
        case COLORTYPE::RED:
            Renderer_->GetColorData().MulColor = float4::ONE;
            SoundPlayer_                       = GameEngineSound::SoundPlayControl("PONTIFF_SPELL_FIRE.wav");
            break;
        case COLORTYPE::BLUE:
            Renderer_->GetColorData().MulColor = float4{0.1f, 0.75f, 1.0f, 1.f};
            SoundPlayer_                       = GameEngineSound::SoundPlayControl("THUNDER_SPELL.wav");
            break;
        case COLORTYPE::GREEN:
            Renderer_->GetColorData().MulColor = float4{0.1f, 0.95f, 0.3f, 1.f};
            SoundPlayer_                       = GameEngineSound::SoundPlayControl("PURPLE_SPELL.wav");
            break;
        case COLORTYPE::PURPLE:
            Renderer_->GetColorData().MulColor = float4{0.46f, 0.0f, 1.0f, 1.f};
            SoundPlayer_                       = GameEngineSound::SoundPlayControl("PURPLE_SPELL.wav");
            break;
    }

    SoundPlayer_.Pause(true);
}