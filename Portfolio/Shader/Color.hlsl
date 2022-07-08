#include "TransformHeader.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct Output
{
    float4 Pos : POSITION;
    float4 Pos2 : SV_POSITION;
    float4 Color : COLOR;
};


Output Color_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Pos.w = 1.0f;
    NewOutPut.Pos2 = _Input.Pos;
    NewOutPut.Color = _Input.Color;
    
    return NewOutPut;
}

cbuffer ResultColor : register(b0)
{
    float4 PlusColor;
    float4 MultyplyColor;
}

float4 Color_PS(Output _Input) : SV_Target0
{
    if (length(float2(_Input.Pos2.x, _Input.Pos2.y)) < 0.5f)
    {
        clip(-1);
    }
        
    return _Input.Color/* * MultyplyColor + PlusColor*/;
}
