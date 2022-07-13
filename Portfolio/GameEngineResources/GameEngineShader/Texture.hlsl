#include "TransformHeader.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD; //uv ÁÂÇ¥
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD; //uv ÁÂÇ¥
};

Output Texture_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.Pos.w = 1.0f;
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    
    NewOutPut.Tex.xy += DeltaTime_.xy;
    
    return NewOutPut;
}

Texture2D Tex : register(t0);
SamplerState Sam : register(s0);
Texture2D Tex2 : register(t1);

float4 Texture_PS(Output _Input) : SV_Target0
{
    float4 TextureColor = Tex.Sample(Sam, _Input.Tex.xy);
    
    float4 TextureColor2 = Tex2.Sample(Sam, _Input.Tex.xy);
    
    //TextureColor.y += TextureColor2.y;
    //TextureColor.x += TextureColor2.x;
   
    if (TextureColor.r >= 0.9f)
    {
        discard;
    }

    return TextureColor;

}
