#include "TransformHeader.fx"

struct Input
{
    float4 Pos : POSITION;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
};

Output Debug3D_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal.xyz = _Input.Pos.xyz;
    NewOutPut.PosLocal.w = 1.0f;
    return NewOutPut;
}

cbuffer DebugInfo : register(b8)
{
    int4 Type;
    float4 Color;
}

float4 Debug3D_PS(Output _Input) : SV_Target0
{
    if (Type.x == 0 && length(_Input.PosLocal.xyz) > 0.7f)
    {
        clip(-1);
    }
    
    return Color;
}
