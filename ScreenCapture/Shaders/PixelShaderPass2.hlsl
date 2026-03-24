#include "BlurShader.hlsl"
#include "FilterShader.hlsl"

Texture2D _texture2D : register(t0);
SamplerState _samplerState : register(s0);
cbuffer _shaderVariables : register(b0)
{
    bool TextureFilterUse;
    bool HDRtoSDR;
    float HDRPaperWhite;
    float HDRMaximumNits;
    float SDRWhiteLevel;
    float Saturation;
    float RedChannel;
    float GreenChannel;
    float BlueChannel;
    float Brightness;
    float Contrast;
    float Gamma;
    float Blur;
    float Unused1;
    float Unused2;
    float Unused3;
};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    //Get texture colors
    float4 color = _texture2D.Sample(_samplerState, input.TexCoord);

    //Return color
    return color;
}