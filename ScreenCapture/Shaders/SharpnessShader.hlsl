float4 AdjustSharpnessUnsharp(Texture2D _texture2D, SamplerState _samplerState, float4 color, float2 texCoord, float2 texSize, float sharp_strength)
{
    if (sharp_strength == 1.0F)
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
    float sharp_unsharp = detail * sharp_strength;

    //Return result
    color.rgb += sharp_unsharp;
    return color;
}