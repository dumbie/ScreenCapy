float CalculateGaussian1D(float x, float sigma)
{
    return exp(-(x * x) / (2.0F * sigma * sigma));
}

float CalculateCosine1D(float x, float sigma)
{
    return 1.0F + cos((x / sigma) * 3.1415926535897932384626433832795F);
}

float4 TextureBlurBoxSingle(Texture2D _texture2D, SamplerState _samplerState, float4 color, float2 texCoord, float2 texDdxy, float blurAmount)
{
    float Normalize = 1.0F;
    for (int y = -blurAmount; y <= blurAmount; y++)
    {
        for (int x = -blurAmount; x <= blurAmount; x++)
        {
            float2 Offset = float2(x, y) * texDdxy;
            color += _texture2D.Sample(_samplerState, texCoord + Offset);
            Normalize++;
        }
    }
    return color / Normalize;
}

float4 TextureBlurBoxHorizontal(Texture2D _texture2D, SamplerState _samplerState, float4 color, float2 texCoord, float2 texDdxy, float blurAmount)
{
    float Normalize = 1.0F;
    for (int i = -blurAmount; i <= blurAmount; i++)
    {
        float2 Offset = float2(i * texDdxy.x, 0.0F);
        color += _texture2D.Sample(_samplerState, texCoord + Offset);
        Normalize++;
    }
    return color / Normalize;
}

float4 TextureBlurBoxVertical(Texture2D _texture2D, SamplerState _samplerState, float4 color, float2 texCoord, float2 texDdxy, float blurAmount)
{
    float Normalize = 1.0F;
    for (int i = -blurAmount; i <= blurAmount; i++)
    {
        float2 Offset = float2(0.0F, i * texDdxy.y);
        color += _texture2D.Sample(_samplerState, texCoord + Offset);
        Normalize++;
    }
    return color / Normalize;
}

float4 TextureBlurCosineHorizontal(Texture2D _texture2D, SamplerState _samplerState, float4 color, float2 texCoord, float2 texDdxy, float blurAmount)
{
    float Normalize = 1.0F;
    for (int i = -blurAmount; i <= blurAmount; i++)
    {
        float Weight = CalculateCosine1D(i, blurAmount);
        float2 Offset = float2(i * texDdxy.x, 0.0F);
        color += _texture2D.Sample(_samplerState, texCoord + Offset) * Weight;
        Normalize += Weight;
    }
    return color / Normalize;
}

float4 TextureBlurCosineVertical(Texture2D _texture2D, SamplerState _samplerState, float4 color, float2 texCoord, float2 texDdxy, float blurAmount)
{
    float Normalize = 1.0F;
    for (int i = -blurAmount; i <= blurAmount; i++)
    {
        float Weight = CalculateCosine1D(i, blurAmount);
        float2 Offset = float2(0.0F, i * texDdxy.y);
        color += _texture2D.Sample(_samplerState, texCoord + Offset) * Weight;
        Normalize += Weight;
    }
    return color / Normalize;
}

float4 TextureBlurGaussianHorizontal(Texture2D _texture2D, SamplerState _samplerState, float4 color, float2 texCoord, float2 texDdxy, float blurAmount)
{
    float Normalize = 1.0F;
    int BlurRange = ceil(blurAmount * 2.57F);
    for (int i = -BlurRange; i <= BlurRange; i++)
    {
        float Weight = CalculateGaussian1D(i, blurAmount);
        float2 Offset = float2(i * texDdxy.x, 0.0F);
        color += _texture2D.Sample(_samplerState, texCoord + Offset) * Weight;
        Normalize += Weight;
    }
    return color / Normalize;
}

float4 TextureBlurGaussianVertical(Texture2D _texture2D, SamplerState _samplerState, float4 color, float2 texCoord, float2 texDdxy, float blurAmount)
{
    float Normalize = 1.0F;
    int BlurRange = ceil(blurAmount * 2.57F);
    for (int i = -BlurRange; i <= BlurRange; i++)
    {
        float Weight = CalculateGaussian1D(i, blurAmount);
        float2 Offset = float2(0.0F, i * texDdxy.y);
        color += _texture2D.Sample(_samplerState, texCoord + Offset) * Weight;
        Normalize += Weight;
    }
    return color / Normalize;
}