
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


Output Distortion_VS(Input _Input)
{
	Output NewOutPut = (Output)0;
	NewOutPut.Pos = _Input.LocalPos;

	return NewOutPut;
}

cbuffer DistortionData : register(b8)
{
	float AccTime;
	float2 ScreenXY;
	float fPadding;
}

cbuffer OffSetData : register(b7)
{
	float2 Offset;
	float2 Padding;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);


float2 GetOffsetFromCenter(float2 ScreenCoords, float2 ScreenSize)
{
	float2 HalfScreenSize = ScreenSize * Offset; //위치
	return (ScreenCoords.xy - HalfScreenSize) / (HalfScreenSize.x, HalfScreenSize.y);
}

float2 GetDistortionTexelOffset(float2 OffsetDirection, float OffsetDistance, float Time)
{
	float EffectDuration = 3.0f;
	float EffectFadeInTimeFactor = 0.25f;
	float EffectWidth = 0.1f;
	float EffectMaxTexelOffset = 100.f; //일그러질 텍셀의 폭

	//힘
	float Progress = Time / EffectDuration;

	float HalfWidth = EffectWidth / 2.0;

	float Lower = 1.0 - smoothstep(Progress - HalfWidth, Progress, OffsetDistance);
	float Upper = smoothstep(Progress, Progress + HalfWidth, OffsetDistance);

	float Band = 1.0 - (Upper + Lower);

	float Strength = 1.0 - Progress;
	float FadeStrength = smoothstep(0.0, EffectFadeInTimeFactor, Progress);

	float Distortion = Band * Strength * FadeStrength;

	return Distortion * OffsetDirection * EffectMaxTexelOffset;
}


float3 GetTextureOffset(float2 Coords, float2 TextureSize, float2 TexelOffset)
{
	float2 TexelSize = 1.0 / TextureSize;
	float2 OffsetCoords = Coords + TexelSize * TexelOffset;
	float2 HalfTexelSize = TexelSize / 2.0;

	//최종 UV
	float2 ClampedOffsetCoords = clamp(OffsetCoords, HalfTexelSize, 1.0 - HalfTexelSize);

	return Tex.Sample(Smp, ClampedOffsetCoords).rgb;
}


float4 Distortion_PS(Output _Input) : SV_Target0
{
	float DeltaTime = AccTime;

	float2 ScreenCoords = _Input.Pos;
	float2 ScreenSize = ScreenXY.xy;

	//센터에서 현재 픽셀의 길이값
	float2 OffsetFromCenter = GetOffsetFromCenter(ScreenCoords, ScreenSize);
	float2 OffsetDirection = normalize(-OffsetFromCenter);
	float OffsetDistance = length(OffsetFromCenter);

	float2 Offset = GetDistortionTexelOffset(OffsetDirection, OffsetDistance * 0.15f, DeltaTime);

	float2 Coords = (ScreenCoords / ScreenSize);

	float3 Background = GetTextureOffset(Coords, ScreenSize, Offset);

	return float4(Background, 1.0);
}
