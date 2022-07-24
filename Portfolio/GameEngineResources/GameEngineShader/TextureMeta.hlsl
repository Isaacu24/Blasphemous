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

cbuffer MetaData : register(b0)
{
    int X_;
    int Y_;
    
    int Height_;
    int Width_;
   
    float4 Pivot_; //UV ��ǥ
};

Output TextureAtlas_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
   
    //NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    //NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    return NewOutPut;
}

Texture2D Tex : register(t0);
SamplerState Sam : register(s0);
float4 TextureAtlas_PS(Output _Input) : SV_Target0
{
    float4 TextureColor = Tex.Sample(Sam, _Input.Tex.xy);
   
    return TextureColor;
}
