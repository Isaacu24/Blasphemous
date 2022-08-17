#include "PreCompile.h"
#include "MetaTextureRenderer.h"

MetaTextureRenderer::MetaTextureRenderer() 
{
}

MetaTextureRenderer::~MetaTextureRenderer() 
{}

void MetaTextureRenderer::Update(float _Delta) 
{
    GameEngineTextureRenderer::Update(_Delta);
    MetaSetPivot(); 
}


void MetaTextureRenderer::MetaSetPivot()
{
    float X = Pivot_.x - 0.5f;
    float Y = (1 - Pivot_.y) - 0.5f;

    float Width  = abs(X * SizeX_);
    float Height = abs(Y * SizeY_);

    // 1��и��� ��
    if (0.f < X && 0.f > Y)
    {
        GetTransform().SetLocalPosition({-(Width), -(Height)});
    }

    // 2��и��� ��
    else if (0.f > X && 0.0f > Y)
    {
        GetTransform().SetLocalPosition({(Width), -(Height)});
    }

    // 3��и��� ��
    else if (0.f > X && 0.f < Y)
    {
        GetTransform().SetLocalPosition({(Width), (Height)});
    }

    // 4��и��� ��
    else if (0.f < X && 0.f < Y)
    {
        GetTransform().SetLocalPosition({-(Width), (Height)});
    }
}
