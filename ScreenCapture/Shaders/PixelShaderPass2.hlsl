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

float4 AdjustTextureBlur(float4 color, float2 texCoord, float2 texSize, float2 texDdxy)
{
    if (Blur == 0.0F)
    {
        return color;
    }
    //Blur
    //return TextureBlurBoxVertical(_texture2D, _samplerState, color, texCoord, texDdxy, Blur);
    return TextureBlurCosineVertical(_texture2D, _samplerState, color, texCoord, texDdxy, Blur);
    //return TextureBlurGaussianVertical(_texture2D, _samplerState, color, texCoord, texDdxy, Blur);
};

float4 main(PS_INPUT input) : SV_TARGET
{
    //Get texture colors
    float4 color = _texture2D.Sample(_samplerState, input.TexCoord);

    //Get texture size
    float2 textureSize = float2(0.0F, 0.0F);
    _texture2D.GetDimensions(textureSize.x, textureSize.y);

    //Get texture ddxy
    float2 textureDdxy = float2(ddx(input.TexCoord.x), ddy(input.TexCoord.y));

    //Adjust texture blur
    color = AdjustTextureBlur(color, input.TexCoord, textureSize, textureDdxy);

    //Return color
    return color;
}