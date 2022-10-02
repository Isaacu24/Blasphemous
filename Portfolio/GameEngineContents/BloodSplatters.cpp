#include "PreCompile.h"
#include "BloodSplatters.h"

BloodSplatters::BloodSplatters() {}

BloodSplatters::~BloodSplatters() {}

// GameEngineTexture::Cut("BloodSplatters.png", 5, 5);
// GameEngineTexture::Cut("BloodSplattersV3.png", 4, 4);
// GameEngineTexture::Cut("BloodSplattersV4.png", 4, 4);


void BloodSplatters::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("BloodSplatters", {"BloodSplatters.png", 0, 23, 0.05f, true});

    Renderer_->AnimationBindFrame("BloodSplatters",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      if (1 == _Info.CurFrame)
                                      {
                                          SoundPlayer_ = GameEngineSound::SoundPlayControl("Combat_Blood_1.wav");
                                          SoundPlayer_.Volume(0.05f);
                                      }
                                  });

    Renderer_->AnimationBindEnd("BloodSplatters",
                                [&](const FrameAnimation_DESC& _Info)
                                {
                                    Renderer_->CurAnimationReset();
                                    Renderer_->Off();
                                });

    Renderer_->CreateFrameAnimationCutTexture("BloodSplattersV3", {"BloodSplattersV3.png", 0, 15, 0.05f, true});

    Renderer_->AnimationBindFrame("BloodSplattersV3",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      if (1 == _Info.CurFrame)
                                      {
                                          SoundPlayer_ = GameEngineSound::SoundPlayControl("Combat_Blood_2.wav");
                                          SoundPlayer_.Volume(0.05f);
                                      }
                                  });

    Renderer_->AnimationBindEnd("BloodSplattersV3",
                                [&](const FrameAnimation_DESC& _Info)
                                {
                                    Renderer_->CurAnimationReset();
                                    Renderer_->Off();
                                });

    Renderer_->CreateFrameAnimationCutTexture("BloodSplattersV4", {"BloodSplattersV4.png", 0, 15, 0.05f, true});

    Renderer_->AnimationBindFrame("BloodSplattersV4",
                                  [&](const FrameAnimation_DESC& _Info)
                                  {
                                      if (1 == _Info.CurFrame)
                                      {
                                          SoundPlayer_ = GameEngineSound::SoundPlayControl("Combat_Blood_3.wav");
                                          SoundPlayer_.Volume(0.05f);
                                      }
                                  });

    Renderer_->AnimationBindEnd("BloodSplattersV4",
                                [&](const FrameAnimation_DESC& _Info)
                                {
                                    Renderer_->CurAnimationReset();
                                    Renderer_->Off();
                                });

    Renderer_->ChangeFrameAnimation("BloodSplattersV4");
    Renderer_->GetTransform().SetWorldScale({100, 100});

    Renderer_->SetPivot(PIVOTMODE::BOT);
}

void BloodSplatters::Update(float _DeltaTime) {}

void BloodSplatters::End() {}
