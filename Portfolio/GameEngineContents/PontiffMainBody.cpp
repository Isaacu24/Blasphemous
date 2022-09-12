#include "PreCompile.h"
#include "PontiffMainBody.h"

PontiffMainBody::PontiffMainBody()
    : Alpha_(1.0f)
    , Speed_(10)
{}

PontiffMainBody::~PontiffMainBody() {}


void PontiffMainBody::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();

    Renderer_->SetTexture("pontiff-boss-fight-spritesheet_8.png");
    Renderer_->GetTransform().SetLocalScale({550, 550});
    Renderer_->GetColorData().PlusColor = float4{1.0f, 1.0f, 1.0f, 0.0f};
}

void PontiffMainBody::Update(float _DeltaTime)
{
    if (0 < Renderer_->GetColorData().PlusColor.r && false == IsAppear_)
    {
        GetTransform().SetWorldMove(float4::DOWN * Speed_ * _DeltaTime);
        Renderer_->GetColorData().PlusColor -= float4{_DeltaTime, _DeltaTime, _DeltaTime, 0.0f};

        if (0 >= Renderer_->GetColorData().PlusColor.r)
        {
            IsAppear_ = true;
            Speed_    = 400;
        }
    }

    if (true == IsAppear_)
    {
        Speed_ += _DeltaTime;
        GetTransform().SetWorldMove(float4::UP * Speed_ * _DeltaTime);
        Alpha_ -= _DeltaTime;
        Renderer_->GetColorData().PlusColor += float4{_DeltaTime, _DeltaTime, _DeltaTime, 0.0f};
        Renderer_->GetColorData().MulColor = float4{1.0f, 1.0f, 1.0f, Alpha_};
        
        if (0 > Alpha_)
        {
            Death();
        }
    }
}

void PontiffMainBody::End() {}