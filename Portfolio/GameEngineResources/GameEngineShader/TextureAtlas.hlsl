#include "TransformHeader.fx"


struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
};

cbuffer AtlasData : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
};


Output TextureAtlas_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.Pos.w = 1.0f;
    NewOutPut.PosLocal = _Input.Pos;

    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    return NewOutPut;
}

Texture2D Tex : register(t0);
SamplerState Sam : register(s0);
float4 TextureAtlas_PS(Output _Input) : SV_Target0
{
    float4 TextureColor = Tex.Sample(Sam, _Input.Tex.xy);
   
    if (TextureColor.r >= 0.9f)
    {
        discard;
    }
    
    if (TextureColor.r <= 0.1f)
    {
        discard;
    }
    
    return TextureColor;

}
