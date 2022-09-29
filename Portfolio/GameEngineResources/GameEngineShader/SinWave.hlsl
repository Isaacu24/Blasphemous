
struct Input
{
    float4 LocalPos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 Tex : TEXCOORD;
};


Output SinWave_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.LocalPos;
    
    return NewOutPut;
}

cbuffer DeltaTimeData : register(b9)
{
    float AccTime;
    float2 ScreenXY;
    float WaveProgress;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 SinWave_PS(Output _Input) : SV_Target0
{
    float2 Coord = _Input.Pos;
    float2 Uv = Coord / ScreenXY.xy;
    //Uv.y = -1.0 - Uv.y;
        
    Uv.y += cos(Uv.x * 10.f + AccTime) / 10.f;
    
    return Tex.Sample(Smp, Uv).rgba;
}
