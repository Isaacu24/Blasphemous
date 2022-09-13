#include "TransformHeader.fx"
#include "RenderOption.fx"

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
    float4 PivotPos;
};

Output TextureAtlas_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    return NewOutPut;
}

cbuffer ColorData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
}

cbuffer UVData : register(b8)
{
    float4 Value;
}

cbuffer DeltaTimeData : register(b9)
{
    float4 Time;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 TextureAtlas_PS(Output _Input) : SV_Target0
{
    if ((Tex.Sample(Smp, _Input.Tex.xy).a == 0.f))
    {
        discard;
    }
    
    if (_Input.Tex.x > Value.x)
    {
        discard;
    }
    
    _Input.Tex.x += Time.x;
    
    return ((Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor);
}
