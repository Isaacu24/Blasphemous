#include "TransformHeader.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct Output
{
    float4 Pos : SV_POSITION; //�����Ͷ������� �Ѿ�� ����Ʈ�� ������ 
    float4 LocalPos : POSITION; 
    float4 Color : COLOR;
};

//Pos: MVP * ViewPort�� ������ ����
//Pos2: ���ؽ� ���� ��ǥ �� ��ü

//ȭ�鿡 ����� �簢���� �� ����(��ǥ)�� �� �� �ִ�

cbuffer ResultColor : register(b8)
{
    float4 Color;
}

Output Color_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos.w = 1.0f;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    
    NewOutPut.LocalPos = _Input.Pos;
    NewOutPut.Color = _Input.Color;
    
    return NewOutPut;
}

float4 Color_PS(Output _Input) : SV_Target0
{
    if (length(float2(_Input.LocalPos.x, _Input.LocalPos.y)) < 0.5f)
    {
        clip(-1);
    }
        
    return Color;
}
