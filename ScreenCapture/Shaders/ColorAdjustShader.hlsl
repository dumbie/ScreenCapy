float4 AdjustSaturation(float4 color, float saturation)
{
    if (saturation == 1.0F)
    {
        return color;
    }
    float luminance = (color.r + color.g + color.b) / 3.0F;
    return lerp(luminance, color, saturation);
}

float4 AdjustColorChannels(float4 color, float redChannel, float greenChannel, float blueChannel)
{
    if (redChannel == 1.0F && greenChannel == 1.0F && blueChannel == 1.0F)
    {
        return color;
    }
    float4x4 matrix4x4 =
    {
        redChannel, 0.0, 0.0, 0.0,
        0.0, greenChannel, 0.0, 0.0,
        0.0, 0.0, blueChannel, 0.0,
        0.0, 0.0, 0.0, 1.0F
    };
    return mul(matrix4x4, color);
}

float4 AdjustBrightness(float4 color, float brightness)
{
    if (brightness == 1.0F)
    {
        return color;
    }
    float4x4 matrix4x4 =
    {
        brightness, 0.0, 0.0, 0.0,
        0.0, brightness, 0.0, 0.0,
        0.0, 0.0, brightness, 0.0,
        0.0, 0.0, 0.0, 1.0F
    };
    return mul(matrix4x4, color);
}

float4 AdjustContrast(float4 color, float contrast)
{
    if (contrast == 0.0F)
    {
        return color;
    }
    float4x4 matrix4x4 =
    {
        1.0F, 0.0, 0.0, contrast,
        0.0, 1.0F, 0.0, contrast,
        0.0, 0.0, 1.0F, contrast,
        0.0, 0.0, 0.0, 1.0F
    };
    return mul(matrix4x4, color);
}

float4 AdjustGamma(float4 color, float gamma)
{
    if (gamma == 1.0F)
    {
        return color;
    }
    float adjustGamma = 1.0F / gamma;
    return pow(color, adjustGamma);
}