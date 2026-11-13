#include "BlurShader.hlsl"
#include "ColorAdjustShader.hlsl"
#include "ColorConvertShader.hlsl"
#include "FilterShader.hlsl"
#include "SharpnessShader.hlsl"

Texture2D _texture2D : register(t0);
SamplerState _samplerState : register(s0);
cbuffer _shaderVariables : register(b0)
{
    int TextureFilter;
    bool MultiPass;
    bool HDRtoSDR;
    float HDRPaperWhite;
    float HDRBrightness;
    float SDRWhiteLevel;
    float Saturation;
    float RedChannel;
    float GreenChannel;
    float BlueChannel;
    float Brightness;
    float Contrast;
    float Gamma;
    float Blur;
    float Sharpness;
    float Unused1;
};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    //Sample texture color
    float4 color = _texture2D.Sample(_samplerState, input.TexCoord);

    //Get original texture alpha
    float colorAlpha = color.a;

    //Get texture size
    float2 textureSize = float2(0.0F, 0.0F);
    _texture2D.GetDimensions(textureSize.x, textureSize.y);

    //Get texture ddxy
    float2 textureDdxy = float2(ddx(input.TexCoord.x), ddy(input.TexCoord.y));

    //Adjust texture filter
    if (TextureFilter == 1)
    {
        color = TextureFilterBilinear(_texture2D, _samplerState, input.TexCoord, textureSize);
    }

    //Adjust sharpness
    color = AdjustSharpnessLuminance(_texture2D, _samplerState, color, input.TexCoord, textureDdxy, Sharpness);

    //Adjust saturation
    color = AdjustSaturation(color, Saturation);

    //Adjust color channels
    color = AdjustColorChannels(color, RedChannel, GreenChannel, BlueChannel);

    //Adjust brightness
    color = AdjustBrightness(color, Brightness);

    //Adjust contrast
    color = AdjustContrast(color, Contrast);

    //Adjust gamma
    color = AdjustGamma(color, Gamma);

    //Adjust texture blur
    if (Blur != 0.0F)
    {
        color = TextureBlurGaussianHorizontal(_texture2D, _samplerState, color, input.TexCoord, textureDdxy, Blur);
    }

    //Convert HDR to SDR
    if (!MultiPass && HDRtoSDR)
    {
        color.rgb = ColorHDRtoSDR(color, SDRWhiteLevel, HDRPaperWhite, HDRBrightness);
    }

    //Set original texture alpha
    color.a = colorAlpha;

    //Return color
    return color;
}