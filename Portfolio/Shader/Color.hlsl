#include "TransformHeader.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct Output
{
    float4 Pos : SV_POSITION; //레스터라이저로 넘어가서 뷰포트가 곱해짐 
    float4 Pos2 : POSITION; 
    float4 Color : COLOR;
};

//Pos: WVP * ViewPort가 곱해진 상태
//Pos2: 버텍스 버퍼 좌표 그 자체

//화면에 띄워진 사각형을 두 관점(좌표)로 볼 수 있다

cbuffer ResultColor : register(b0)
{
    float4 PlusColor;
    float4 MultyplyColor;
}

Output Color_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Pos.w = 1.0f;
    NewOutPut.Pos = mul(NewOutPut.Pos, WorldViewProjection);
    
    NewOutPut.Pos2 = _Input.Pos;
    NewOutPut.Color = _Input.Color;
    
    return NewOutPut;
}

float4 Color_PS(Output _Input) : SV_Target0
{
    if (length(float2(_Input.Pos2.x, _Input.Pos2.y)) < 0.5f)
    {
        clip(-1);
    }
        
    return _Input.Color/* * MultyplyColor + PlusColor*/;
}
