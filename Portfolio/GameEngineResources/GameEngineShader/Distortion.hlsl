//#include "TransformHeader.fx"
//#include "RenderOption.fx"

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


Output TextureAtlas_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    //_Input.Pos += PivotPos;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.PosLocal = _Input.Pos;
    
    //NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    //NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    return NewOutPut;
}

cbuffer DeltaTimeData : register(b9)
{
    float Time;
    float2 ScreenXY;
    int padding;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);


float2 GetOffsetFromCenter(float2 screenCoords, float2 screenSize)
{
    float2 halfScreenSize = screenSize / 2.0;
    return (screenCoords.xy - halfScreenSize) / min(halfScreenSize.x, halfScreenSize.y);
}

float2 GetDistortionTexelOffset(float2 offsetDirection, float offsetDistance, float time)
{
    float EffectDuration = 1.0;
    float EffectFadeInTimeFactor = 0.5;
    float EffectWidth = 0.4;
    float EffectMaxTexelOffset = 20.0;
    
    float progress = Time / EffectDuration;
    
    float halfWidth = EffectWidth / 2.0;
    float lower = 1.0 - smoothstep(progress - halfWidth, progress, offsetDistance);
    float upper = smoothstep(progress, progress + halfWidth, offsetDistance);
    
    float band = 1.0 - (upper + lower);
    
    float strength = 1.0 - progress;
    float fadeStrength = smoothstep(0.0, EffectFadeInTimeFactor, progress);
    
    float distortion = band * strength * fadeStrength;
    
    return distortion * offsetDirection * EffectMaxTexelOffset;
}


float3 GetTextureOffset(float2 coords, float2 textureSize, float2 texelOffset)
{
    float2 texelSize = 1.0 / textureSize;
    float2 offsetCoords = coords + texelSize * texelOffset;
    
    float2 halfTexelSize = texelSize / 2.0;
    float2 clampedOffsetCoords = clamp(offsetCoords, halfTexelSize, 1.0 - halfTexelSize);
    
    return Tex.Sample(Smp, clampedOffsetCoords).rgb;
}


float4 TextureAtlas_PS(Output _Input) : SV_Target0
{
    float time = Time;
    
    float2 screenCoords = _Input.Pos;
    float2 screenSize = ScreenXY.xy;
        
    float2 offsetFromCenter = GetOffsetFromCenter(screenCoords, screenSize);
    float2 offsetDirection = normalize(-offsetFromCenter);
    float offsetDistance = length(offsetFromCenter);
    
    float2 offset = GetDistortionTexelOffset(offsetDirection, offsetDistance, time);
    
    float2 coords = (screenCoords / screenSize);
    //coords.y = 1.0 - coords.y;
    
    float3 background = GetTextureOffset(coords, screenSize, offset);
    
    float4 result = float4(background, 1.0);
    
    return result;
}
