float4 AdjustSharpnessUnsharp(Texture2D _texture2D, SamplerState _samplerState, float4 color, float2 texCoord, float2 texSize, float sharpness_strength)
{
    if (sharpness_strength == 0.0F)
    {
        return color;
    }

    //Get texture samples
    float3 center = _texture2D.Sample(_samplerState, texCoord).rgb;
    float3 north = _texture2D.Sample(_samplerState, texCoord + float2(0.0F, -texSize.y)).rgb;
    float3 east = _texture2D.Sample(_samplerState, texCoord + float2(texSize.x, 0.0F)).rgb;
    float3 south = _texture2D.Sample(_samplerState, texCoord + float2(0.0F, texSize.y)).rgb;
    float3 west = _texture2D.Sample(_samplerState, texCoord + float2(-texSize.x, 0.0F)).rgb;

    //Get blur and detail
    float3 blur = (north + east + south + west) / 4.0F;
    float3 detail = center - blur;

    //Adjust sharpness
    float sharpness_result = detail * sharpness_strength;

    //Return result
    color.rgb += sharpness_result;
    return color;
}

float4 AdjustSharpnessLuminance(Texture2D _texture2D, SamplerState _samplerState, float4 color, float2 texCoord, float2 texSize, float sharpness_strength)
{
    if (sharpness_strength == 0.0F)
    {
        return color;
    }

    //Settings
    float sharpness_limit = 0.05F;

    //Get texture samples
    float3 center = _texture2D.Sample(_samplerState, texCoord).rgb;
    float3 north = _texture2D.Sample(_samplerState, texCoord + float2(0.0F, -texSize.y)).rgb;
    float3 east = _texture2D.Sample(_samplerState, texCoord + float2(texSize.x, 0.0F)).rgb;
    float3 south = _texture2D.Sample(_samplerState, texCoord + float2(0.0F, texSize.y)).rgb;
    float3 west = _texture2D.Sample(_samplerState, texCoord + float2(-texSize.x, 0.0F)).rgb;

    //Get blur and detail
    float3 blur = (north + east + south + west) / 4.0F;
    float3 detail = center - blur;

    //Calculate luminance
    float luminance = (center.r + center.g + center.b) / 3.0F;

    //Adjust sharpness
    float sharpness_result = dot(detail, luminance * sharpness_strength);
    sharpness_result = clamp(sharpness_result, -sharpness_limit, sharpness_limit);

    //Return result
    color.rgb += sharpness_result;
    return color;
}